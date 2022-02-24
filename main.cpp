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

int main()
{
    // InitWindow(1200, 840, "Dulce Metal v1.0");
    InitWindow(Convertir::MetrosEnPixeles(Config::DIM_VENTANA.x), Convertir::MetrosEnPixeles(Config::DIM_VENTANA.y), "Dulce Metal v1.0");

    SetTargetFPS(60);

    Motor &motor = Motor::retMotor();
    motor.iniciarModulos();

    motor.retGestorTexturas()->cargarTexturas();
    motor.retGestorSprites()->generarSprites();

    Texture2D t = motor.retGestorTexturas()->retTextura("principal");

    Auto *a1 = new Auto((Vector2) {0.f, 0.f});
    a1->angulo = 120.f;

    Jugador *a2 = new Jugador((Vector2) {5.f, 10.f});
    Muro *m1 = new Muro((Vector2) {15.f, 10.f});

    std::cout << "A1" << std::endl;
    a1->mostrar();
    a1->fcuerpo->mostrar();
    std::cout << std::endl;
    std::cout << "A2" << std::endl;
    a2->mostrar();
    a2->fcuerpo->mostrar();
    std::cout << std::endl;
    std::cout << "Muro" << std::endl;
    m1->mostrar();
    m1->fcuerpo->mostrar();
    std::cout << std::endl;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        motor.retGestorFisicas()->limpiarFuerzas();
        motor.retGestorFisicas()->actualizarFisicas();

        float dt = GetFrameTime();

        a1->actualizar(dt);
        a2->actualizar(dt);
        m1->actualizar(dt);

        a1->dibujar();
        a2->dibujar();
        m1->dibujar();

        EndDrawing();
    }

    std::cout << "A1" << std::endl;
    a1->mostrar();
    a1->fcuerpo->mostrar();
    std::cout << std::endl;
    std::cout << "A2" << std::endl;
    a2->mostrar();
    a2->fcuerpo->mostrar();
    std::cout << std::endl;
    std::cout << "Muro" << std::endl;
    m1->mostrar();
    m1->fcuerpo->mostrar();

    motor.destruirModulos();

    CloseWindow();

    return 0;
}
