#ifndef BALA_HPP
#define BALA_HPP

#include "Objeto.hpp"

enum TipoBala
{
    BALA_BASICA,
    BALA_MISIL
};

class Bala : public Objeto
{
  public:

    // Cantidad de vida que puede quitar
    int efecto;

  public:

    Bala(Vector2 _posicion, const std::string &_nombreBala);

    ~Bala();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void generarFisicasIniciales();
    
    void explotar();
};


#endif /* BALA_HPP */
