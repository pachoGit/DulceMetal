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

#include "Mapa.hpp"

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

    Auto *a1 = new Auto((Vector2) {2.f, 5.f});

    Jugador *a2 = new Jugador((Vector2) {5.f, 10.f});
    Obstaculo *m1 = new Obstaculo((Vector2) {15.f, 12.f}, OBSTACULO_ARBOL);
    Animacion *b1 = new Animacion((Vector2) {20.f, 12.f}, ANIM_VIDA);
    b1->enBucle = true;

    Mapa *mapa = new Mapa();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGRAY);
        motor.retGestorFisicas()->actualizarFisicas();

        float dt = GetFrameTime();

        if (a1 != nullptr)
        {
            a1->actualizar(dt);
            if (a1->vida <= 0)
                a1->explotar();
            if (a1->marcadoParaBorrar == true && a1->animacion->estaCorriendo == false)
            {
                delete a1;
                a1 = nullptr;
            }

        }

        a2->actualizar(dt);
        m1->actualizar(dt);
        b1->actualizar(dt);

        mapa->actualizar(dt);

        if (a1 != nullptr)
            a1->dibujar();

        a2->dibujar();
        m1->dibujar();
        b1->dibujar();

        mapa->dibujar();

        motor.retGestorFisicas()->limpiarFuerzas();

        EndDrawing();
    }

    if (a1 != nullptr)
        delete a1;

    delete a2;
    delete m1;
    delete b1;
    delete mapa;

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
