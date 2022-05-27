#ifndef MAPA_HPP
#define MAPA_HPP

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

    // Los obstaculos en el mapa
    std::vector<Obstaculo *> obstaculos;

    // Los equipamientos en el mapa
    std::vector<Equipamiento *> equipamientos;

  public:
    
    Mapa();

    ~Mapa();

    void actualizar(float dt);

    void dibujar();
};

#endif /* MAPA_HPP */
