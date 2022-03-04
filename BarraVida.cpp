#include "BarraVida.hpp"
#include "Config.hpp"
#include "Convertir.hpp"

BarraVida::BarraVida(Objeto *_vehiculo)
{
    vehiculo = _vehiculo;
    espacio.x = Convertir::MetrosEnPixeles(vehiculo->espacio.x);
    espacio.y = Convertir::MetrosEnPixeles(vehiculo->espacio.y);
    espacio.width = Config::DIM_BARRAVIDA.x;
    espacio.height = Config::DIM_BARRAVIDA.y;
    posicion = vehiculo->posicion;
    anchoBarraVida = Config::MAX_VIDA;
}

BarraVida::~BarraVida() {}

void BarraVida::actualizar(float dt)
{
    if (IsKeyPressed(KEY_DOWN))
        anchoBarraVida -= 10;
    if (IsKeyPressed(KEY_UP))
        anchoBarraVida += 10;
    if (anchoBarraVida < 0)
        anchoBarraVida = 0;
    if (anchoBarraVida > Config::MAX_VIDA)
        anchoBarraVida = Config::MAX_VIDA;
    posicion = Convertir::MetrosEnPixeles(vehiculo->posicion);

    // Como punto central del objeto es la posicion del objeto, debemos modificar
    // esa posicion para dirigirse a la esquina superior izquierda del objeto
    posicion.x -= Convertir::MetrosEnPixeles(vehiculo->espacio.width) * 0.5;
    posicion.y -= Convertir::MetrosEnPixeles(vehiculo->espacio.height) * 0.5 + 10;
}

void BarraVida::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;
    int a = (anchoBarraVida * Config::DIM_BARRAVIDA.x) / Config::MAX_VIDA;
    Rectangle rvidaActual = {espacio.x, espacio.y, a, espacio.height};
    // Dibujamos la barra de vida
    DrawRectangleRec(rvidaActual, BLUE);
    // Dibujamos el contorno de la vida
    DrawRectangleLinesEx(espacio, 1, GREEN);
}
