#include "Obstaculo.hpp"
#include "Motor.hpp"
#include "Config.hpp"

#include <iostream>

Obstaculo::Obstaculo(Vector2 _posicion, TipoObstaculo tipo, Vector2 _tam) : Objeto(_posicion)
{
    auto info = dataObstaculo[tipo];
    espacio.width =  _tam.x;
    espacio.height = _tam.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite(info);
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
}
