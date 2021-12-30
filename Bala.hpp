#ifndef BALA_HPP
#define BALA_HPP

#include "Objeto.hpp"

class Bala : public Objeto
{
    float velocidad;

  public:

    Bala(Vector2 _posicion);

    ~Bala();

    void actualizar(float dt);

    void dibujar();

};


#endif /* BALA_HPP */
