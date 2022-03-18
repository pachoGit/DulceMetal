#include "BarraVida.hpp"
#include "Config.hpp"
#include "Convertir.hpp"
#include "ObjetoAyudas.hpp"

BarraVida::BarraVida(Vector2 _posicion, int _anchoPintado)
{
    // Seria genial que reconociera a la clase Auto, pero no se que por que no :/
    espacio.x = _posicion.x;
    espacio.y = _posicion.y;
    espacio.width = Config::DIM_BARRAVIDA.x;
    espacio.height = Config::DIM_BARRAVIDA.y;
    posicion = _posicion;
    anchoPintado = _anchoPintado;
}

BarraVida::~BarraVida() {}

void BarraVida::actualizar(Vector2 _posicion, int _anchoPintado)
{
    posicion = _posicion;
    anchoPintado = _anchoPintado;
}

void BarraVida::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    int ancho = (anchoPintado * Config::DIM_BARRAVIDA.x) / Config::MAX_VIDA;
    Rectangle rvidaActual = {espacio.x, espacio.y, ancho, espacio.height};
    // Dibujamos la barra de vida
    DrawRectangleRec(rvidaActual, BLUE);
    // Dibujamos el contorno de la vida
    DrawRectangleLinesEx(espacio, 1, GREEN);
}
