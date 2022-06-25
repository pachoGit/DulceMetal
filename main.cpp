#include <raylib.h>
#include <box2d/box2d.h>

#include "Motor.hpp"
#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"
#include "GestorFisicas.hpp"
#include "Objeto.hpp"
#include "Auto.hpp"
#include "Jugador.hpp"
#include "Obstaculo.hpp"
#include "Convertir.hpp"
#include "Config.hpp"
#include "Animacion.hpp"
#include "Equipamiento.hpp"
#include "Mapa.hpp"
#include "Enemigo.hpp"
#include "Nivel.hpp"

#include <iostream>

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

    Nivel *nivel = new Nivel(1);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);
        motor.retGestorFisicas()->actualizarFisicas();

        float dt = GetFrameTime();

        nivel->actualizar(dt);
        nivel->dibujar();

        motor.retGestorFisicas()->limpiarFuerzas();

        EndDrawing();
    }

    if (nivel)
    {
        delete nivel;
        nivel = nullptr;
    }

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
