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

    int velocidadIteraciones;

    int posicionIteraciones;

  public:

    std::vector<FisicasCuerpo *> cuerposBox2D;

  public:

    GestorFisicas();

    ~GestorFisicas();

    // Cuerpos Box2D
    b2Body *crearCuerpoBox2D(const b2BodyDef *def);

    void destruirCuerpoBox2D(b2Body *cuerpo);

    // Cuerpos definidos por mi :D
    FisicasCuerpo *crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas);

    FisicasCuerpo *crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas, const FMaterial &material,
                                FGrupoColision miGrupo, FGrupoColision colisionarCon);

    void destruirFCuerpo(FisicasCuerpo *cuerpo);

    void actualizarFisicas();

    void limpiarFuerzas();

    void BeginContact(b2Contact *contacto) override;

    void EndContact(b2Contact *contacto) override;

    void PreSolve(b2Contact *contacto, const b2Manifold *oldManifold) override;
    
    void PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso) override;
};


#endif /* GESTORFISICAS_HPP */
