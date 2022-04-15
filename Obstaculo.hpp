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

static std::map<TipoObstaculo, std::pair<std::string, Vector2>> dataObstaculo =
{
    {OBSTACULO_MURO_GRIS_PURO,    {"muroGris",        Config::DIM_MURO}},
    {OBSTACULO_MURO_GRIS_RACE,    {"muroGrisRace",    Config::DIM_MURO}},
    {OBSTACULO_MURO_NARANJA_PURO, {"muroNaranja",     Config::DIM_MURO}},
    {OBSTACULO_MURO_NARANJA_RACE, {"muroNaranjaRace", Config::DIM_MURO}},
    {OBSTACULO_CONO,              {"cono",            Config::DIM_CONO}},
    {OBSTACULO_CARPA,             {"carpa",           Config::DIM_CARPA}},
    {OBSTACULO_ARBOL,             {"arbol",           Config::DIM_ARBOL}}
};
    

class Obstaculo : public Objeto
{
  public:
    
    Obstaculo(Vector2 _posicion, TipoObstaculo tipo);

    ~Obstaculo();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();
};

#endif /* OBSTACULO_HPP */
