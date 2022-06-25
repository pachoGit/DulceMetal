#ifndef MAPA_HPP
#define MAPA_HPP

#include "Objeto.hpp"
#include "Obstaculo.hpp"
#include "Enemigo.hpp"
#include "Equipamiento.hpp"
#include "Auto.hpp"

#include <vector>
#include <map>

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

class FondoMapa
{
  public:

    Sprite *sprite;

  public:

    // El fondo del mapa siempre va en medio de la ventana
    FondoMapa();

    ~FondoMapa();
    
    void dibujar();
};

struct infoMapa
{
    // TODO: De hecho solo pondria `unsigned` y listo no?
    struct ObjMapa
    {
        TipoObstaculo tobst;
        TipoEquipamiento tequi;
    } tobjeto;
    // Posicion y dimensiones del objeto obstaculo
    Vector2 posicion;
    Vector2 tam;
};

// Informacion sobre cada objeto del mapa en cada nivel
static std::map<unsigned, std::vector<infoMapa>> dataMapa;

class Mapa
{
  public:

    // El contorno del mapa
    ContornoMapa *marco;

    // Todos los objetos que se pueden interactuar con el mapa
    // por el momento: obstaculos y equipamiento
    std::vector<Objeto *> objetos;

    FondoMapa *fondo;

    // Identificar el mapa
    int nivel;

  public:
    
    Mapa(int _nivel);

    ~Mapa();

    void actualizar(float dt);

    void dibujar();

  private:

    void cargarInfo();
};

#endif /* MAPA_HPP */
