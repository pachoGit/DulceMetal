#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "Bala.hpp"

#include <vector>

struct Arma
{
    // Tipo de bala
    TipoBala tipoBala;

    // Cantidad de balas actuales
    int cantidad;
    
    Arma(TipoBala _tipoBala, int _cantidad)
    {
        tipoBala = _tipoBala;
        cantidad = _cantidad;
    }
};

class Inventario
{
  private:

    // La lista de armas en el inventario
    std::vector<Arma *> armas;

    // El arma actual seleccionado
    int actual;

  public:

    Inventario();

    ~Inventario();
    
    // Ingresar balas o una arma nueva al inventario
    void ingresar(TipoBala tipo, int cantidad);

    // Remover un arma del inventario
    void remover(Arma *arma);

    // Remover un arma del inventario por su tipo
    void remover(TipoBala tipo);

    // Obtener el arma actual
    Arma *retActual() const;
            
    // Avanzar en el inventario
    void avanzar();

    // Regresar en el inventario
    void retroceder();

    // Retorna true si el inventario esta vacio :D
    bool estaVacio() const;
};

#endif /* INVENTARIO_HPP */
