#include "GestorSprites.hpp"
#include "Motor.hpp"

Sprite::Sprite(Rectangle _espacio, std::string _nombre, Texture2D _textura)
{
    espacio = _espacio;
    nombre = _nombre;
    textura = _textura;
}

Sprite::~Sprite() {}

void Sprite::dibujar()
{
    DrawTextureRec(textura, espacio, (Vector2) {0.f, 0.f}, RAYWHITE);
}

void Sprite::dibujar(Vector2 posicion)
{
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
    Texture2D tprincipal = Motor::retMotor().retGestorTexturas()->retTextura("principal");
    insertar((Rectangle){40.f, 10.f, 35.f, 65.f}, "auto1", tprincipal);    
    insertar((Rectangle){187.f, 3.f, 12.f, 20.f}, "bala1", tprincipal);
    insertar((Rectangle){745.f, 25.f, 100.f, 30.f}, "muro1", tprincipal);
}

void GestorSprites::insertar(Rectangle espacio, std::string nombre, Texture2D textura)
{
    sprites.push_back(new Sprite(espacio, nombre, textura));
}

Sprite *GestorSprites::retSprite(std::string nombre)
{
    for (auto &sprite : sprites)
        if (sprite->nombre == nombre)
            return sprite;
    return nullptr;
}

Sprite *GestorSprites::CrearSprite(std::string nombre)
{
    Sprite *actual = retSprite(nombre);
    return (actual ? new Sprite(actual->espacio, actual->nombre, actual->textura) : nullptr);
}
