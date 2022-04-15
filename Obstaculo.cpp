#include "Obstaculo.hpp"
#include "Motor.hpp"
#include "Config.hpp"

#include <iostream>

Obstaculo::Obstaculo(Vector2 _posicion, TipoObstaculo tipo) : Objeto(_posicion)
{
    auto info = dataObstaculo[tipo];
    espacio.width =  info.second.x;
    espacio.height = info.second.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite(info.first);
    tipoClase = CLASE_OBSTACULO;
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_ESTATICO,
                                                                 FMaterial(1.f, 0.f, 1.f),
                                                                 FGRUPO_OBSTACULO,
                                                                 FGRUPO_TODO);
    nombre = "Obstaculo";
}

Obstaculo::~Obstaculo() {}

void Obstaculo::actualizar(float dt)
{
    procesarFisicas();
    sincronizarObjetoConFisicas();
}

void Obstaculo::procesarFisicas()
{
}

void Obstaculo::dibujar()
{
    Objeto::dibujar();
    /*
    if (fcuerpo)
        fcuerpo->dibujar();
    */
}
