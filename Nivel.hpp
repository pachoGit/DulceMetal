#ifndef NIVEL_HPP
#define NIVEL_HPP

#include "Enemigo.hpp"
#include "Jugador.hpp"
#include "Mapa.hpp"
#include "GestorIA.hpp"

#include <map>
#include <utility> // Para std::pair
#include <vector>

// Informacion sobre la posicion del jugador en cada nivel
static std::map<unsigned, Vector2> dataJugador =
{
    {1, {3.f, 15.f}}
};

class Nivel
{
  private:
    
    // El mapa (muros y objetos)
    Mapa *mapa;

    // El jugador
    Jugador *jugador;

    // Gestor de los bots
    GestorIA *gbots;

    // El nivel que se esta jugando
    int nivel;

  public:

    bool estaCorriendo;

  public:

    Nivel(int _nivel);

    ~Nivel();

    void actualizar(float dt);

    void dibujar();
};


#endif /* NIVEL_HPP */
