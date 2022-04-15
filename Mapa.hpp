#ifndef MAPA_HPP
#define MAPA_HPP

#include "Obstaculo.hpp"

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

  public:
    
    Mapa();

    ~Mapa();

    void actualizar(float dt);

    void dibujar();
};

#endif /* MAPA_HPP */
