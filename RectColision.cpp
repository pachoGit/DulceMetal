#include <cmath>
#include <iostream>

#include "RectColision.hpp"

RectColision::RectColision(Rectangle r, float _angulo)
{
    ancho = r.width;
    alto = r.height;
    arribaIzquierda = {r.x, r.y};
    arribaDerecha   = {arribaIzquierda.x + ancho, arribaIzquierda.y};
    abajoIzquierda  = {arribaIzquierda.x, arribaIzquierda.y + alto};
    abajoDerecha    = {arribaIzquierda.x + ancho, arribaIzquierda.y + alto};

    angulo = _angulo;

    std::cout << "Falsa posicion..." << std::endl;
    std::cout << "Posicion final: " << arribaIzquierda.x << ", " << arribaIzquierda.y << std::endl;
    std::cout << "Posicion final: " << arribaDerecha.x << ", " << arribaDerecha.y << std::endl;
    std::cout << "Posicion final: " << abajoIzquierda.x << ", " << abajoIzquierda.y << std::endl;
    std::cout << "Posicion final: " << abajoDerecha.x << ", " << abajoDerecha.y << std::endl;
}

RectColision::~RectColision()
{
}

void RectColision::dibujar()
{
    float senoRotacion = std::sin(angulo * DEG2RAD);
    float cosenoRotacion = std::cos(angulo * DEG2RAD);
    float x = arribaIzquierda.x;
    float y = arribaIzquierda.y;
    float dx = - (ancho / 2.f);
    float dy = - (alto / 2.f);    

    Vector2 p1, p2, p3, p4;

    p1.x = x + dx * cosenoRotacion - dy * senoRotacion;
    p1.y = y + dx * senoRotacion   + dy * cosenoRotacion;

    p2.x = x + (dx + ancho) * cosenoRotacion - dy * senoRotacion;
    p2.y = y + (dx + ancho) * senoRotacion   + dy * cosenoRotacion;

    p3.x = x + dx * cosenoRotacion - (dy + alto) * senoRotacion;
    p3.y = y + dx * senoRotacion   + (dy + alto) * cosenoRotacion;

    p4.x = x + (dx + ancho) * cosenoRotacion - (dy + alto) * senoRotacion;
    p4.y = y + (dx + ancho) * senoRotacion   + (dy + alto) * cosenoRotacion;

    r1 = p1;
    r2 = p2;
    r3 = p3;
    r4 = p4;

    // Esta es la posicion real :D
    /*
    if (IsKeyDown(KEY_SPACE))
    {
        std::cout << "R1: " << r1.x << ", " << r1.y << std::endl;
        std::cout << "R2: " << r2.x << ", " << r2.y << std::endl;
        std::cout << "R3: " << r3.x << ", " << r3.y << std::endl;
        std::cout << "R4: " << r4.x << ", " << r4.y << std::endl;
    }
    */

    DrawLineV(p1, p2, GREEN);
    DrawLineV(p2, p4, GREEN);
    DrawLineV(p4, p3, GREEN);
    DrawLineV(p3, p1, GREEN);

}

