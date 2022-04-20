#ifndef ANIMACION_HPP
#define ANIMACION_HPP

#include <raylib.h>
#include <map>
#include <vector>

#include "GestorSprites.hpp"
#include "Config.hpp"

enum TipoAnimacion
{
    ANIM_EXPLOSION_AZUL,
    ANIM_EXPLOSION_VERDE,
    ANIM_EXPLOSION_AMARILLO,
    ANIM_EXPLOSION_NARANJA,
    ANIM_EXPLOSION_NEGRA,

    ANIM_EXPLOSION_BALA_VERDE,
    ANIM_EXPLOSION_BALA_AMARILLA,
    ANIM_EXPLOSION_BALA_ROJA,
    ANIM_EXPLOSION_BALA_AZUL, 

    ANIM_ARMA_RAYO,
    ANIM_ARMA_FUEGO,
    ANIM_ARMA_AURA,
    ANIM_ARMA_FLOREAL,
    ANIM_ARMA_FURIA,
    ANIM_ARMA_VIDA
};

struct InfoAnimacion
{
    std::string nombre;
    Vector2 dimension;
    int velocidadCuadro;
};

static std::map<TipoAnimacion, InfoAnimacion> dataAnimacion = {
    {ANIM_EXPLOSION_AZUL,      {"explosionAzul",     Config::DIM_EXPLOSION_AUTO, 10}},
    {ANIM_EXPLOSION_VERDE,     {"explosionVerde",    Config::DIM_EXPLOSION_AUTO, 10}},
    {ANIM_EXPLOSION_AMARILLO,  {"explosionAmarillo", Config::DIM_EXPLOSION_AUTO, 10}},
    {ANIM_EXPLOSION_NARANJA,   {"explosionNaranja",  Config::DIM_EXPLOSION_AUTO, 10}},
    {ANIM_EXPLOSION_NEGRA,     {"explosionNegra",    Config::DIM_EXPLOSION_AUTO, 10}},

    {ANIM_EXPLOSION_BALA_VERDE,    {"explosionBalaVerde",    Config::DIM_EXPLOSION_BALA, 10}},
    {ANIM_EXPLOSION_BALA_AMARILLA, {"explosionBalaAmarilla", Config::DIM_EXPLOSION_BALA, 10}},
    {ANIM_EXPLOSION_BALA_ROJA,     {"explosionBalaRoja",     Config::DIM_EXPLOSION_BALA, 10}},
    {ANIM_EXPLOSION_BALA_AZUL,     {"explosionBalaAzul",     Config::DIM_EXPLOSION_BALA, 10}},
            
    {ANIM_ARMA_RAYO,     {"armaRayo",     Config::DIM_EQUIPAMIENTO, 10}},
    {ANIM_ARMA_FUEGO,    {"armaFuego",    Config::DIM_EQUIPAMIENTO, 10}},
    {ANIM_ARMA_AURA,     {"armaAura",     Config::DIM_EQUIPAMIENTO, 10}},
    {ANIM_ARMA_FLOREAL,  {"armaFloreal",  Config::DIM_EQUIPAMIENTO, 10}},
    {ANIM_ARMA_FURIA,    {"armaFuria",    Config::DIM_EQUIPAMIENTO, 10}},
    {ANIM_ARMA_VIDA,     {"vida",         Config::DIM_EQUIPAMIENTO, 8}}
};

class Animacion
{
  public:
    
    // Posicion y dimension de la animacion (en pixeles)
    Rectangle espacio;

    // Lista de sprites para la animacion
    SpriteAnimado *animacion;

    // Angulo de rotacion de la animacion (en grados)
    float angulo;

    // Cuadro actual de la animacion
    int cuadroActual;

    // Velocidad de cada cuadro (fps)
    int velocidadCuadro;

    // Contador de cuadros de la ejecucion
    int contadorCuadro;

    // True para reproducir por siempre
    bool enBucle;

    // Informa si la animacion esta ejecutandose
    bool estaCorriendo;

  public:
    
    Animacion(Vector2 _posicion, TipoAnimacion tipo);

    ~Animacion();
    
    void actualizar(float dt);

    void dibujar();

};


#endif /* ANIMACION_HPP */
