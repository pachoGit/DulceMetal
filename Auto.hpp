#ifndef AUTO_HPP
#define AUTO_HPP

#include <vector>

#include "Objeto.hpp"
#include "Bala.hpp"
#include "BarraVida.hpp"

#include "Inventario.hpp"

class Auto : public Objeto
{
  public:

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

    void disparar(/* TipoBala bala*/);

    // Realizar la explosion de explotar del auto
    void explotar();
};


#endif /* AUTO_HPP */
