#ifndef MURO_HPP
#define MURO_HPP

#include "Objeto.hpp"

class Muro : public Objeto
{
  public:
    
    Muro(Vector2 _posicion);

    ~Muro();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void generarFisicasIniciales();

};


#endif /* MURO_HPP */
