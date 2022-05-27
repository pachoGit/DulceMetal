#ifndef EQUIPAMIENTO_HPP
#define EQUIPAMIENTO_HPP

#include "Objeto.hpp"
#include "Bala.hpp"
#include "Animacion.hpp"

#include <map>

enum TipoEquipamiento
{
    EQUIP_RAYO,
    EQUIP_FUEGO,
    EQUIP_AURA,
    EQUIP_FLOREAL,
    EQUIP_FURIA,
    EQUIP_VIDA
};

struct InfoEquipamiento
{
    TipoAnimacion tanimacion; // Tipo de animacion del objeto
    TipoBala tipoBala;
    int ganancia; // En el caso de las armas, la cantidad de balas. En el caso de la vida, la cantidad de vida :D
    int tiempoNoVisible; // Tiempo en el que no se puede recoger (en segundos)
};

static std::map<TipoEquipamiento, InfoEquipamiento> dataEquipamiento = {
    {EQUIP_RAYO,    {ANIM_ARMA_RAYO, BALA_ELECTRICO, 5 /* balas */, 4}},
    {EQUIP_FUEGO,   {ANIM_ARMA_FUEGO, BALA_FUEGO, 2 /* balas */, 8}},
    {EQUIP_AURA,    {ANIM_ARMA_AURA, BALA_AURA, 4 /* balas */, 6}},
    {EQUIP_FLOREAL, {ANIM_ARMA_FLOREAL, BALA_FLOREAL, 4 /* balas */, 4}},
    {EQUIP_FURIA,   {ANIM_ARMA_FURIA, BALA_FURIA, 3 /* balas */, 3}},
    {EQUIP_VIDA,    {ANIM_ARMA_VIDA, BALA_BASICA /* Esto no se usara*/, 35 /* de vida */, 7}},
};

// Armas y vida que se encuentran esparcidos por el mapa :D
class Equipamiento : public Objeto
{
  public:

    // Podría poner de tipo InfoEquipamiento tambien :D

    TipoEquipamiento tipo;

    int ganancia;

    TipoBala tipoBala;

    // Controlar el tiempo
    int tiempoAnterior;

  public:

    Equipamiento(Vector2 _posicion, TipoEquipamiento _tipo);

    ~Equipamiento();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void desaparecer();
};


#endif /* EQUIPAMIENTO_HPP */
