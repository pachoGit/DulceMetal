#ifndef OBJETOAYUDAS_HPP
#define OBJETOAYUDAS_HPP

#include "Objeto.hpp"
#include "Bala.hpp"
#include "Jugador.hpp"
#include "Auto.hpp"

inline Jugador* ObjetoEnJugador(Objeto *objeto)
{
    Jugador *jugador = nullptr;
    if (objeto && objeto->esClaseJugador())
        jugador = static_cast<Jugador *>(objeto);
    return jugador;
}

inline Bala *ObjetoEnBala(Objeto *objeto)
{
    Bala *bala = nullptr;
    if (objeto && objeto->esClaseBala())
        bala = static_cast<Bala *>(objeto);
    return bala;
}

inline Auto *ObjetoEnAuto(Objeto *objeto)
{
    Auto *a = nullptr;
    if (objeto && objeto->esClaseAuto())
        a = static_cast<Auto *>(objeto);
    return a;
}

inline Objeto *retObjetoDeFixture(b2Fixture *faccesorio)
{
    Objeto *objeto = nullptr;
    if (faccesorio == nullptr)
        return objeto; // nullptr
    FisicasCuerpo *fcuerpo = (FisicasCuerpo *) faccesorio->GetBody()->GetUserData().pointer;
    return fcuerpo->objeto;
}

#endif /* OBJETOAYUDAS_HPP */
