#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Box2D.h>

#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"

class Motor
{
  private:

    GestorTexturas *gTexturas;

    GestorSprites *gSprites;

    b2World *mundoFisicas;

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
    b2World *retMundoFisicas() const;
};


#endif /* MOTOR_HPP */
