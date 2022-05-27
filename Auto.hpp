#ifndef AUTO_HPP
#define AUTO_HPP

#include <vector>
#include <string>
#include <map>

#include "Objeto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"
#include "Inventario.hpp"
#include "Animacion.hpp"

enum TipoAuto
{
    AUTO_NARANJA,
    AUTO_AZUL,
    AUTO_VERDE,
    AUTO_AMARILLO,
    AUTO_NEGRO
};

struct InfoAuto
{
    std::string nombre; // Nombre del sprite del auto
    // TODO: Si queremos que cada auto tenga alguna caracteristica en especial
    // Agregar aqui, como: cantidad de vida, impulso para su velocidad, etc
    TipoAnimacion texplosion; // Animacion de explosion del auto
};

static const std::map<TipoAuto, InfoAuto> dataAuto =
{
    {AUTO_NARANJA,  {"autoNaranja",  ANIM_EXPLOSION_NARANJA}},
    {AUTO_AZUL,     {"autoAzul",     ANIM_EXPLOSION_AZUL}},
    {AUTO_VERDE,    {"autoVerde",    ANIM_EXPLOSION_VERDE}},
    {AUTO_AMARILLO, {"autoAmarillo", ANIM_EXPLOSION_AMARILLO}},
    {AUTO_NEGRO,    {"autoNegro",    ANIM_EXPLOSION_NEGRA}}
};

class Auto : public Objeto
{
  public:

    // Tipo de auto
    TipoAuto tipoAuto;

    // Cantidad de vida actual del auto
    int vida;

    // Textura de la barra de vida
    BarraVida *barraVida;

    // Lista de balas que esta lanzando el auto
    std::vector<Bala *> balas;

    // Las armas que posee el auto
    Inventario *inventario;

    // Tipo de bala actual que dispara el auto
    TipoBala tipoBala;

    // Identificador del objeto
    unsigned ID;

  protected:

    // Obtener la velocidad lateral del cuerpo
    b2Vec2 retVelocidadLateral();
    
    // Obtener la velocidad delantera del cuerpo
    b2Vec2 retVelocidadDelantera();

    // Detiene el movimiento del auto
    void detenerAuto();

    // 
    void actualizarFriccion();

    void iniciarBarraVida();

    void actualizarBarraVida();

    /* Elimina aquellas balas que ya no son necesarias */
    void eliminarBalasDeMemoria();

  public:

    Auto(Vector2 _posicion, TipoAuto _tipo, unsigned _ID);

    ~Auto();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void disparar();

    // Realizar la explosion de explotar del auto
    void explotar();

    // Detiene la rotacion del auto poco a poco
    void reducirRotacion();

    // Detiene el seco la rotacion del auto
    void detenerRotacion();

    // Funciones de movimiento del auto
    void impulsarHaciaAdelante();

    void impulsarHaciaAtras();

    void girarHaciaDerecha();

    void girarHaciaIzquierda();

    void girarHasta(int anguloDestino);
};


#endif /* AUTO_HPP */
