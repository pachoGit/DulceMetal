#include <iostream>

#include <raylib.h>

#include "Motor.hpp"
#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"

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

    //Texture2D t = motor.retGestorTexturas()->retTextura("principal");

    //Sprite *s3 = CrearSprite("nombreSprite", "nombreTextura");

    Sprite *s1 = motor.retGestorSprites()->retSprite("auto1");
    std::cout << "Espacio de Sprite 1: ";
    verRect(s1->espacio);

    Sprite *s2 = motor.retGestorSprites()->retSprite("auto1");
    std::cout << "Espacio de Sprite 2: ";
    verRect(s2->espacio);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Esta es la primera ventana", 190, 200, 20, RED);
        //DrawTexture(t, 0, 0, RAYWHITE);

        s1->dibujar();
        s2->dibujar((Vector2) {50.f, 50.f});
        
        EndDrawing();
    }

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
