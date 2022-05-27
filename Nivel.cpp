#include "Nivel.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <algorithm>

Nivel::Nivel()
{
    estaCorriendo = true;
    mapa = new Mapa();
    jugador = new Jugador((Vector2) {5.f, 10.f}, AUTO_VERDE, 0);
    gbots = new GestorIA(jugador, mapa);
}

Nivel::~Nivel()
{
    if (mapa)
    {
        delete mapa;
        mapa = nullptr;
    }
    if (jugador)
    {
        delete jugador;
        jugador = nullptr;
    }
    if (gbots)
    {
        delete gbots;
        gbots = nullptr;
    }
}

void Nivel::actualizar(float dt)
{
    mapa->actualizar(dt);
    jugador->actualizar(dt);
    gbots->actualizar(dt);
}

void Nivel::dibujar()
{
    mapa->dibujar();
    jugador->dibujar();
    gbots->dibujar();
}
