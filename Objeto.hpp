#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <raylib.h>
#include <cmath>

#include "GestorSprites.hpp"

class Objeto
{
  public:

    // Posicion y dimensiones actual ocupado por el objeto en la ventana del juego
    // NOTA: Considerar que la esquina superior izquierda de este rectangulo esta en
    // el centro del dibujo, por lo que este rectangulo parte desde el centro del sprite
    // hacia la derecha
    // Es decir que la posicion (0, 0) es el centro del sprite :D
    Rectangle espacio;

    // Posicion actual del objeto
    Vector2 posicion;
    
    // Sprite del objeto
    Sprite *sprite;

    // Angulo de rotacion del objeto
    float angulo;

    // Indica si el objeto debe dibujarse
    bool visible;

  public:
    
    Objeto(Vector2 _posicion);

    virtual ~Objeto();

    virtual void actualizar(float dt);
    
    virtual void dibujar();

};

#endif /* OBJETO_HPP */
