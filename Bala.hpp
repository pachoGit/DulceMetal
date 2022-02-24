#ifndef BALA_HPP
#define BALA_HPP

#include "Objeto.hpp"

class Bala : public Objeto
{
  public:

    Bala(Vector2 _posicion);

    ~Bala();

    void actualizar(float dt);

    void dibujar();

    void generarFisicasIniciales();
};


#endif /* BALA_HPP */
