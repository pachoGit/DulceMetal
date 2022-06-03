#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <vector>

#include "Auto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"

enum JAtaque
{
    J_ATACADO_1 = BIT(0), // Esta siendo atacado por el bot 1
    J_ATACADO_2 = BIT(1), // Esta siendo atacado por el bot 2
    J_NOATACADO = BIT(2)  // No esta siendo atacado
};

class Jugador : public Auto
{
  public:
    
    // El jugador esta siendo atacado?
    JAtaque estadoAtaque;

  public:

    Jugador(Vector2 _posicion, TipoAuto _tipo, unsigned _ID);

    ~Jugador();

    void actualizar(float dt) override;

    void procesarFisicas() override;

    void dibujar() override;

    void disparar();

    // Verificar que banderas de estado de ataque tiene el jugador
    inline bool checkEstadoAtaque(JAtaque e)
    {
        return (estadoAtaque & e) > 0;
    }

    inline void agregarEstadoAtaque(JAtaque e)
    {
        estadoAtaque = (JAtaque) (estadoAtaque | e);
    }

    inline void quitarEstadoAtaque(JAtaque e)
    {
        estadoAtaque = (JAtaque) (estadoAtaque & ~e);
    }
};


#endif /* JUGADOR_HPP */
