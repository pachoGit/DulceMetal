#ifndef NIVEL_HPP
#define NIVEL_HPP

#include "Enemigo.hpp"
#include "Jugador.hpp"
#include "Mapa.hpp"
#include "GestorIA.hpp"

#include <map>
#include <utility> // Para std::pair
#include <vector>

class Nivel
{
  private:
    
    // El mapa (muros y objetos)
    Mapa *mapa;

    // El jugador
    Jugador *jugador;

    // Gestor de los bots
    GestorIA *gbots;

  public:

    bool estaCorriendo;

  public:

    Nivel();

    ~Nivel();

    void actualizar(float dt);

    void dibujar();
};


#endif /* NIVEL_HPP */
