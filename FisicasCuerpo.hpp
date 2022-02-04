#ifndef FISICASCUERPO_HPP
#define FISICASCUERPO_HPP

#include "FisicasDefs.hpp"
#include "FisicasColisionador.hpp"
#include "Objeto.hpp"

class FisicasColisionador;

class FisicasCuerpo
{
  private:
    
    // Representacion de las fisicas de Box2D
    b2Body *cuerpoBox2D;

  public:
    
    Objeto *objeto; // Objeto al que le pertenecen las fisicas

    // Propiedades del cuerpo
    FCuerpoBanderas fbanderas;
    
    // La forma (shape) y el accesorio (fixture) del cuerpo
    FisicasColisionador *fcolisionador;

  public:
    
    FisicasCuerpo(Objeto *_objeto, FCuerpoBanderas _fbanderas);

    ~FisicasCuerpo();

    b2Body *retCuerpoBox2D() const;

    // Obtener la posicion del objeto de fisicas
    Vector2 retPosicion() const;

    // Obtener el angulo en grados
    float retAngulo() const;

    FisicasColisionador *agregarColisionador(const FMaterial &material);
    
  private:
    
    inline bool checkBanderas(FCuerpoBanderas bandera) const;
};

#endif /* FISICASCUERPO_HPP */
