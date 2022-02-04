#include "Objeto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Util.hpp"

Objeto::Objeto(Vector2 _posicion)
{
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::obj_espacio.width;
    espacio.height = Config::obj_espacio.height;

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
}

void Objeto::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    if (sprite != nullptr && visible)
        DrawTexturePro(sprite->textura, sprite->espacio, Util::arreglarPosicion(espacio), (Vector2) {espacio.width/2.f, espacio.height/2.f}, angulo, RAYWHITE);
    //DrawRectangleLinesEx(espacio, 2, BLACK);
    //Util::DrawRectangleLinesPro(Util::arreglarPosicion(espacio), (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo, GREEN);
}


