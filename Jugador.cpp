#include "Jugador.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

Jugador::Jugador(Vector2 _posicion, TipoAuto _tipo, unsigned _ID) : Auto(_posicion, _tipo, _ID)
{
    auto data = dataAuto.at(_tipo);
    sprite = Motor::retMotor().retGestorSprites()->retSprite(data.nombre);
    velocidad = {10.f, 10.f};
    tipoClase = CLASE_JUGADOR;
    // Creado al pasar por el constructor de "Auto.cpp"
    if (fcuerpo != nullptr)
        Motor::retMotor().retGestorFisicas()->destruirFCuerpo(fcuerpo);
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_DEFECTO,
                                                                 FMaterial(80.f, 0.0f, 0.0f),
                                                                 FGRUPO_JUGADOR,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_OBSTACULO | FGRUPO_BALA | FGRUPO_EQUIPAMIENTO));
    nombre = "Jugador";
}

Jugador::~Jugador()
{
    // Se borra en "Auto.cpp"
}

void Jugador::actualizar(float dt)
{
    procesarFisicas();
    sincronizarObjetoConFisicas();
    actualizarBarraVida();

    if (IsKeyPressed(KEY_SPACE) && !inventario->estaVacio())
    {
        tipoBala = inventario->retActual()->tipoBala;
        disparar();
    }

    if (IsKeyPressed(KEY_LEFT_SHIFT))
    {
        tipoBala = BALA_BASICA;
        disparar();
    }

    for (auto &bala : balas)
        bala->actualizar(dt);

    if (IsKeyDown(KEY_ENTER))
    {
        for (auto &bala : balas)
            bala->explotar();
    }
    
    // Manejo del inventario
    if (IsKeyPressed(KEY_Q) && !inventario->estaVacio())
            inventario->retroceder();
    if (IsKeyPressed(KEY_E) && !inventario->estaVacio())
            inventario->avanzar();

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
        reducirRotacion();

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
    if (!inventario->estaVacio())
    {
        std::string nbalas = std::to_string(inventario->retActual()->cantidad);
        Vector2 ptexto = Convertir::MetrosEnPixeles((Vector2) {30.f, 15.f});
        DrawText(nbalas.c_str(), ptexto.x, ptexto.y, 2, RED);
    }
}

void Jugador::disparar()
{
    Auto::disparar();
}
