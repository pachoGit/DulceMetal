#include "FisicasColisionador.hpp"

FisicasColisionador::FisicasColisionador(FisicasCuerpo *_fcuerpo, const FMaterial &_fmaterial, FGrupoColision miGrupo, FGrupoColision colisionarCon) :
        fcuerpo(_fcuerpo),
        fmaterial(_fmaterial)
{
    b2PolygonShape cubierta;
    Rectangle r = fcuerpo->objeto->espacio; // Posicion y dimension del objeto
    cubierta.SetAsBox(r.width * 0.5f, r.height * 0.5f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cubierta;
    fixtureDef.friction = fmaterial.friccion;
    fixtureDef.restitution = fmaterial.restitucion;
    fixtureDef.density = fmaterial.densidad;
    fixtureDef.filter.categoryBits = miGrupo;
    fixtureDef.filter.maskBits = colisionarCon;

    accesorioBox2D = fcuerpo->retCuerpoBox2D()->CreateFixture(&fixtureDef);
}

FisicasColisionador::~FisicasColisionador()
{
    if (accesorioBox2D != nullptr)
    {
        fcuerpo->retCuerpoBox2D()->DestroyFixture(accesorioBox2D);
        accesorioBox2D = nullptr;
    }
}

void FisicasColisionador::ingMaterial(const FMaterial &material)
{
    accesorioBox2D->SetFriction(material.friccion);
    accesorioBox2D->SetRestitution(material.restitucion);
    accesorioBox2D->SetDensity(material.densidad);
    fmaterial = material;
}

FMaterial FisicasColisionador::retMaterial() const
{
    return fmaterial;
}

b2Fixture *FisicasColisionador::retAccesorioBox2D() const
{
    return accesorioBox2D;
}
