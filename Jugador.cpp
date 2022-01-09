#include "Jugador.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"

Jugador::Jugador(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::auto_espacio.width;
    espacio.height = Config::auto_espacio.height;

    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    vida = 0;
    velocidad = 50.f;
}

Jugador::~Jugador()
{
    // Borrar las balas
}

void Jugador::actualizar(float dt)
{
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        angulo += 0.5f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        angulo -= 0.5f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        posicion.x += std::sin(angulo * DEG2RAD) * dt * velocidad;
        posicion.y -= std::cos(angulo * DEG2RAD) * dt * velocidad;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        posicion.x -= std::sin(angulo * DEG2RAD) * dt * velocidad;
        posicion.y += std::cos(angulo * DEG2RAD) * dt * velocidad;
    }
    if (IsKeyPressed(KEY_SPACE))
        disparar();
    for (auto &bala : balas)
        bala->actualizar(dt);
}

void Jugador::dibujar()
{
    Objeto::dibujar();
    for (auto bala : balas)
        bala->dibujar();
}

void Jugador::disparar()
{
    //Vector2 posicion = {posicion.x + (espacio.width / 2.f), posicion.y};
    Vector2 p = {posicion.x, posicion.y - (espacio.height / 2.f)};
    Bala *nueva = new Bala(p);
    nueva->angulo = angulo;
    balas.push_back(nueva);
}
