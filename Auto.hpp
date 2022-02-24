#ifndef AUTO_HPP
#define AUTO_HPP

#include <vector>

#include "Objeto.hpp"
#include "Bala.hpp"

class Auto : public Objeto
{
  public:

    int vida;

    std::vector<Bala *> balas;

  public:

    Auto(Vector2 _posicion);

    ~Auto();

    void actualizar(float dt);

    void dibujar();

    void generarFisicasIniciales();

    void disparar(/* TipoBala bala*/);

};


#endif /* AUTO_HPP */
