#include "GestorSprites.hpp"
#include "Motor.hpp"

#include <algorithm>

// SPRITE

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

// SPRITE ANIMADO

SpriteAnimado::SpriteAnimado(std::vector<Sprite *> _sprites, bool _enBucle, std::string _nombre)
{
    sprites = _sprites;
    enBucle = _enBucle;
    nombre = _nombre;
    ncuadros = _sprites.size();
}

SpriteAnimado::~SpriteAnimado() {}

// GESTOR DE SPRITES

GestorSprites::GestorSprites() {}

GestorSprites::~GestorSprites()
{
    if (spritesAnimados.size() > 0)
    {
        for (auto &spriteAnimado : spritesAnimados)
            delete spriteAnimado;
        spritesAnimados.clear();
    }

    if (sprites.size() > 0)
    {
        for (auto &sprite : sprites)
            delete sprite;
        sprites.clear();
    }
}

void GestorSprites::generarSprites()
{
    Texture2D tautos = Motor::retMotor().retGestorTexturas()->retTextura("autos");
    insertar((Rectangle) {40.f, 10.f, 35.f, 65.f}, "auto1", tautos);    


    Texture2D tbalas = Motor::retMotor().retGestorTexturas()->retTextura("balas");
    insertar((Rectangle) {312.f, 108.f, 13.f, 11.f}, "bala1", tbalas);

    // Los sprites de las explosiones
    Texture2D texplosion = Motor::retMotor().retGestorTexturas()->retTextura("explosiones");
    insertar((Rectangle) {130.f, 15.f, 45.f, 40.f}, "explosionBlanca1", texplosion);
    insertar((Rectangle) {70.f, 10.f, 50.f, 55.f},  "explosionBlanca2", texplosion);
    insertar((Rectangle) {5.f, 10.f, 55.f, 50.f},   "explosionBlanca3", texplosion);
    
    insertar((Rectangle) {130.f, 75.f, 45.f, 40.f}, "explosionGris1", texplosion);
    insertar((Rectangle) {70.f, 70.f, 50.f, 55.f},  "explosionGris2", texplosion);
    insertar((Rectangle) {5.f, 65.f, 55.f, 50.f},   "explosionGris3", texplosion);

    insertar((Rectangle) {130.f, 135.f, 45.f, 40.f}, "explosionAmarillo1", texplosion);
    insertar((Rectangle) {70.f, 130.f, 50.f, 55.f},  "explosionAmarillo2", texplosion);
    insertar((Rectangle) {5.f, 135.f, 55.f, 50.f},   "explosionAmarillo3", texplosion);

    insertar((Rectangle) {130.f, 195.f, 45.f, 40.f}, "explosionNaranja1", texplosion);
    insertar((Rectangle) {70.f, 190.f, 50.f, 55.f},  "explosionNaranja2", texplosion);
    insertar((Rectangle) {5.f, 195.f, 55.f, 50.f},   "explosionNaranja3", texplosion);

    Texture2D tobstaculos = Motor::retMotor().retGestorTexturas()->retTextura("obstaculos");
    insertar((Rectangle) {0.f, 855.f, 209.f, 67.f},   "obstaculo1", tobstaculos);
    
}

void GestorSprites::generarSpritesAnimados()
{
    insertar(retListaSprites("explosionBlanca"),   false, "explosionBlanca");
    insertar(retListaSprites("explosionGris"),     false, "explosionGris");
    insertar(retListaSprites("explosionAmarillo"), false, "explosionAmarillo");
    insertar(retListaSprites("explosionNaranja"),  false, "explosionNaranja");
}

Sprite *GestorSprites::retSprite(const std::string nombre) const
{
    for (auto &sprite : sprites)
        if (sprite->nombre == nombre)
            return sprite;
    return nullptr;
}

SpriteAnimado *GestorSprites::retSpriteAnimado(const std::string nombre) const
{
    for (auto &spriteAnimado : spritesAnimados)
        if (spriteAnimado->nombre == nombre)
            return spriteAnimado;
    return nullptr;
}

void GestorSprites::insertar(Rectangle espacio, std::string nombre, Texture2D textura)
{
    sprites.push_back(new Sprite(espacio, nombre, textura));
}

void GestorSprites::insertar(std::vector<Sprite *> sprites, bool enBucle, std::string nombre)
{
    spritesAnimados.push_back(new SpriteAnimado(sprites, enBucle, nombre));
}

std::vector<Sprite *> GestorSprites::retListaSprites(std::string subNombre)
{
    std::vector<Sprite *> lista;
    std::for_each(sprites.begin(), sprites.end(), [&] (Sprite *sprite) {
                                                      if (sprite->nombre.find(subNombre) != std::string::npos)
                                                          lista.push_back(sprite);
                                                  });
    return lista;
}

/*
Sprite *GestorSprites::CrearSprite(std::string nombre)
{
    Sprite *actual = retSprite(nombre);
    return (actual ? new Sprite(actual->espacio, actual->nombre, actual->textura) : nullptr);
}
*/
