#include <iostream>

#include <raylib.h>
#include <Box2D.h>

#include "Motor.hpp"
#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"
#include "GestorFisicas.hpp"
#include "Objeto.hpp"
#include "Auto.hpp"
#include "Jugador.hpp"
#include "Muro.hpp"

#include "Convertir.hpp"
#include "Config.hpp"
#include "Animacion.hpp"

#include <array>

int main()
{
    // InitWindow(1200, 840, "Dulce Metal v1.0");
    InitWindow(Convertir::MetrosEnPixeles(Config::DIM_VENTANA.x), Convertir::MetrosEnPixeles(Config::DIM_VENTANA.y), "Dulce Metal v1.0");

    SetTargetFPS(60);

    Motor &motor = Motor::retMotor();
    motor.iniciarModulos();

    motor.retGestorTexturas()->cargarTexturas();
    motor.retGestorSprites()->generarSprites();
    motor.retGestorSprites()->generarSpritesAnimados();

    Auto *a1 = new Auto((Vector2) {0.f, 5.f});
    a1->angulo = 120.f;

    Jugador *a2 = new Jugador((Vector2) {5.f, 10.f});
    Muro *m1 = new Muro((Vector2) {15.f, 10.f});

    Animacion *b1 = new Animacion((Vector2) {100.f, 10.f});

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);
        motor.retGestorFisicas()->actualizarFisicas();

        float dt = GetFrameTime();

        a1->actualizar(dt);
        a2->actualizar(dt);
        m1->actualizar(dt);
        b1->actualizar(dt);

        a1->dibujar();
        a2->dibujar();
        m1->dibujar();
        b1->dibujar();

        motor.retGestorFisicas()->limpiarFuerzas();

        EndDrawing();
    }

    delete a1;
    delete a2;
    delete m1;
    delete b1;

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
