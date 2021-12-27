#include <iostream>

#include <raylib.h>

#include "Motor.hpp"
#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"
#include "Objeto.hpp"

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

    Objeto *o1 = new Objeto((Vector2){0.f, 0.f});

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Esta es la primera ventana", 190, 200, 20, RED);
        o1->actualizar();
        o1->dibujar();

        EndDrawing();
    }

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
