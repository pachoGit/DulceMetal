#include "Objeto.hpp"
#include "Motor.hpp"
#include "Config.hpp"

Objeto::Objeto(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::obj_espacio.width;
    espacio.height = Config::obj_espacio.height;

    colision.x = espacio.x;
    colision.y = espacio.y;
    colision.width = Config::obj_espacio.width;
    colision.height = Config::obj_espacio.height;

    posicion = _posicion;
    sprite = nullptr; //Motor::retMotor().retGestorSprites()->retSprite("auto1");
    angulo = 0.f;
    visible = true;
}

Objeto::~Objeto()
{
    if (sprite != nullptr)
        sprite = nullptr;
}

void Objeto::actualizar(float dt)
{
    posicion.x += dt * 10.1;
}

void Objeto::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    colision.x = posicion.x;
    colision.y = posicion.y;
    if (sprite != nullptr && visible)
        DrawTexturePro(sprite->textura, sprite->espacio, espacio, (Vector2) {espacio.width/2.f, espacio.height/2.f}, angulo, RAYWHITE);
    DrawRectangleLinesEx(espacio, 2, RED);
    //DrawRectanglePro(colision, (Vector2) {colision.width / 2.f, colision.height / 2.f}, angulo, BLUE);
}


