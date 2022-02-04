#include "GestorFisicas.hpp"

#include <algorithm>

GestorFisicas::GestorFisicas()
{
    gravedad.Set(0.f, 0.f);
    mundoBox2D = new b2World(gravedad);
    mundoBox2D->SetContactListener(this);
}

GestorFisicas::~GestorFisicas()
{
    if (mundoBox2D)
    {
        delete mundoBox2D;
        mundoBox2D = nullptr;
    }
    for (auto &fcuerpo : cuerposBox2D)
        delete fcuerpo;
}

FisicasCuerpo *GestorFisicas::crearCuerpoBox2D(Objeto *objeto, FCuerpoBanderas fbanderas)
{
    FisicasCuerpo *nuevo = new FisicasCuerpo(objeto, fbanderas);
    cuerposBox2D.push_back(nuevo);
    return nuevo;
}

FisicasCuerpo *GestorFisicas::crearCuerpoBox2D(Objeto *objeto, FCuerpoBanderas fbanderas, const FMaterial &material)
{
    FisicasCuerpo *nuevo = crearCuerpoBox2D(objeto, fbanderas);
    if (nuevo)
        nuevo->agregarColisionador(material);
    return nuevo;
}


void GestorFisicas::destruirCuerpoBox2D(FisicasCuerpo *cuerpo)
{
    if (!cuerpo)
        return;
    cuerposBox2D.erase(std::remove(cuerposBox2D.begin(), cuerposBox2D.end(), cuerpo), cuerposBox2D.end());
    delete cuerpo;
}
