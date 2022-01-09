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

std::vector<Vector2> Util::retVerticesRectangulo(Rectangle rect, Vector2 protacion, float angulo)
{
    std::vector<Vector2> resultado;

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
    
    resultado.push_back(arribaIzquierda);
    resultado.push_back(arribaDerecha);
    resultado.push_back(abajoIzquierda);
    resultado.push_back(abajoDerecha);

    return resultado;
}


float Util::pendiente(Vector2 p1, Vector2 p2)
{
    return ((p1.y - p2.y) / (p1.x - p2.x));
}