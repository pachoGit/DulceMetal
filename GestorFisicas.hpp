#ifndef GESTORFISICAS_HPP
#define GESTORFISICAS_HPP

#include "FisicasDefs.hpp"
#include "FisicasCuerpo.hpp"
#include "FisicasColisionador.hpp"

class GestorFisicas : public b2ContactListener
{
  private:
    
    b2World *mundoBox2D;

    b2Vec2 gravedad;

  public:

    std::vector<FisicasCuerpo *> cuerposBox2D;

  public:

    GestorFisicas();

    ~GestorFisicas();

    FisicasCuerpo *crearCuerpoBox2D(Objeto *objeto, FCuerpoBanderas fbanderas);

    FisicasCuerpo *crearCuerpoBox2D(Objeto *objeto, FCuerpoBanderas fbanderas, const FMaterial &material);

    void destruirCuerpoBox2D(FisicasCuerpo *cuerpo);
};


#endif /* GESTORFISICAS_HPP */
