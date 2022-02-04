#include "FisicasColisionador.hpp"
#include <Box2D.h>
#include <stdarg.h>
#include <stdint.h>


FisicasColisionador::FisicasColisionador(FisicasCuerpo *_fcuerpo, const FMaterial &_fmaterial) :
        fcuerpo(_fcuerpo),
        fmaterial(_fmaterial)
{
    b2PolygonShape cubierta;
    cubierta.SetAsBox(fcuerpo->objeto->espacio.width / 2.f, fcuerpo->objeto->espacio.height / 2.f);

    b2FixtureDef fixtureDef;
    //fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    fixtureDef.shape = &cubierta;
    //fixtureDef.userData.pointer = (uintptr_t) this;
    fixtureDef.friction = fmaterial.friccion;
    fixtureDef.restitution = fmaterial.restitucion;
    fixtureDef.density = fmaterial.densidad;

    accesorioBox2D = fcuerpo->retCuerpoBox2D()->CreateFixture(&fixtureDef);
}

FisicasColisionador::~FisicasColisionador()
{
    if (accesorioBox2D)
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
