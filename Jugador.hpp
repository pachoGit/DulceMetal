#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <vector>

#include "Objeto.hpp"
#include "Bala.hpp"

class Jugador : public Objeto
{
  public:

    int vida;

    std::vector<Bala *> balas;

  public:

    Jugador(Vector2 _posicion);

    ~Jugador();

    void actualizar(float dt);

    void dibujar();

    void disparar(/* TipoBala bala*/);

    void generarFisicasIniciales();
};


#endif /* JUGADOR_HPP */
