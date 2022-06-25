#ifndef GESTORFISICAS_HPP
#define GESTORFISICAS_HPP

#include "FisicasDefs.hpp"
#include "FisicasCuerpo.hpp"
#include "FisicasColisionador.hpp"

class MiRayCast : public b2RayCastCallback
{
  public:

    b2Fixture *accesorio;
    b2Vec2 punto;
    b2Vec2 normal;
    float fraccion;
    
  public:

    MiRayCast() : accesorio(nullptr) {}
    
    float ReportFixture(b2Fixture *_accesorio, const b2Vec2 &_punto, const b2Vec2 &_normal, float _fraccion)
    {
        accesorio = _accesorio;
        punto = _punto;
        normal = _normal;
        fraccion = _fraccion;
        return fraccion;
    }
};

class GestorFisicas : public b2ContactListener
{
  private:
    
    b2World *mundoBox2D;

    b2Vec2 gravedad;

    int velocidadIteraciones;

    int posicionIteraciones;

    MiRayCast raycast;

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

    // Para lanzar rayos
    MiRayCast &rayCast(const b2Vec2 &inicio, const b2Vec2 &fin);

  private:

    bool DeberiaColisionar_ObstaculoConObjeto(b2Contact *contacto, b2Fixture *obstaculoAccesorio, b2Fixture *objetoAccesorio);

    bool DeberiaColisionar_ObjetoConObjeto(b2Contact *contacto, b2Fixture *objetoAccesorioA, b2Fixture *objetoAccesorioB);

    void ResolverColision_AutoConBala(Objeto *ovehiculo, Objeto *obala);

    void ResolverColision_AutoConEquipamiento(Objeto *ovehiculo, Objeto *oequipamiento);
};



#endif /* GESTORFISICAS_HPP */
