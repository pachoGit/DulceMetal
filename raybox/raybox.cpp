#include <iostream>
#include <raylib.h>
#include <Box2D.h>

#define ANCHO 840
#define ALTO  640

int main()
{
    InitWindow(ANCHO, ALTO, "Raylib y Box2D");
    SetTargetFPS(60);
    b2World mundo((b2Vec2) {0.f, 10.f});

    Rectangle piso     = {0.f, ALTO - 50.f, ANCHO, 50.f};
    Rectangle jugador  = {100.f, 100.f, 50.f, 50.f};
    //Rectangle jugador  = {ANCHO - 50.f, 100.f, 50.f, 50.f};
    Rectangle objetivo = {ANCHO / 2.f, piso.y - 50.f, 50.f, 50.f}; // Sin fisicas
    
    // Configuracion de las fisicas
    // EL PISO
    b2BodyDef defpiso;
    defpiso.position.Set(piso.x, piso.y);
    b2Body *fpiso = mundo.CreateBody(&defpiso);
    b2PolygonShape shapepiso;
    shapepiso.SetAsBox(piso.width, piso.height / 2.f);
    fpiso->CreateFixture(&shapepiso, 0.f);

    // EL JUGADOR
    b2BodyDef defjugador;
    defjugador.type = b2_dynamicBody;
    defjugador.position.Set(jugador.x, jugador.y);
    b2Body *fjugador = mundo.CreateBody(&defjugador);
    b2PolygonShape shapejugador;
    shapejugador.SetAsBox(jugador.width / 2.f, jugador.height / 2.f);
    b2FixtureDef fixjugador;
    fixjugador.shape = &shapejugador;
    fixjugador.density = 1.f;
    fixjugador.friction = 0.3f;
    fixjugador.restitution = 0.6f;
    fjugador->CreateFixture(&fixjugador);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        mundo.Step(1.f / 60.f, 6, 2);

        piso.x = fpiso->GetPosition().x;
        piso.y = fpiso->GetPosition().y;
        
        jugador.x = fjugador->GetPosition().x;
        jugador.y = fjugador->GetPosition().y;

        DrawRectangleRec(piso, GREEN);
        DrawRectangleRec(jugador, RED);
        DrawRectangleRec(objetivo, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
