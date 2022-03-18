#include "Animacion.hpp"
#include "Config.hpp"
#include "Motor.hpp"

Animacion::Animacion(Vector2 _posicion, std::string _animacion, int _velocidadCuadro)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::DIM_EXPLOSION.x;
    espacio.height = Config::DIM_EXPLOSION.y;
    animacion = Motor::retMotor().retGestorSprites()->retSpriteAnimado(_animacion);
    //if (animacion != nullptr)
    enBucle = animacion->enBucle;
    angulo = 0.0f;
    cuadroActual = 0;
    velocidadCuadro = _velocidadCuadro;
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
    DrawTexturePro(sprite->textura, sprite->espacio, espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo, RAYWHITE);
}
