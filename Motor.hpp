#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <box2d/box2d.h>

#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"
#include "GestorFisicas.hpp"

class Motor
{
  private:

    GestorTexturas *gTexturas;

    GestorSprites *gSprites;

    GestorFisicas *gFisicas;

  public:
    
    Motor();

    ~Motor();

    /* Crear un objeto estatico de motor y retornarlo */
    static Motor &retMotor();

    /* Iniciar los modulos */
    void iniciarModulos();

    /* Destruir los modulos */
    void destruirModulos();
    
    /* Obtener el gestor de texturas */
    GestorTexturas *retGestorTexturas() const;

    /* Obtener el gestor de sprites */
    GestorSprites *retGestorSprites() const;

    /* Obtener el mundo de las fisicas */
    GestorFisicas *retGestorFisicas() const;
};

#endif /* MOTOR_HPP */
