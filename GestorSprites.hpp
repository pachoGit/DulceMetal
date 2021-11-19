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

  public:

    Sprite(Rectangle _espacio, std::string _nombre);

    ~Sprite();

    // Dibujar el sprite en la posicion (0, 0)
    void dibujar();

    // Dibujar el sprite en una posicion dada
    void dibujar(Vector2 posicion);
};

class GestorSprites
{
  public:
    
    std::vector<Sprite *> sprites;

  public:

    GestorSprites();

    ~GestorSprites();

    // Genera los sprites
    // NOTA: Llamar a esta funcion despues de cargar 
    void generarSprites();

    // Insertar un sprite
    void insertar(Rectangle rect, std::string nombre);

    // Obtener un sprite
    Sprite *retSprite(std::string nombre);
};


#endif /* SPRITE_HPP */
