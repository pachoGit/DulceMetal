/*
 * Ejemplo basico de simulacion de fisicas con Raylib y Box2D.
 * Presenta la manera basica de controlar las fisicas
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

// Data hecha para identificar al objeto
struct Info
{
    char nombre[20];
};

class MiEscuchadorColision : public b2ContactListener
{
  public:

    void BeginContact(b2Contact *contacto)
    {
        Info *info1 = (Info *) contacto->GetFixtureA()->GetBody()->GetUserData();
        Info *info2 = (Info *) contacto->GetFixtureB()->GetBody()->GetUserData();
        std::cout << "Objetos colisionando..." << info1->nombre << " - " << info2->nombre << std::endl;
    }
    
    void EndContact(b2Contact *contacto)
    {
        std::cout << "Objetos dejaron de colisionar..." << std::endl;
    }
};

int main()
{
    InitWindow(ANCHO, ALTO, "Raylib y Box2D - Procesar fisicas");

    SetTargetFPS(60);

    b2World mundo((b2Vec2) {0.f, 0.f});

    MiEscuchadorColision escuchador;

    mundo.SetContactListener(&escuchador);

    Rectangle jugador = {0.f, 100.f, 50.f, 50.f};
    float ang_jugador = 60.f;

    Rectangle jugador2 = {ANCHO - 60.f, 100.f, 50.f, 50.f};
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
    Info infojugador = {"Jugador 1"};
    fjugador->SetUserData(&infojugador);


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
    Info infojugador2 = {"Jugador 2"};
    fjugador2->SetUserData(&infojugador2);

    b2BodyDef defpiso;
    defpiso.position.Set(piso.x, piso.y);
    b2Body *fpiso = mundo.CreateBody(&defpiso);
    b2PolygonShape shapepiso;
    shapepiso.SetAsBox(piso.width, piso.height / 2.f);
    fpiso->CreateFixture(&shapepiso, 0.f);
    Info infopiso = {"Piso"};
    fpiso->SetUserData(&infopiso);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        mundo.Step(1.f / 60.f, 6, 2);

        float dt = GetFrameTime();

        if (IsKeyDown(KEY_SPACE))
        {
            fjugador->ApplyLinearImpulse((b2Vec2) {100.f, 0.f}, fjugador->GetWorldCenter(), true);
            fjugador2->ApplyLinearImpulse((b2Vec2) {-100.f, 0.f}, fjugador->GetWorldCenter(), true);
        }

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            ang_jugador += 0.5f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            ang_jugador -= 0.5f;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            jugador.x += std::sin(ang_jugador * DEG2RAD) * dt * 50.f;
            jugador.y -= std::cos(ang_jugador * DEG2RAD) * dt * 50.f;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            jugador.x -= std::sin(ang_jugador * DEG2RAD) * dt * 50.f;
            jugador.y += std::cos(ang_jugador * DEG2RAD) * dt * 50.f;
        }
        fjugador->SetTransform(b2Vec2(jugador.x, jugador.y), ang_jugador * DEG2RAD);

        jugador.x = fjugador->GetPosition().x;
        jugador.y = fjugador->GetPosition().y;
        ang_jugador = fjugador->GetAngle() * RAD2DEG;
        
        jugador2.x = fjugador2->GetPosition().x;
        jugador2.y = fjugador2->GetPosition().y;
        ang_jugador2 = fjugador2->GetAngle() * RAD2DEG;

        piso.x = fpiso->GetPosition().x;
        piso.y = fpiso->GetPosition().y;

        // Objeto 1
        DrawRectanglePro(arreglar_posicion(jugador), (Vector2) {jugador.width / 2.f, jugador.height / 2.f}, ang_jugador, RED);
        DrawText("Jugador1", jugador.x, jugador.y, 11, BLACK);

        // Objeto 2
        DrawRectanglePro(arreglar_posicion(jugador2), (Vector2) {jugador2.width / 2.f, jugador2.height / 2.f}, ang_jugador2, RED);
        DrawText("Jugador2", jugador2.x, jugador2.y, 11, BLACK);

        // Objeto 3
        DrawRectanglePro(arreglar_posicion(piso), (Vector2) {piso.width / 2.f, piso.height / 2.f}, ang_piso, GREEN);
        DrawText("Suelo", piso.x + (piso.width / 2.f), piso.y + (piso.height / 2.f), 15, BLACK);

        DrawText("Presiona la barra espaciadora para aplicar las fuerzas", 100.f, 50.f, 20, BLUE);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}


