#ifndef BALA_HPP
#define BALA_HPP

#include "Objeto.hpp"

#include <map>
#include <vector>
#include "Config.hpp"
#include "Animacion.hpp"

enum TipoBala
{
    BALA_BASICA,
    BALA_FUEGO,
    BALA_ELECTRICO,
    BALA_AURA,
    BALA_FURIA,
    BALA_FLOREAL
};

struct InfoBala
{
    std::string nombre;
    Vector2 dimension;
    int efecto;
    int distanciaMaxima;
    TipoAnimacion texplosion; // Tipo de animacion de la explosion
    Vector2 velocidad; // No usado por el momento
};

static const std::map<TipoBala, InfoBala> dataBala = {
    {BALA_BASICA,    {"balaBasica",    Config::DIM_BALA_BASICA, 1, 50, ANIM_EXPLOSION_BALA_AMARILLA, {2.f, 2.f}}},
    {BALA_FUEGO,     {"balaFuego",     Config::DIM_BALA_NORMAL, 4, 5,  ANIM_EXPLOSION_BALA_AMARILLA, {2.f, 2.f}}},
    {BALA_ELECTRICO, {"balaElectrico", Config::DIM_BALA_NORMAL, 2, 10, ANIM_EXPLOSION_BALA_AMARILLA, {2.f, 2.f}}},
    {BALA_AURA,      {"balaAura",      Config::DIM_BALA_NORMAL, 3, 13, ANIM_EXPLOSION_BALA_AZUL,     {2.f, 2.f}}}, // Este es el desvalanceado :D (mas efecto y mas distancia :D)
    {BALA_FURIA,     {"balaFuria",     Config::DIM_BALA_NORMAL, 2, 10, ANIM_EXPLOSION_BALA_ROJA,     {2.f, 2.f}}},
    {BALA_FLOREAL,   {"balaFloreal",   Config::DIM_BALA_NORMAL, 2, 10, ANIM_EXPLOSION_BALA_VERDE,    {2.f, 2.f}}}
};


class Bala : public Objeto
{
  public:

    // Cantidad de vida que puede quitar
    int efecto;

    // Tipo de bala
    TipoBala tipo;

    // Quien disparo el objeto, esto es para el filtrado de colisiones
    // debido a que la bala debe colisionar con Enemigo - Enemigo,
    // tendria la colision de la bala con el mismo que lo disparo
    // es para eso que agrego esta variable
    unsigned autor;

  private:

    // Distancia maxima que la bala puede recorrer (en metros)
    float distanciaMaxima;

    // La posicion anterior de la bala, necesario para ir calculando la distancia
    // que esta recorriendo la bala
    Vector2 posicionAnterior;

    // Distancia (en metros) que ha recorrido la bala
    float distanciaRecorrida;

  public:

    Bala(Vector2 _posicion, TipoBala tipo, unsigned _autor);

    ~Bala();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();
    
    void explotar();

    float retDistanciaRecorrida() const;
};


#endif /* BALA_HPP */
