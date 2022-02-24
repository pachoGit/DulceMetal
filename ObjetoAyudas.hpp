#ifndef OBJETOAYUDAS_HPP
#define OBJETOAYUDAS_HPP

#include "Objeto.hpp"
#include "Bala.hpp"
#include "Jugador.hpp"
#include "Auto.hpp"

inline Jugador* aJugador(Objeto *objeto)
{
    Jugador *jugador = nullptr;
    if (objeto && objeto->esClaseJugador())
        jugador = static_cast<Jugador *>(objeto);
    return jugador;
}

inline Bala *aBala(Objeto *objeto)
{
    Bala *bala = nullptr;
    if (objeto && objeto->esClaseBala())
        bala = static_cast<Bala *>(objeto);
    return bala;
}

inline Auto *aAuto(Objeto *objeto)
{
    Auto *a = nullptr;
    if (objeto && objeto->esClaseAuto())
        a = static_cast<Auto *>(objeto);
    return a;
}

#endif /* OBJETOAYUDAS_HPP */
