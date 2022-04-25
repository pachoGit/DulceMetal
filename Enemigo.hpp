#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "Auto.hpp"

class Enemigo : public Auto
{
  private:
    
    // Rango de vicion del auto
    Rectangle rango;

  public:

    // Ultima vez desde que disparo
    int tiempoDisparo;

  public:

    Enemigo(Vector2 _posicion, TipoAuto _tipo, unsigned _ID);

    ~Enemigo();

    void actualizar(float dt) override;

    void dibujar() override;
};


#endif /* ENEMIGO_HPP */
