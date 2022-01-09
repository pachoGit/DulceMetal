#ifndef UTIL_HPP
#define UTIL_HPP

#include <raylib.h>

class Util
{
  public:

    /*
     * El renderizado con angulo de una textura en raylib, realiza un cambio en la posicion
     * origen que se envia como parametro, por lo que cuando se ubica algo en la posicion
     * (0, 0) con algun angulo, y lo queremos rotar con respecto a su centro, raylib posiciona
     * el centro del objeto en (0, 0), pero sin embargo, se trabaja mejor si se gira el objeto
     * desde la posicion en la que se le indica
     */
    static Rectangle arreglarPosicion(Rectangle rect);

    /*
     * Dibujar el contorno de un rectangulo con angulo de rotacion
     */
    static void DrawRectangleLinesPro(Rectangle rect, Vector2 protacion, float angulo, Color color);


};


#endif /* UTIL_HPP */
