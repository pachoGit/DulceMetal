#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <vector>

#include "Auto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"

class Jugador : public Auto
{
  public:

    Jugador(Vector2 _posicion);

    ~Jugador();

    void actualizar(float dt) override;

    void procesarFisicas() override;

    void dibujar() override;

    void disparar(/* TipoBala bala*/);

    void generarFisicasIniciales() override;
};


#endif /* JUGADOR_HPP */
