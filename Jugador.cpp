#include "Jugador.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

Jugador::Jugador(Vector2 _posicion) : Auto(_posicion)
{
    sprite = Motor::retMotor().retGestorSprites()->retSprite("autoVerde");
    velocidad = {10.f, 10.f};
    tipoClase = CLASE_JUGADOR;
    nombre = "Jugador";

    iniciarBarraVida();
    generarFisicasIniciales();
}

Jugador::~Jugador()
{
    // Se borra en "Auto.cpp"
}

void Jugador::actualizar(float dt)
{
    procesarFisicas();
    sincronizarObjetoConFisicas();

    if (IsKeyPressed(KEY_SPACE))
        disparar();
    for (auto &bala : balas)
        bala->actualizar(dt);

    actualizarBarraVida();

    if (IsKeyDown(KEY_ENTER))
    {
        for (auto &bala : balas)
            bala->explotar();
    }
    
    eliminarBalasDeMemoria();
}

void Jugador::procesarFisicas()
{
    if (fcuerpo == nullptr)
        return;

    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();

    actualizarFriccion();


    // TODO: Evitar que la variable aumente a mas de 360 grados, sin utilizar SetTransform, para reiniciar el conteo del angulo
    if (IsKeyDown(KEY_D))
        cuerpo->ApplyAngularImpulse(2.0f, true);
    if (IsKeyDown(KEY_A))
        cuerpo->ApplyAngularImpulse(-2.0f, true);
    if (IsKeyReleased(KEY_A))
        detenerRotacion();

    if (IsKeyDown(KEY_W))
    {
        float longitud = espacio.height;
        b2Vec2 impulso(longitud * std::sin(cuerpo->GetAngle()), longitud * std::cos(cuerpo->GetAngle()) * -1);
        cuerpo->ApplyLinearImpulse(10.0f * impulso, cuerpo->GetWorldCenter(), true);
    }

    if (IsKeyDown(KEY_S))
    {
        float longitud = espacio.height;
        b2Vec2 impulso(longitud * std::sin(cuerpo->GetAngle()), longitud * std::cos(cuerpo->GetAngle()) * -1);
        cuerpo->ApplyLinearImpulse(-(10.0f * impulso), cuerpo->GetWorldCenter(), true);
    }
}

void Jugador::dibujar()
{
    Auto::dibujar();
}

void Jugador::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);

    TipoBala tbala = BALA_FURIA;

    Bala *b1 = new Bala((Vector2){arribaIzquierda.x, arribaIzquierda.y}, tbala);
    b1->angulo = angulo;
    Bala *b2 = new Bala((Vector2){arribaDerecha.x, arribaDerecha.y}, tbala);
    b2->angulo = angulo;

    balas.push_back(b1);
    balas.push_back(b2);
}

void Jugador::generarFisicasIniciales()
{
    if (fcuerpo != nullptr)
    {
        delete fcuerpo;
        fcuerpo = nullptr;
    }
    fcuerpo = new FisicasCuerpo(this, FCUERPO_DEFECTO);
    if (fcuerpo == nullptr)
        return;
    fcuerpo->agregarColisionador(FMaterial(80.f, 0.0f, 0.0f), FGRUPO_JUGADOR, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_OBSTACULO));
}
