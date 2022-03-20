#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <raylib.h>

class Config
{
  public:
    
    // Cantidad de pixeles que conforman un metro para Box2D
    static float PIXELES_POR_METRO;

    // Dimensiones de la ventana (en metros)
    static Vector2 DIM_VENTANA;

    // Dimensiones (en metros) por defecto de un "Objeto"
    static Vector2 DIM_OBJETO;

    // Dimensiones (en metros) por defecto de un "Auto"
    static Vector2 DIM_AUTO;

    // Dimensiones (en metros) por defecto de una "Bala" basica
    static Vector2 DIM_BALA_BASICA;

    // Dimensiones (en metros) por defecto de una "Bala"
    static Vector2 DIM_BALA_NORMAL;

    // dimensiones (en metros) por defecto de una "Muro"
    static Vector2 DIM_MURO;

    // Dimensiones (en metros) por defecto de un bloque de mapa
    //static Vector2 DIM_BLOQUEMAPA;

    // Iteraciones de velocidad para la simulacion de la fisica
    static int VELOCIDAD_ITER;
    
    // Iteraciones de posiciones para la simulacion de la fisica
    static int POSICION_ITER;

    // Dimension de la animacion de explosion (en pixeles)
    static Vector2 DIM_EXPLOSION_BALA;

    static Vector2 DIM_EXPLOSION_AUTO;

    // Maxima vida de los autos y el personaje
    static int MAX_VIDA;

    // Dimensiones de la barra de vida (en pixeles)
    static Vector2 DIM_BARRAVIDA;
};


#endif /* CONFIG_HPP */
