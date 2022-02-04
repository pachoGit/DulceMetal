/*
 * Ejemplo basico de simulacion de fisicas con Raylib y Box2D.
 * Presenta la manera basica de como es la colision entre objetos que
 * se mueven
 */

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
    InitWindow(ANCHO, ALTO, "Raylib y Box2D - Choque");

    SetTargetFPS(60);

    b2World mundo((b2Vec2) {0.f, 10.f});

    Rectangle jugador = {0.f, ALTO - 100.f, 50.f, 50.f};
    float ang_jugador = 60.f;
    Rectangle jugador2 = {ANCHO - 60.f, ALTO - 100.f, 50.f, 50.f};
    float ang_jugador2 = 60.f;
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
    fixjugador.density = 0.2f;
    fixjugador.friction = 0.3f;
    fixjugador.restitution = 0.6f;
    fjugador->CreateFixture(&fixjugador);

    b2BodyDef defjugador2;
    defjugador2.type = b2_dynamicBody;
    defjugador2.position.Set(jugador2.x, jugador2.y);
    defjugador2.angle = ang_jugador2 * DEG2RAD;
    b2Body *fjugador2 = mundo.CreateBody(&defjugador2);
    b2FixtureDef fixjugador2;
    fixjugador2.shape = &shapejugador;
    fixjugador2.density = 0.5f;
    fixjugador2.friction = 0.1f;
    fixjugador2.restitution = 0.9f;
    fjugador2->CreateFixture(&fixjugador2);

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

        if (IsKeyDown(KEY_SPACE))
        {
            fjugador->ApplyLinearImpulse((b2Vec2) {100.f, 0.f}, fjugador->GetWorldCenter(), true);
            fjugador2->ApplyLinearImpulse((b2Vec2) {-100.f, 0.f}, fjugador->GetWorldCenter(), true);
        }

        jugador.x = fjugador->GetPosition().x;
        jugador.y = fjugador->GetPosition().y;
        ang_jugador = fjugador->GetAngle() * RAD2DEG;
        
        jugador2.x = fjugador2->GetPosition().x;
        jugador2.y = fjugador2->GetPosition().y;
        ang_jugador2 = fjugador2->GetAngle() * RAD2DEG;

        piso.x = fpiso->GetPosition().x;
        piso.y = fpiso->GetPosition().y;

        DrawRectanglePro(arreglar_posicion(jugador), (Vector2) {jugador.width / 2.f, jugador.height / 2.f}, ang_jugador, RED);
        DrawRectanglePro(arreglar_posicion(jugador2), (Vector2) {jugador2.width / 2.f, jugador2.height / 2.f}, ang_jugador2, RED);
        DrawRectanglePro(arreglar_posicion(piso), (Vector2) {piso.width / 2.f, piso.height / 2.f}, ang_piso, GREEN);
        
        DrawText("Presiona la barra espaciadora para aplicar las fuerzas", 100.f, 50.f, 20, BLUE);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}


