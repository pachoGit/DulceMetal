#ifndef EQUIPAMIENTO_HPP
#define EQUIPAMIENTO_HPP

#include "Objeto.hpp"
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
    int ganancia; // En el caso de las armas, la cantidad de balas. En el caso de la vida, la cantidad de vida :D
};

static std::map<TipoEquipamiento, InfoEquipamiento> dataEquipamiento = {
    {EQUIP_RAYO,    {ANIM_ARMA_RAYO, 5 /* balas */}},
    {EQUIP_FUEGO,   {ANIM_ARMA_RAYO, 2 /* balas */}},
    {EQUIP_AURA,    {ANIM_ARMA_RAYO, 4 /* balas */}},
    {EQUIP_FLOREAL, {ANIM_ARMA_RAYO, 4 /* balas */}},
    {EQUIP_FURIA,   {ANIM_ARMA_RAYO, 3 /* balas */}},
    {EQUIP_VIDA,    {ANIM_ARMA_RAYO, 35 /* de vida */}},
};


// Armas y vida que se encuentran esparcidos por el mapa :D
class Equipamiento : public Objeto
{
  public:

    Equipamiento(Vector2 _posicion, TipoEquipamiento _tipo);

    ~Equipamiento();

  public:

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();
};


#endif /* EQUIPAMIENTO_HPP */
