#ifndef MAPA_HPP
#define MAPA_HPP

#include "Objeto.hpp"
#include "Obstaculo.hpp"
#include "Equipamiento.hpp"

#include <vector>

class ContornoMapa
{
  public:

    // Lista de obstaculos que cubren el contorno del mapa
    std::vector<Obstaculo *> obstaculos;

  public:
    
    ContornoMapa(TipoObstaculo tobstaculo);

    ~ContornoMapa();

    void actualizar(float dt);

    void dibujar();

};

class Mapa
{
  public:

    // El contorno del mapa
    ContornoMapa *marco;

    // Todos los objetos que se pueden interactuar con el mapa
    // por el momento: obstaculos y equipamiento
    std::vector<Objeto *> objetos;

  public:
    
    Mapa();

    ~Mapa();

    void actualizar(float dt);

    void dibujar();
};

#endif /* MAPA_HPP */
