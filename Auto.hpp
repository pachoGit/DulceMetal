#ifndef AUTO_HPP
#define AUTO_HPP

#include <vector>

#include "Objeto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"

class Auto : public Objeto
{
  public:

    // Cantidad de vida actual del auto
    int vida;

    // Textura de la barra de vida
    BarraVida *barraVida;

    // Lista de balas que esta lanzando el auto
    std::vector<Bala *> balas;

  protected:

    // Obtener la velocidad lateral del cuerpo
    b2Vec2 retVelocidadLateral();
    
    // Obtener la velocidad delantera del cuerpo
    b2Vec2 retVelocidadDelantera();

    // Detiene la rotacion del auto
    void detenerRotacion();

    // Detiene el movimiento del auto
    void detenerAuto();

    // 
    void actualizarFriccion();

    void iniciarBarraVida();

    void actualizarBarraVida();

    /* Elimina aquellas balas que ya no son necesarias */
    void eliminarBalasDeMemoria();

  public:

    Auto(Vector2 _posicion);

    ~Auto();

    void actualizar(float dt);

    void procesarFisicas();

    void dibujar();

    void generarFisicasIniciales();

    void disparar(/* TipoBala bala*/);
};


#endif /* AUTO_HPP */
