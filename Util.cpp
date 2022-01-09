#include <cmath>

#include "Util.hpp"

Rectangle Util::arreglarPosicion(Rectangle rect)
{
    Rectangle nuevo;
    nuevo.x = rect.x + (rect.width / 2.f);
    nuevo.y = rect.y + (rect.height / 2.f);
    nuevo.width = rect.width;
    nuevo.height = rect.height;
    return nuevo;
}

void Util::DrawRectangleLinesPro(Rectangle rect, Vector2 protacion, float angulo, Color color)
{
    Vector2 arribaIzquierda = {0};
    Vector2 arribaDerecha = {0};
    Vector2 abajoIzquierda = {0};
    Vector2 abajoDerecha = {0};

    float senoRotacion = std::sin(angulo * DEG2RAD);
    float cosenoRotacion = std::cos(angulo * DEG2RAD);
    float x = rect.x;
    float y = rect.y;
    float dx = -protacion.x;
    float dy = -protacion.y;

    arribaIzquierda.x = x + dx * cosenoRotacion - dy * senoRotacion;
    arribaIzquierda.y = y + dx * senoRotacion   + dy * cosenoRotacion;

    arribaDerecha.x = x + (dx + rect.width) * cosenoRotacion - dy * senoRotacion;
    arribaDerecha.y = y + (dx + rect.width) * senoRotacion   + dy * cosenoRotacion;

    abajoIzquierda.x = x + dx * cosenoRotacion - (dy + rect.height) * senoRotacion;
    abajoIzquierda.y = y + dx * senoRotacion   + (dy + rect.height) * cosenoRotacion;
    
    abajoDerecha.x = x + (dx + rect.width) * cosenoRotacion - (dy + rect.height) * senoRotacion;
    abajoDerecha.y = y + (dx + rect.width) * senoRotacion   + (dy + rect.height) * cosenoRotacion;
    

    DrawLineV(arribaIzquierda, arribaDerecha, color);
    DrawLineV(arribaDerecha, abajoDerecha, color);
    DrawLineV(abajoDerecha, abajoIzquierda, color);
    DrawLineV(abajoIzquierda, arribaIzquierda, color);
}
