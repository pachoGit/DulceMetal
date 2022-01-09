#ifndef RECTCOLISION_HPP
#define RECTCOLISION_HPP

#include <raylib.h>

class RectColision
{
  public:
    
    // Ancho y alto del rectangulo
    float ancho, alto;

    // Puntos del rectangulo
    Vector2 arribaIzquierda;
    Vector2 arribaDerecha;
    Vector2 abajoIzquierda;
    Vector2 abajoDerecha;

    // Angulo de rotacion del rectangulo
    float angulo;

    Vector2 r1;
    Vector2 r2;
    Vector2 r3;
    Vector2 r4;

  public:

    RectColision(Rectangle r, float _angulo = 0.f);

    ~RectColision();

    void dibujar();

};


#endif /* RECTCOLISION_HPP */
