#ifndef BARRAVIDA_HPP
#define BARRAVIDA_HPP

#include "Objeto.hpp"

#include <raylib.h>

class BarraVida
{
  private:

    // Auto al que le pertenece la barra de vida
    Objeto *vehiculo;

  public:
    
    // Posicion y dimension de la barra de vida
    Rectangle espacio;
    
    // Anchura actual de la barra de vida
    int anchoBarraVida;

    // Posicion actual del objeto
    Vector2 posicion;

  public:

    BarraVida(Objeto *_vehiculo);

    ~BarraVida();

    void actualizar(float dt);

    void dibujar();
};

#endif /* BARRAVIDA_HPP */
