/*
 * Ejemplo basico de simulacion de fisicas con Raylib y Box2D.
 * Presenta la manera basica de controlar las fisicas
 */

#include <iostream>
#include <string>
#include <raylib.h>
#include <Box2D.h>

#include "Objeto.hpp"
#include "FisicasCuerpo.hpp"

#define ANCHO 840
#define ALTO  640

class MiEscuchadorColision : public b2ContactListener
{
  public:

    void BeginContact(b2Contact *contacto)
    {
        Objeto *o1 = (Objeto * ) contacto->GetFixtureA()->GetBody()->GetUserData();
        Objeto *o2 = (Objeto * ) contacto->GetFixtureB()->GetBody()->GetUserData();

        std::cout << "Objetos colisionando..." << o1->nombre << " - " << o2->nombre << std::endl;
        if (o1->nombre == "Jugador")
            o1->habilitarControles = false;
        if (o2->nombre == "Jugador")
            o2->habilitarControles = false;
        if (contacto->IsTouching())
            std::cout << "Objetos SIGUEN colisionando..." << std::endl;
    }
    
    void EndContact(b2Contact *contacto)
    {
        std::cout << "Objetos dejaron de colisionar..." << std::endl;
        Objeto *o1 = (Objeto * ) contacto->GetFixtureA()->GetBody()->GetUserData();
        Objeto *o2 = (Objeto * ) contacto->GetFixtureB()->GetBody()->GetUserData();
        if (o1->nombre == "Jugador")
            o1->habilitarControles = true;
        if (o2->nombre == "Jugador")
            o2->habilitarControles = true;
    }

    void PreSolve(b2Contact *contacto, const b2Manifold *colector)
    {
        std::cout << "Entro a la funcion PreSolve" << std::endl;
        contacto->SetEnabled(true);
    }
    
    void PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso)
    {
        std::cout << "Entro a la funcion PostSolve" << std::endl;
        b2Fixture *accesorioA = contacto->GetFixtureA();
        b2Fixture *accesorioB = contacto->GetFixtureB();
        
        b2Body *fcuerpoA = accesorioA->GetBody();
        b2Body *fcuerpoB = accesorioB->GetBody();
        
        b2Manifold *colector = contacto->GetManifold();

        /*
        fcuerpoA->ApplyLinearImpulse(b2Vec2(impulso->normalImpulses[0], impulso->normalImpulses[0]),
                                     colector->localPoint, true);
        fcuerpoB->ApplyLinearImpulse(b2Vec2(impulso->normalImpulses[0], impulso->normalImpulses[0]),
                                     colector->localPoint, true);
        */
        /*
        fcuerpoA->ApplyLinearImpulse(b2Vec2(10.f, 10.f), fcuerpoA->GetLocalCenter(), true);
        fcuerpoB->ApplyLinearImpulse(b2Vec2(30.f, 30.f), fcuerpoB->GetLocalCenter(), true);
        */
        fcuerpoA->ApplyLinearImpulse(b2Vec2(10.f, 10.f), colector->localPoint, true);
        fcuerpoB->ApplyLinearImpulse(b2Vec2(30.f, 30.f), colector->localPoint, true);
    }
};

int main()
{
    InitWindow(ANCHO, ALTO, "Raylib y Box2D - Procesar fisicas");

    SetTargetFPS(60);

    b2World mundo((b2Vec2) {0.f, 0.f});
    MiEscuchadorColision escuchador;
    mundo.SetContactListener(&escuchador);

    // Iniciamos objetos
    Objeto jugador( (Rectangle) {0.f, 100.f, 30.f, 50.f},          (Vector2) {0.f, 100.f},          60.f);
    jugador.agregarFisicas(FMaterial(0.2f, 0.3f, 0.6f), b2_dynamicBody, &mundo);
    jugador.habilitarControles = true;
    jugador.nombre = "Jugador";

    Objeto objetivo((Rectangle) {ANCHO - 250.f, 100.f, 50.f, 50.f}, (Vector2) {ANCHO - 250.f, 100.f}, 60.f);
    objetivo.agregarFisicas(FMaterial(0.5f, 0.1f, 0.8f), b2_dynamicBody, &mundo);
    objetivo.nombre = "Objetivo";

    Objeto piso(    (Rectangle) {0.f, ALTO - 50.f, ANCHO, 50.f},   (Vector2) {0.f, ALTO - 50.f},    0.f);
    piso.agregarFisicas(FMaterial(0.5f, 0.1f, 0.8f), b2_staticBody, &mundo);
    piso.color = GREEN;
    piso.nombre = "Piso";
    
    // Objeto muro((Rectangle) {50.f, 50.f, 50.f, 50.f}, (Vector2) {100.f, 50.f}, 0.f);
    Objeto muro((Rectangle) {50.f, 50.f, 50.f, 50.f}, (Vector2) {100.f, 50.f}, 0.f);
    muro.agregarFisicas(FMaterial(1.f, 0.f, 0.f), b2_staticBody, &mundo);
    muro.color = GREEN;
    muro.nombre = "Muro";

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        mundo.ClearForces();
        mundo.Step(1.f / 60.f, 6, 2);
        float dt = GetFrameTime();
        jugador.actualizar(dt);
        objetivo.actualizar(dt);
        piso.actualizar(dt);
        muro.actualizar(dt);

        jugador.dibujar();
        objetivo.dibujar();
        piso.dibujar();
        muro.dibujar();

        EndDrawing();
    }
    
    jugador.Destruir(&mundo);
    objetivo.Destruir(&mundo);
    piso.Destruir(&mundo);
    muro.Destruir(&mundo);

    CloseWindow();
    
    return 0;
}


