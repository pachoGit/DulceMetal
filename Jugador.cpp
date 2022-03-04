#include "Jugador.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

Jugador::Jugador(Vector2 _posicion) : Auto(_posicion)
{
    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    velocidad = {10.f, 10.f};
    tipoClase = CLASE_JUGADOR;
    nombre = "Jugador";

    generarFisicasIniciales();
}

Jugador::~Jugador()
{
    // Se borra en "Auto.cpp"
}

void Jugador::actualizar(float dt)
{
    if (habilitarProcesadoFisicas == true)
    {
        sincronizarObjetoConFisicas();
        barraVida->actualizar(dt);
        return;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        angulo += 0.5f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        angulo -= 0.5f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        posicion.x += std::sin(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.x;
        posicion.y -= std::cos(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.y;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        posicion.x -= std::sin(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.x;
        posicion.y += std::cos(Convertir::GradosEnRadianes(angulo)) * dt * velocidad.y;
    }
    sincronizarFisicasConObjeto();

    if (IsKeyPressed(KEY_SPACE))
        disparar();
    for (auto &bala : balas)
        bala->actualizar(dt);

    barraVida->actualizar(dt);
}

void Jugador::dibujar()
{
    Auto::dibujar();

    /*
    Objeto::dibujar();
    barraVida->dibujar();
    for (auto bala : balas)
        bala->dibujar();
    */
    fcuerpo->dibujar(); // Dibujar las fisicas
}

void Jugador::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);
    Bala *b1 = new Bala((Vector2){arribaIzquierda.x, arribaIzquierda.y});
    b1->angulo = angulo;
    Bala *b2 = new Bala((Vector2){arribaDerecha.x, arribaDerecha.y});
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
