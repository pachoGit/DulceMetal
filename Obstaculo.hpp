#ifndef OBSTACULO_HPP
#define OBSTACULO_HPP

#include "Objeto.hpp"
#include "Config.hpp"

#include <map>
#include <utility>

enum TipoObstaculo
{
    OBSTACULO_MURO_GRIS_PURO, // Muro limpio
    OBSTACULO_MURO_GRIS_RACE, // Muro con la palabra "Race"
    OBSTACULO_MURO_NARANJA_PURO,
    OBSTACULO_MURO_NARANJA_RACE,
    OBSTACULO_CONO,
    OBSTACULO_CARPA,
    OBSTACULO_ARBOL
};

static std::map<TipoObstaculo, std::string> dataObstaculo =
{
    {OBSTACULO_MURO_GRIS_PURO,    "muroGris"},
    {OBSTACULO_MURO_GRIS_RACE,    "muroGrisRace"},
    {OBSTACULO_MURO_NARANJA_PURO, "muroNaranja"},
    {OBSTACULO_MURO_NARANJA_RACE, "muroNaranjaRace"},
    {OBSTACULO_CONO,              "cono"},
    {OBSTACULO_CARPA,             "carpa"},
    {OBSTACULO_ARBOL,             "arbol"}
};
    

class Obstaculo : public Objeto
{
  public:
    
    Obstaculo(Vector2 _posicion, TipoObstaculo tipo, Vector2 _tam = Config::DIM_MURO);

    ~Obstaculo();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();
};

#endif /* OBSTACULO_HPP */
