#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>
#include <vector>

#include <raylib.h>

class Sprite
{
  public:

    // Espacio del sprite en la textura
    Rectangle espacio;

    // Nombre del sprite
    std::string nombre;

    // Puntero hacia la textura donde se encuentra el sprite
    Texture2D textura;

  public:

    Sprite(Rectangle _espacio, std::string _nombre, Texture2D _textura);

    ~Sprite();

    // Dibujar el sprite en la posicion (0, 0)
    void dibujar();

    // Dibujar el sprite en una posicion dada
    void dibujar(Vector2 posicion);
};

class SpriteAnimado
{
  public:
    
    // Lista de sprites para la animacion
    std::vector<Sprite *> sprites;

    // Siempre repetir
    bool enBucle;

    // Nombre de la animacion
    std::string nombre;

    // Cantidad de cuadros que conforman la animacion
    int ncuadros;

  public:
    
    SpriteAnimado(std::vector<Sprite *> _sprites, bool _enBucle, std::string _nombre);

    ~SpriteAnimado();
};

class GestorSprites
{
  public:
    
    // Lista de sprites de un solo cuadro
    std::vector<Sprite *> sprites;

    // Lista de sprites de varios cuadros
    std::vector<SpriteAnimado *> spritesAnimados;

  public:

    GestorSprites();

    ~GestorSprites();

    // Genera los sprites
    // NOTA: Llamar a esta funcion despues de cargar 
    void generarSprites();

    // Genera los sprites animados
    void generarSpritesAnimados();

    // Obtener un sprite
    Sprite *retSprite(const std::string nombre) const;

    SpriteAnimado *retSpriteAnimado(const std::string nombre) const;

  private:
    
    // Insertar un sprite
    void insertar(Rectangle espacio, std::string nombre, Texture2D textura);

    // Inserta un sprite animado
    void insertar(std::vector<Sprite *> sprites, bool enBucle, std::string nombre);

    // Obtener una lista de sprites, de acuerdo a su nombre
    std::vector<Sprite *> retListaSprites(std::string subNombre);

    // Sprite *CrearSprite(std::string nombre);
};

#endif /* SPRITE_HPP */
