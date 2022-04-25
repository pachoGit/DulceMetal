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

    unsigned contador = 0;

    Jugador *a2 = new Jugador((Vector2) {5.f, 10.f}, AUTO_VERDE, contador++);
    //Equipamiento *eq = new Equipamiento((Vector2) {25.f, 12.f}, EQUIP_RAYO);
    Mapa *mapa = new Mapa();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);
        motor.retGestorFisicas()->actualizarFisicas();

        float dt = GetFrameTime();

        a2->actualizar(dt);
        mapa->actualizar(dt);
        //eq->actualizar(dt);


        mapa->dibujar();
        a2->dibujar();
        //eq->dibujar();

        motor.retGestorFisicas()->limpiarFuerzas();

        EndDrawing();
    }

    delete a2;
    delete mapa;
    //delete eq;

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
