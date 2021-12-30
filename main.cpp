#include <iostream>

#include <raylib.h>

#include "Motor.hpp"
#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"
#include "Objeto.hpp"
#include "Auto.hpp"
#include "Jugador.hpp"

void verRect(Rectangle rect)
{
    std::cout << "[" << rect.x << ", " << rect.y <<  ", " << rect.width << ", " << rect.height << "]" << std::endl;
}

int main()
{
    InitWindow(1200, 840, "Dulce Metal v1.0");

    SetTargetFPS(60);

    Motor &motor = Motor::retMotor();
    motor.iniciarModulos();

    motor.retGestorTexturas()->cargarTexturas();
    motor.retGestorSprites()->generarSprites();

    Texture2D t = motor.retGestorTexturas()->retTextura("principal");

    Auto *a1 = new Auto((Vector2) {0.f, 0.f});
    a1->angulo = 120.f;
    Jugador *a2 = new Jugador((Vector2) {100.f, 100.f});

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        float dt = GetFrameTime();
        DrawText("Esta es la primera ventana", 190, 200, 20, RED);
        a1->actualizar(dt);
        a2->actualizar(dt);

        a1->dibujar();
        a2->dibujar();

        EndDrawing();
    }

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
