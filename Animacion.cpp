#include "Animacion.hpp"
#include "Config.hpp"
#include "Motor.hpp"

#include <iostream>

Animacion::Animacion(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::DIM_EXPLOSION.x;
    espacio.height = Config::DIM_EXPLOSION.y;
    animacion = Motor::retMotor().retGestorSprites()->retSpriteAnimado("explosionAmarillo");
    angulo = 0.0f;
    cuadroActual = 0;
    velocidadCuadro = 10;
    contadorCuadro = 0;
}

Animacion::~Animacion()
{
}

void Animacion::actualizar(float dt)
{
    if (animacion == nullptr)
        return;
    contadorCuadro++;
    if (contadorCuadro >= (GetFPS() / velocidadCuadro))
    {
        contadorCuadro = 0;
        cuadroActual++;
        if (cuadroActual >= animacion->ncuadros)
            cuadroActual = 0;
    }
}

void Animacion::dibujar()
{
    if (animacion == nullptr)
        return;
    Sprite *sprite = animacion->sprites.at(cuadroActual);
    DrawTexturePro(sprite->textura, sprite->espacio, espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo, RAYWHITE);
}
