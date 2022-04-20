#include "Motor.hpp"
#include "Enemigo.hpp"

#include <iostream>

Enemigo::Enemigo(Vector2 _posicion, TipoAuto _tipo, unsigned _ID) : Auto(_posicion, _tipo, _ID)
{
    tiempoDisparo = GetTime();
    if (fcuerpo != nullptr)
        Motor::retMotor().retGestorFisicas()->destruirFCuerpo(fcuerpo);
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_DEFECTO,
                                                                 FMaterial(80.f, 0.0f, 0.0f),
                                                                 FGRUPO_ENEMIGO,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO | FGRUPO_EQUIPAMIENTO));
    nombre = "Enemigo";
}

Enemigo::~Enemigo() {}

void Enemigo::actualizar(float dt)
{
    Auto::actualizar(dt);
    // Disparar bot
    int resultado = GetTime() - tiempoDisparo;
    
    if (resultado > 2)
    {
        std::cout << "Disparando..." << std::endl;
        disparar();
        tiempoDisparo = GetTime();
    }
}

