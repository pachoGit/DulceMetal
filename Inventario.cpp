#include "Inventario.hpp"

#include <algorithm>

Inventario::Inventario()
{
    actual = 0;
}

Inventario::~Inventario()
{
    if (armas.size() != 0)
    {
        for (auto &arma : armas)
            delete arma;
        armas.clear();
    }
}

void Inventario::ingresar(TipoBala tipo, int cantidad)
{
    // Buscamos si ya existe el arma
    for (auto &arma : armas)
    {
        if (arma->tipoBala == tipo)
        {
            arma->cantidad += cantidad;
            return;
        }
    }
    // Si no existe lo creamos
    armas.push_back(new Arma(tipo, cantidad));
}

void Inventario::remover(Arma *arma)
{
    armas.erase(std::remove_if(armas.begin(), armas.end(), [&] (Arma *a) {
                                                               if (a->tipoBala == arma->tipoBala)
                                                               {
                                                                   delete a;
                                                                   return true;
                                                               }
                                                               return false;
                                                           }), armas.end());
}

void Inventario::remover(TipoBala tipo)
{
    for (auto &arma : armas)
    {
        if (arma->tipoBala == tipo)
        {
            remover(arma);
            return;
        }
    }
}

Arma *Inventario::retActual() const
{
    return armas.at(actual);
}

void Inventario::avanzar()
{
    // Si llego al ultimo elemento del inventario, ir al primero
    (actual == armas.size() - 1 ? actual = 0 : actual++);
}

void Inventario::retroceder()
{
    // Si llego al primer elemento del inventario, ir al ultimo
    (actual == 0 ? actual = armas.size() - 1 : actual--);
}

bool Inventario::estaVacio() const
{
    return (armas.size() == 0);
}
