#include <raylib.h>

#include "Motor.hpp"
#include "GestorSprites.hpp"

int main()
{
    InitWindow(1200, 840, "Dulce Metal v1.0");

    SetTargetFPS(60);

    Motor motor = Motor::retMotor();
    motor.iniciarModulos();

    motor.retGestorTexturas()->cargarTexturas();
    motor.retGestorSprites()->generarSprites();

    Texture2D t = motor.retGestorTexturas()->retTextura("principal");

    //Sprite *s3 = CrearSprite("nombreSprite", "nombreTextura");

    /*
    Sprite *s1 = motor.retGestorSprites()->retSprite("auto1");
    Sprite *s2 = motor.retGestorSprites()->retSprite("auto1");
    */
    
    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Esta es la primera ventana", 190, 200, 20, RED);
        DrawTexture(t, 0, 0, RAYWHITE);

        /*
        s1->dibujar();
        s2->dibujar((Vector2) {50.f, 50.f});
        */
        
        EndDrawing();
    }

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
