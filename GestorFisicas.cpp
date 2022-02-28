#include "GestorFisicas.hpp"
#include "ObjetoAyudas.hpp"
#include "Config.hpp"

#include <algorithm>
#include <iostream>

GestorFisicas::GestorFisicas()
{
    gravedad.Set(0.f, 0.f);
    mundoBox2D = new b2World(gravedad);
    mundoBox2D->SetContactListener(this);
    velocidadIteraciones = Config::VELOCIDAD_ITER;
    posicionIteraciones = Config::POSICION_ITER;
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

b2Body *GestorFisicas::crearCuerpoBox2D(const b2BodyDef *def)
{
    return mundoBox2D->CreateBody(def);
}

void GestorFisicas::destruirCuerpoBox2D(b2Body *cuerpo)
{
    mundoBox2D->DestroyBody(cuerpo);
}

FisicasCuerpo *GestorFisicas::crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas)
{
    FisicasCuerpo *nuevo = new FisicasCuerpo(objeto, fbanderas);
    cuerposBox2D.push_back(nuevo);
    return nuevo;
}

FisicasCuerpo *GestorFisicas::crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas, const FMaterial &material)
{
    FisicasCuerpo *nuevo = crearFCuerpo(objeto, fbanderas);
    /*
    if (nuevo)
        nuevo->agregarColisionador(material);
    */
    return nuevo;
}

void GestorFisicas::destruirFCuerpo(FisicasCuerpo *cuerpo)
{
    if (!cuerpo)
        return;
    //cuerposBox2D.erase(std::remove(cuerposBox2D.begin(), cuerposBox2D.end(), cuerpo), cuerposBox2D.end());
    delete cuerpo;
}

void GestorFisicas::actualizarFisicas()
{
    mundoBox2D->Step(1.f / 60.f, velocidadIteraciones, posicionIteraciones);
}

void GestorFisicas::limpiarFuerzas()
{
    mundoBox2D->ClearForces();
}

void GestorFisicas::BeginContact(b2Contact *contacto)
{
    Objeto *o1 = (Objeto *) contacto->GetFixtureA()->GetBody()->GetUserData();
    Objeto *o2 = (Objeto *) contacto->GetFixtureB()->GetBody()->GetUserData();
    
    std::cout << "Colisionando: " << o1->nombre << " - " << o2->nombre << std::endl;

    o1->habilitarProcesadoFisicas = true;
    o2->habilitarProcesadoFisicas = true;
}

void GestorFisicas::EndContact(b2Contact *contacto)
{
    std::cout << "Algunos objetos DEJARON DE colisionaron :D" << std::endl;
    Objeto *o1 = (Objeto *) contacto->GetFixtureA()->GetBody()->GetUserData();
    Objeto *o2 = (Objeto *) contacto->GetFixtureB()->GetBody()->GetUserData();

    // Solo habilitar las teclas para el jugador
    if (o1->esClaseJugador())
        o1->habilitarProcesadoFisicas = false;
    if (o2->esClaseJugador())
        o2->habilitarProcesadoFisicas = false;

    /*
    o1->habilitarProcesadoFisicas = false;
    o2->habilitarProcesadoFisicas = false;
    */
}

void GestorFisicas::PreSolve(b2Contact *contacto, const b2Manifold *colector)
{
    //std::cout << "PreSolve..." << std::endl;
    Objeto *o1 = (Objeto *) contacto->GetFixtureA()->GetBody()->GetUserData();
    Objeto *o2 = (Objeto *) contacto->GetFixtureB()->GetBody()->GetUserData();

    contacto->SetEnabled(true);
}

void GestorFisicas::PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso)
{
    //std::cout << "PostSolve..." << std::endl;

    b2Body *fcuerpoA = contacto->GetFixtureA()->GetBody();
    b2Body *fcuerpoB = contacto->GetFixtureB()->GetBody();
    
    Objeto *o1 = (Objeto *) contacto->GetFixtureA()->GetBody()->GetUserData();
    Objeto *o2 = (Objeto *) contacto->GetFixtureB()->GetBody()->GetUserData();
}
