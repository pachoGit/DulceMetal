/*
 * Ejemplo basico de simulacion de fisicas con Raylib y Box2D.
 * Presenta la manera basica de coincidir los elementos de raylib con
 * los de Box2D con angulos de rotacion
 */

#include <iostream>
#include <raylib.h>
#include <Box2D.h>

#define ANCHO 840
#define ALTO  640

/*
 * Cuando se usa alguna funcion de renderizado con rotacion (funciones que terminan en `Pro`),
 * Raylib, toma como punto de rotacion y de origen la posicion que enviamos (en cualquiera de dichas funciones).
 * Eso es una molestia, por que imagine que desea dibujar un rectangulo de 50x50 en la posicion
 * (0, 0) con un rotacion de 20 grados y el punto de rotacion en el centro del rectangulo
 * LLamando a la funcion seria: DrawRectanglePro(rectangulo, {ancho / 2.f, alto / 2.f}, 20, BLUE)
 * Lo que normalmente se esperaria es que se ubique en primer lugar el rectangulo en la
 * posicion (0, 0) y a partir de ahi se gire, pero se sorprendera que en realidad eso no sucede,
 * vera que tiene una parte del rectangulo en la pantalla.
 * Lo que sucede es que el punto que enviamos (el centro del rectangulo) se posiciona en la
 * ubicacion (0, 0) y a partir de ahi la figura se gira.
 * Esto es un problema, por que Box2D no funciona de esa manera, Box2D ubica y gira los
 * figuras de la primera forma que explique, lo que ocasiona un incompatibilidad al querer
 * hacer coincidir la textura de Raylib con el cubrimiento de Box2D
 * Por lo que un objeto ubicado por Raylib en la posicion (0, 0) con rotacion de 20 grados
 * no estara en el mismo lugar que un objeto de Box2D con las mismas caracteristicas
 * Lo que hago simplemente es modificar la posicion del rectangulo para que coincida con
 * la posicion de Box2D
 */
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
    InitWindow(ANCHO, ALTO, "Raylib y Box2D con angulos de rotacion");

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

        // Puede quitar la funcion arreglar_posicion para notar la diferencia
        DrawRectanglePro(arreglar_posicion(jugador), (Vector2) {jugador.width / 2.f, jugador.height / 2.f}, ang_jugador, RED);
        DrawRectanglePro(arreglar_posicion(piso), (Vector2) {piso.width / 2.f, piso.height / 2.f}, ang_piso, GREEN);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}


