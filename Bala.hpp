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

  private:

    // Distancia maxima que la bala puede recorrer (en metros)
    float distanciaMaxima;

    // La posicion anterior de la bala, necesario para ir calculando la distancia
    // que esta recorriendo la bala
    Vector2 posicionAnterior;

    // Distancia (en metros) que ha recorrido la bala
    float distanciaRecorrida;

  public:

    Bala(Vector2 _posicion, TipoBala tipo);

    ~Bala();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();
    
    void explotar();

    float retDistanciaRecorrida() const;
};


#endif /* BALA_HPP */
