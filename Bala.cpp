#include "Bala.hpp"
#include "Motor.hpp"
#include "Config.hpp"

Bala::Bala(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::bala_espacio.width;
    espacio.height = Config::bala_espacio.height;
    sprite = Motor::retMotor().retGestorSprites()->retSprite("bala1");
    velocidad = 100.f;
    angulo = 0.f; // Para que este a la misma direccion de la textura del auto :D
}

Bala::~Bala()
{
    
}

void Bala::actualizar(float dt)
{
    posicion.x += std::sin(angulo * DEG2RAD) * dt * velocidad;
    posicion.y -= std::cos(angulo * DEG2RAD) * dt * velocidad;
}

void Bala::dibujar()
{
    Objeto::dibujar();
}
