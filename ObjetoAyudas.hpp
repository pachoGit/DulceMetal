#ifndef OBJETOAYUDAS_HPP
#define OBJETOAYUDAS_HPP

#include "Objeto.hpp"
#include "Bala.hpp"
#include "Jugador.hpp"
#include "Auto.hpp"
#include "Equipamiento.hpp"
#include "Enemigo.hpp"

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

inline Equipamiento *ObjetoEnEquipamiento(Objeto *objeto)
{
    Equipamiento *e = nullptr;
    if (objeto && objeto->esClaseEquipamiento())
        e = static_cast<Equipamiento *>(objeto);
    return e;
}

inline Enemigo *ObjetoEnEnemigo(Objeto *objeto)
{
    Enemigo *e = nullptr;
    if (objeto && objeto->esClaseEnemigo())
        e = static_cast<Enemigo *>(objeto);
    return e;
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
