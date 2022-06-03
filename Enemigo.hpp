#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP

#include "Auto.hpp"

enum EstadoAtaque
{
    E_ATACANDO_BOT =     BIT(0), // Si el auto esta atacando a otro bot
    E_ATACANDO_JUGADOR = BIT(1), // Si el auto esta atacando al jugador
    E_ATACADO =          BIT(2), // Si el auto esta siendo atacado por "atacante 1"
    E_RECARGANDO =       BIT(3),  // Si el bot esta recogiendo municiones

    E_NADA =             BIT(4) // Para ciertos momentos del juego
};

class Enemigo : public Auto
{
  private:
    
    // Rango de vicion del auto
    Rectangle rango;

  public:

    // Ultima vez desde que disparo
    int tiempoDisparo;

    // El estado de ataque del enemigo
    EstadoAtaque estadoAtaque;

  public:

    Enemigo(Vector2 _posicion, TipoAuto _tipo, unsigned _ID);

    ~Enemigo();

    void actualizar(float dt) override;

    void dibujar() override;
};


#endif /* ENEMIGO_HPP */
