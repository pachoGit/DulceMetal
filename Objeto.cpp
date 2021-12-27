#include "Objeto.hpp"
#include "Motor.hpp"

Objeto::Objeto(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    posicion = _posicion;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    angulo = 0.f;
}

Objeto::~Objeto() {}

void Objeto::actualizar()
{
    posicion.x += GetFrameTime() * 5.1;
}

void Objeto::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    if (sprite != nullptr)
        sprite->dibujar(posicion);
}

