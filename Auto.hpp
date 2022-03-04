#ifndef AUTO_HPP
#define AUTO_HPP

#include <vector>

#include "Objeto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"

class Auto : public Objeto
{
  public:

    // Cantidad de vida actual del auto
    int vida;

    // Textura de la barra de vida
    BarraVida *barraVida;

    // Lista de balas que esta lanzando el auto
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
