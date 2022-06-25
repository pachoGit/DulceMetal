#include "Nivel.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <algorithm>

Nivel::Nivel(int _nivel)
{
    nivel = _nivel;
    estaCorriendo = true;
    mapa = new Mapa(nivel);
    jugador = new Jugador(dataJugador.at(1), AUTO_VERDE, 0);
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
