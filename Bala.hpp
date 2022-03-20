#ifndef BALA_HPP
#define BALA_HPP

#include "Objeto.hpp"

enum TipoBala
{
    BALA_BASICA,
    BALA_FUEGO,
    BALA_ELECTRICO,
    BALA_AURA,
    BALA_FURIA,
    BALA_FLOREAL
};

class Bala : public Objeto
{
  public:

    // Cantidad de vida que puede quitar
    int efecto;

    TipoBala tipo;

  public:

    Bala(Vector2 _posicion, TipoBala tipo);

    ~Bala();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void generarFisicasIniciales();
    
    void explotar();
};


#endif /* BALA_HPP */
