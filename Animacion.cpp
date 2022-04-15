#include "Animacion.hpp"
#include "Motor.hpp"
#include "Convertir.hpp"

Animacion::Animacion(Vector2 _posicion, TipoAnimacion tipo)
{
    auto data = dataAnimacion[tipo];
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = data.dimension.x;
    espacio.height = data.dimension.y;
    animacion = Motor::retMotor().retGestorSprites()->retSpriteAnimado(data.nombre);
    //if (animacion != nullptr)
    enBucle = animacion->enBucle;
    angulo = 0.0f;
    cuadroActual = 0;
    velocidadCuadro = data.velocidadCuadro;
    contadorCuadro = 0;
    estaCorriendo = true;
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
        {
            if (enBucle == true)
            {
                cuadroActual = 0;
            }
            else
            {
                animacion = nullptr; // Terminar la animacion
                estaCorriendo = false;
            }
        }
    }
}

void Animacion::dibujar()
{
    if (animacion == nullptr)
        return;
    Sprite *sprite = animacion->sprites.at(cuadroActual);
    Rectangle vespacio = Convertir::MetrosEnPixeles(espacio);
    DrawTexturePro(sprite->textura, sprite->espacio, vespacio, (Vector2) {vespacio.width / 2.f, vespacio.height / 2.f}, angulo, RAYWHITE);
}
