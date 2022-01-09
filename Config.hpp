#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

class Config
{
  public:
    
    // Posicion y dimensiones por defecto de un "Objeto"
    static Rectangle obj_espacio;

    // Posicion y dimensiones por defecto de un "Auto"
    static Rectangle auto_espacio;

    // Posicion y dimensiones por defecto de una "Bala"
    static Rectangle bala_espacio;

    // Configuracion de iteraciones para las fisicas
    static int velocidadIter;
    
    static int posicionIter;

};


#endif /* CONFIG_HPP */
