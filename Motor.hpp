#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "GestorTexturas.hpp"
#include "GestorSprites.hpp"

class Motor
{
  private:

    GestorTexturas *gTexturas;

    GestorSprites *gSprites;

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
};


#endif /* MOTOR_HPP */
