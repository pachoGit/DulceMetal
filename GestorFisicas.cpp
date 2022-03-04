#include "GestorFisicas.hpp"
#include "ObjetoAyudas.hpp"
#include "Config.hpp"

#include <box2d/b2_collision.h>
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
    FisicasCuerpo *fcuerpo1 = (FisicasCuerpo *) contacto->GetFixtureA()->GetBody()->GetUserData().pointer;
    Objeto *o1 = fcuerpo1->objeto;
    FisicasCuerpo *fcuerpo2 = (FisicasCuerpo *) contacto->GetFixtureB()->GetBody()->GetUserData().pointer;
    Objeto *o2 = fcuerpo2->objeto;

    std::cout << "Colisionando: " << o1->nombre << " - " << o2->nombre << std::endl;

    if (contacto->IsTouching())
    {
        std::cout << "Colisionando: " << std::endl;
        int npuntosContacto = contacto->GetManifold()->pointCount;
        b2WorldManifold puntosMundiales;

        contacto->GetWorldManifold(&puntosMundiales);
        std::cout << "Puntos de Contacto Mundiales..." << std::endl;
        for (int i = 0; i < npuntosContacto; ++i)
            std::cout << "( " << puntosMundiales.points[i].x << ", " << puntosMundiales.points[i].y << ")" << std::endl;
    }
    o1->habilitarProcesadoFisicas = true;
    o2->habilitarProcesadoFisicas = true;
}

void GestorFisicas::EndContact(b2Contact *contacto)
{
    FisicasCuerpo *fcuerpo1 = (FisicasCuerpo *) contacto->GetFixtureA()->GetBody()->GetUserData().pointer;
    Objeto *o1 = fcuerpo1->objeto;
    FisicasCuerpo *fcuerpo2 = (FisicasCuerpo *) contacto->GetFixtureB()->GetBody()->GetUserData().pointer;
    Objeto *o2 = fcuerpo2->objeto;

    std::cout << "Dejo de Colisionar: " << o1->nombre << " - " << o2->nombre << std::endl;

    // Solo habilitar las teclas para el jugador
    if (o1->esClaseJugador())
        o1->habilitarProcesadoFisicas = false;
    if (o2->esClaseJugador())
        o2->habilitarProcesadoFisicas = false;
}

void GestorFisicas::PreSolve(b2Contact *contacto, const b2Manifold *colector)
{
}

void GestorFisicas::PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso)
{
}
