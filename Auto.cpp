#include "Auto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"

Auto::Auto(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::auto_espacio.width;
    espacio.height = Config::auto_espacio.height;

    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    vida = 0;
    velocidad = 60.f;
}

Auto::~Auto()
{
    // Borrar las balas
}

void Auto::actualizar(float dt)
{
    posicion.x += std::sin(angulo * DEG2RAD) * dt * velocidad;
    posicion.y -= std::cos(angulo * DEG2RAD) * dt * velocidad;
}

void Auto::dibujar()
{
    Objeto::dibujar();
    for (auto bala : balas)
        bala->dibujar();
}

void Auto::disparar()
{
    Vector2 p = {posicion.x, posicion.y};
    Bala *nueva = new Bala(p);
    nueva->angulo += angulo;
    balas.push_back(nueva);
}
