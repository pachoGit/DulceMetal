#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <raylib.h>

class Objeto
{
  public:

    // Espacio actual ocupado por el objeto en la ventana del juego
    Rectangle espacio;

    // Posicion actual del objeto
    Vector2 posicion;
    
    // Rectangulo de colision
    //Rectangle colision;

    // Angulo de rotacion del objeto
    float angulo;

  public:
    
    Objeto(Vector2 _posicion);

    virtual ~Objeto();

    virtual void actualizar();
    
    virtual void dibujar();

};

#endif /* OBJETO_HPP */
