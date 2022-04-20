#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "Auto.hpp"

class Enemigo : public Auto
{
  public:

    // Ultima vez desde que disparo
    int tiempoDisparo;

  public:

    Enemigo(Vector2 _posicion, TipoAuto _tipo, unsigned _ID);

    ~Enemigo();

    void actualizar(float dt) override;
};


#endif /* ENEMIGO_HPP */
