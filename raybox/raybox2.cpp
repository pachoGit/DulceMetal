#include <iostream>
#include <raylib.h>
#include <Box2D.h>

#define ANCHO 840
#define ALTO  640

Rectangle arreglar_posicion(Rectangle r)
{
    Rectangle nuevo;
    nuevo.x = r.x + (r.width / 2.f);
    nuevo.y = r.y + (r.height / 2.f);
    nuevo.width = r.width;
    nuevo.height = r.height;
    return nuevo;
}

int main()
{
    InitWindow(ANCHO, ALTO, "Raylib y Box2D con angulos");

    SetTargetFPS(60);

    b2World mundo((b2Vec2) {0.f, 10.f});

    Rectangle jugador = {0.f, 0.f, 50.f, 50.f};
    float ang_jugador = 60.f;
    Rectangle piso = {0.f, ALTO - 50.f, ANCHO, 50.f};
    float ang_piso = 0.f;

    // FISICAS
    b2BodyDef defjugador;
    defjugador.type = b2_dynamicBody;
    defjugador.position.Set(jugador.x, jugador.y);
    defjugador.angle = ang_jugador * DEG2RAD;
    b2Body *fjugador = mundo.CreateBody(&defjugador);
    b2PolygonShape shapejugador;
    shapejugador.SetAsBox(jugador.width / 2.f, jugador.height / 2.f);
    b2FixtureDef fixjugador;
    fixjugador.shape = &shapejugador;
    fixjugador.density = 1.f;
    fixjugador.friction = 0.3f;
    fixjugador.restitution = 0.6f;
    fjugador->CreateFixture(&fixjugador);

    b2BodyDef defpiso;
    defpiso.position.Set(piso.x, piso.y);
    b2Body *fpiso = mundo.CreateBody(&defpiso);
    b2PolygonShape shapepiso;
    shapepiso.SetAsBox(piso.width, piso.height / 2.f);
    fpiso->CreateFixture(&shapepiso, 0.f);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        mundo.Step(1.f / 60.f, 6, 2);

        jugador.x = fjugador->GetPosition().x;
        jugador.y = fjugador->GetPosition().y;
        ang_jugador = fjugador->GetAngle() * RAD2DEG;
        
        piso.x = fpiso->GetPosition().x;
        piso.y = fpiso->GetPosition().y;

        DrawRectanglePro(arreglar_posicion(jugador), (Vector2) {jugador.width / 2.f, jugador.height / 2.f}, ang_jugador, RED);
        DrawRectanglePro(arreglar_posicion(piso), (Vector2) {piso.width / 2.f, piso.height / 2.f}, ang_piso, GREEN);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}


