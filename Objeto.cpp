#include "Objeto.hpp"

Objeto::Objeto(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    posicion = _posicion;
    angulo = 0.f;
}

Objeto::~Objeto() {}

void Objeto::actualizar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
}

void Objeto::dibujar()
{
}

