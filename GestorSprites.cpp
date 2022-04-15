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
    insertar((Rectangle) {40.f, 10.f, 35.f, 65.f}, "autoNaranja", tautos);    
    insertar((Rectangle) {90.f, 10.f, 35.f, 65.f}, "autoAzul", tautos);    
    insertar((Rectangle) {140.f, 10.f, 35.f, 65.f}, "autoVerde", tautos);    
    insertar((Rectangle) {190.f, 10.f, 35.f, 65.f}, "autoAmarillo", tautos);    
    insertar((Rectangle) {240.f, 10.f, 35.f, 65.f}, "autoNegro", tautos);    

    Texture2D tbalas = Motor::retMotor().retGestorTexturas()->retTextura("balas");
    insertar((Rectangle) {312.f, 108.f, 13.f, 11.f}, "balaBasica",    tbalas);
    insertar((Rectangle) {400.f, 215.f, 9.f, 14.f},  "balaFuego",     tbalas);
    insertar((Rectangle) {422.f, 215.f, 9.f, 14.f},  "balaElectrico", tbalas);
    insertar((Rectangle) {444.f, 215.f, 9.f, 14.f},  "balaAura",      tbalas);
    insertar((Rectangle) {466.f, 215.f, 9.f, 14.f},  "balaFuria",     tbalas);
    insertar((Rectangle) {488.f, 215.f, 9.f, 14.f},  "balaFloreal",   tbalas);

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
    
    // Algunas explosiones estan en la textura de las balas
    insertar((Rectangle) {11.f, 102.f, 5.f, 5.f},    "explosionBalaVerde1", tbalas);
    insertar((Rectangle) {17.f, 102.f, 8.f, 8.f},    "explosionBalaVerde2", tbalas);
    insertar((Rectangle) {25.f, 100.f, 10.f, 10.f},  "explosionBalaVerde3", tbalas);
    insertar((Rectangle) {35.f, 100.f, 10.f, 10.f},  "explosionBalaVerde4", tbalas);
    insertar((Rectangle) {46.f, 98.f, 10.f, 10.f},   "explosionBalaVerde5", tbalas);
    
    insertar((Rectangle) {11.f, 122.f, 5.f, 5.f},    "explosionBalaAmarilla1", tbalas);
    insertar((Rectangle) {17.f, 122.f, 8.f, 8.f},    "explosionBalaAmarilla2", tbalas);
    insertar((Rectangle) {25.f, 120.f, 10.f, 10.f},  "explosionBalaAmarilla3", tbalas);
    insertar((Rectangle) {35.f, 120.f, 10.f, 10.f},  "explosionBalaAmarilla4", tbalas);
    insertar((Rectangle) {46.f, 118.f, 10.f, 10.f},  "explosionBalaAmarilla5", tbalas);

    insertar((Rectangle) {11.f, 142.f, 5.f, 5.f},    "explosionBalaRoja1", tbalas);
    insertar((Rectangle) {17.f, 142.f, 8.f, 8.f},    "explosionBalaRoja2", tbalas);
    insertar((Rectangle) {25.f, 140.f, 10.f, 10.f},  "explosionBalaRoja3", tbalas);
    insertar((Rectangle) {35.f, 140.f, 10.f, 10.f},  "explosionBalaRoja4", tbalas);
    insertar((Rectangle) {46.f, 138.f, 10.f, 10.f},  "explosionBalaRoja5", tbalas);

    insertar((Rectangle) {11.f, 162.f, 5.f, 5.f},    "explosionBalaAzul1", tbalas);
    insertar((Rectangle) {17.f, 162.f, 8.f, 8.f},    "explosionBalaAzul2", tbalas);
    insertar((Rectangle) {25.f, 160.f, 10.f, 10.f},  "explosionBalaAzul3", tbalas);
    insertar((Rectangle) {35.f, 160.f, 10.f, 10.f},  "explosionBalaAzul4", tbalas);
    insertar((Rectangle) {46.f, 158.f, 10.f, 10.f},  "explosionBalaAzul5", tbalas);

    Texture2D tobstaculos = Motor::retMotor().retGestorTexturas()->retTextura("obstaculos");
    insertar((Rectangle) {5.f, 740.f, 195.f, 50.f},   "muroGris", tobstaculos);
    insertar((Rectangle) {215.f, 740.f, 195.f, 50.f}, "muroNaranja", tobstaculos);
    insertar((Rectangle) {5.f, 865.f, 195.f, 50.f},   "muroGrisRace", tobstaculos);
    insertar((Rectangle) {5.f, 800.f, 195.f, 50.f},   "muroNaranjaRace", tobstaculos);
    insertar((Rectangle) {860.f, 170.f, 46.f, 40.f},  "cono", tobstaculos);
    insertar((Rectangle) {662.f, 513.f, 127.f, 127.f},  "carpa", tobstaculos);
    insertar((Rectangle) {540.f, 790.f, 140.f, 140.f},  "arbol", tobstaculos);
    
    // Las texturas de armas y vida que se recogen en campo de batalla :D
    Texture2D trecogibles = Motor::retMotor().retGestorTexturas()->retTextura("recogibles");
    insertar((Rectangle) {0.f,   0.f, 40.f, 40.f},   "armaRayo1", trecogibles);
    insertar((Rectangle) {40.f,  0.f, 40.f, 40.f},   "armaRayo2", trecogibles);
    insertar((Rectangle) {80.f,  0.f, 40.f, 40.f},   "armaRayo3", trecogibles);
    insertar((Rectangle) {120.f, 0.f, 40.f, 40.f},   "armaRayo4", trecogibles);
                                                     
    insertar((Rectangle) {0.f,   40.f, 40.f, 40.f},  "armaFuego1", trecogibles);
    insertar((Rectangle) {40.f,  40.f, 40.f, 40.f},  "armaFuego2", trecogibles);
    insertar((Rectangle) {80.f,  40.f, 40.f, 40.f},  "armaFuego3", trecogibles);
    insertar((Rectangle) {120.f, 40.f, 40.f, 40.f},  "armaFuego4", trecogibles);
                                                     
    insertar((Rectangle) {0.f,   80.f, 40.f, 40.f},  "armaAura1", trecogibles);
    insertar((Rectangle) {40.f,  80.f, 40.f, 40.f},  "armaAura2", trecogibles);
    insertar((Rectangle) {80.f,  80.f, 40.f, 40.f},  "armaAura3", trecogibles);
    insertar((Rectangle) {120.f, 80.f, 40.f, 40.f},  "armaAura4", trecogibles);

    insertar((Rectangle) {0.f,   120.f, 40.f, 40.f}, "armaFloreal1", trecogibles);
    insertar((Rectangle) {40.f,  120.f, 40.f, 40.f}, "armaFloreal2", trecogibles);
    insertar((Rectangle) {80.f,  120.f, 40.f, 40.f}, "armaFloreal3", trecogibles);
    insertar((Rectangle) {120.f, 120.f, 40.f, 40.f}, "armaFloreal4", trecogibles);

    insertar((Rectangle) {0.f,   160.f, 40.f, 40.f}, "armaFuria1", trecogibles);
    insertar((Rectangle) {40.f,  160.f, 40.f, 40.f}, "armaFuria2", trecogibles);
    insertar((Rectangle) {80.f,  160.f, 40.f, 40.f}, "armaFuria3", trecogibles);
    insertar((Rectangle) {120.f, 160.f, 40.f, 40.f}, "armaFuria4", trecogibles);

    insertar((Rectangle) {0.f,   200.f, 40.f, 40.f}, "vida1", trecogibles);
    insertar((Rectangle) {40.f,  200.f, 40.f, 40.f}, "vida2", trecogibles);
    insertar((Rectangle) {80.f,  200.f, 40.f, 40.f}, "vida3", trecogibles);
    insertar((Rectangle) {120.f, 200.f, 40.f, 40.f}, "vida4", trecogibles);
}

void GestorSprites::generarSpritesAnimados()
{
    insertar(retListaSprites("explosionBlanca"),        false, "explosionBlanca");
    insertar(retListaSprites("explosionGris"),          false, "explosionGris");
    insertar(retListaSprites("explosionAmarillo"),      false, "explosionAmarillo");
    insertar(retListaSprites("explosionNaranja"),       false, "explosionNaranja");
    insertar(retListaSprites("explosionBalaVerde"),     false, "explosionBalaVerde");
    insertar(retListaSprites("explosionBalaAmarilla"),  false, "explosionBalaAmarilla");
    insertar(retListaSprites("explosionBalaRoja"),      false, "explosionBalaRoja");
    insertar(retListaSprites("explosionBalaAzul"),      false, "explosionBalaAzul");

    insertar(retListaSprites("armaRayo"),    false, "armaRayo");
    insertar(retListaSprites("armaFuego"),   false, "armaFuego");
    insertar(retListaSprites("armaAura"),    false, "armaAura");
    insertar(retListaSprites("armaFloreal"), false, "armaFloreal");
    insertar(retListaSprites("armaFuria"),   false, "armaFuria");
    insertar(retListaSprites("vida"),        false, "vida");
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
