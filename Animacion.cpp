#include "Animacion.hpp"
#include "Config.hpp"
#include "Motor.hpp"

Animacion::Animacion(Vector2 _posicion, TipoAnimacion tipo, int _velocidadCuadro)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    Vector2 dimension; // Dimensiones de la animacion
    std::string nombre; // Nombre de la  animacion
    // TODO: Esto si se deberia estructurar :D, me da asco y todo :D
    switch (tipo)
    {
        case ANIM_EXPLOSION_BLANCA:
        case ANIM_EXPLOSION_GRIS:
        case ANIM_EXPLOSION_AMARILLO:
        case ANIM_EXPLOSION_NARANJA:
            dimension.x = Config::DIM_EXPLOSION_AUTO.x;
            dimension.y = Config::DIM_EXPLOSION_AUTO.y;
            break;
        default: // Explosiones de las balas
            dimension.x = Config::DIM_EXPLOSION_BALA.x;
            dimension.y = Config::DIM_EXPLOSION_BALA.y;
    }

    switch (tipo)
    {
        case ANIM_EXPLOSION_BLANCA:
            nombre = "explosionBlanca";
            break;
        case ANIM_EXPLOSION_GRIS:
            nombre = "explosionGris";
            break;
        case ANIM_EXPLOSION_AMARILLO:
            nombre = "explosionAmarillo";
            break;
        case ANIM_EXPLOSION_NARANJA:
            nombre = "explosionNaranja";
            break;
        case ANIM_EXPLOSION_BALA_VERDE:
            nombre = "explosionBalaVerde";
            break;
        case ANIM_EXPLOSION_BALA_AMARILLA:
            nombre = "explosionBalaAmarilla";
            break;
        case ANIM_EXPLOSION_BALA_ROJA:
            nombre = "explosionBalaRoja";
            break;
        case ANIM_EXPLOSION_BALA_AZUL:
            nombre = "explosionBalaAzul";
            break;
    }
    
    espacio.width  = dimension.x;
    espacio.height = dimension.y;
    animacion = Motor::retMotor().retGestorSprites()->retSpriteAnimado(nombre);
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
