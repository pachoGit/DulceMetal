#include "Muro.hpp"
#include "Motor.hpp"
#include "Config.hpp"

#include <iostream>

Muro::Muro(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::DIM_MURO.x;
    espacio.height = Config::DIM_MURO.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("obstaculo1");
    tipoClase = CLASE_MURO;
    nombre = "Muro";

    generarFisicasIniciales();
}

Muro::~Muro() {}

void Muro::actualizar(float dt)
{
    procesarFisicas();
    sincronizarObjetoConFisicas();
}

void Muro::procesarFisicas()
{
}

void Muro::dibujar()
{
    Objeto::dibujar();
    /*
    if (fcuerpo)
        fcuerpo->dibujar();
    */
}

void Muro::generarFisicasIniciales()
{
    fcuerpo = new FisicasCuerpo(this, FCUERPO_ESTATICO);
    if (fcuerpo == nullptr)
        return;
    fcuerpo->agregarColisionador(FMaterial(1.f, 0.f, 1.f), FGRUPO_OBSTACULO, FGRUPO_TODO);
}
