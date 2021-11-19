#include "GestorSprites.hpp"

#include "Motor.hpp"

Sprite::Sprite(Rectangle _espacio, std::string _nombre)
{
    espacio = _espacio;
    nombre = _nombre;
}

Sprite::~Sprite() {}

void Sprite::dibujar()
{
    Texture2D textura = Motor::retMotor().retGestorTexturas()->retTextura("principal");
    DrawTextureRec(textura, espacio, (Vector2) {0.f, 0.f}, RAYWHITE);
}

void Sprite::dibujar(Vector2 posicion)
{
    Texture2D textura = Motor::retMotor().retGestorTexturas()->retTextura("principal");
    DrawTextureRec(textura, espacio, posicion, RAYWHITE);
}

// Gestor de sprites

GestorSprites::GestorSprites() {}

GestorSprites::~GestorSprites()
{
    if (sprites.size() > 0)
    {
        for (auto &sprite : sprites)
            delete sprite;
        sprites.clear();
    }
}

void GestorSprites::generarSprites()
{
    insertar((Rectangle){5.f, 0.f, 95.f, 180.f}, "auto1");
    insertar((Rectangle){1.f, 185.f, 21.f, 10.f}, "bala1");
}

void GestorSprites::insertar(Rectangle rect, std::string nombre)
{
    sprites.push_back(new Sprite(rect, nombre));
}

Sprite *GestorSprites::retSprite(std::string nombre)
{
    for (auto &sprite : sprites)
        if (sprite->nombre == nombre)
            return sprite;
    return nullptr;
}


