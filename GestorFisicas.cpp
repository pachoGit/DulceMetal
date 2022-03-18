#include "GestorFisicas.hpp"
#include "ObjetoAyudas.hpp"
#include "Config.hpp"
#include "Convertir.hpp"

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

    if (contacto->IsTouching())
    {
        o1->habilitarProcesadoFisicas = true;
        o2->habilitarProcesadoFisicas = true;
        std::cout << "Colisionando: " << o1->nombre << " - " << o2->nombre << std::endl;
        int npuntosContacto = contacto->GetManifold()->pointCount;
        b2WorldManifold puntosMundiales;

        contacto->GetWorldManifold(&puntosMundiales);
        std::cout << "Puntos de Contacto Mundiales..." << std::endl;
        for (int i = 0; i < npuntosContacto; ++i)
        {
            Rectangle r = {Convertir::MetrosEnPixeles(puntosMundiales.points[i].x), Convertir::MetrosEnPixeles(puntosMundiales.points[i].y), 10.f, 10.f};
            DrawRectangleRec(r, GREEN);
            std::cout << "( " << puntosMundiales.points[i].x << ", " << puntosMundiales.points[i].y << ")" << std::endl;
        }
    }
}

void GestorFisicas::EndContact(b2Contact *contacto)
{
}

void GestorFisicas::PreSolve(b2Contact *contacto, const b2Manifold *colector)
{
    Objeto *o1 = retObjetoDeFixture(contacto->GetFixtureA());
    Objeto *o2 = retObjetoDeFixture(contacto->GetFixtureB());

    if (o1 == nullptr || o2 == nullptr)
        return;
    
    // Verificar que solo una vez debe llegar aqui :D
    if (o1->esClaseBala() && (o2->esClaseJugador() || o2->esClaseAuto()))
    {
        // Generar el danio
        Auto *vehiculo = ObjetoEnAuto(o2);
        Bala *bala = ObjetoEnBala(o1);
        int efecto = bala->efecto;
        vehiculo->vida -= efecto;
        bala->explotar();
    }
    if (o2->esClaseBala() && (o1->esClaseJugador() || o1->esClaseAuto()))
    {
        // Generar el danio
        Auto *vehiculo = ObjetoEnAuto(o1);
        Bala *bala = ObjetoEnBala(o2);
        int efecto = bala->efecto;
        vehiculo->vida -= efecto;
        bala->explotar();
    }
}

void GestorFisicas::PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso)
{
    
}
