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

    // Dimensiones (en metros) por defecto del obstaculo "Muro"
    static Vector2 DIM_MURO;

    // Dimensiones (en metros) por defecto del obstaculo "Carpa"
    static Vector2 DIM_CARPA;

    // Dimensiones (en metros) por defecto del obstaculo "Cono"
    static Vector2 DIM_CONO;

    // Dimensiones (en metros) por defecto del obstaculo "Arbol"
    static Vector2 DIM_ARBOL;

    // Dimensiones (en metros) por defecto de un bloque de mapa
    //static Vector2 DIM_BLOQUEMAPA;

    // Iteraciones de velocidad para la simulacion de la fisica
    static int VELOCIDAD_ITER;
    
    // Iteraciones de posiciones para la simulacion de la fisica
    static int POSICION_ITER;

    // Dimension de la animacion de explosion (en metros)
    static Vector2 DIM_EXPLOSION_BALA;

    static Vector2 DIM_EXPLOSION_AUTO;

    // Maxima vida de los autos y el personaje
    static int MAX_VIDA;

    // Dimensiones de la barra de vida (en pixeles)
    static Vector2 DIM_BARRAVIDA;

    // Dimensiones de las armas (recogibles) en metros
    static Vector2 DIM_EQUIPAMIENTO;

    // Dimensiones del rango de vicion del enemigo
    static float RANGO_VISION_ENEMIGO;
};


#endif /* CONFIG_HPP */
