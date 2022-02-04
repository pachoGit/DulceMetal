#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <raylib.h>
#include <Box2D.h>

class Util
{
  public:

    /*
     * Cuando se usa alguna funcion de renderizado con rotacion (funciones que terminan en `Pro`),
     * Raylib, toma como punto de rotacion y de origen la posicion que enviamos (en cualquiera de dichas funciones).
     * Eso es una molestia, por que imagine que desea dibujar un rectangulo de 50x50 en la posicion
     * (0, 0) con un rotacion de 20 grados y el punto de rotacion en el centro del rectangulo
     * LLamando a la funcion seria: DrawRectanglePro(rectangulo, {ancho / 2.f, alto / 2.f}, 20, BLUE)
     * Lo que normalmente se esperaria es que se ubique en primer lugar el rectangulo en la
     * posicion (0, 0) y a partir de ahi se gire, pero se sorprendera que en realidad eso no sucede,
     * vera que tiene una parte del rectangulo en la pantalla.
     * Lo que sucede es que el punto que enviamos (el centro del rectangulo) se posiciona en la
     * ubicacion (0, 0) y a partir de ahi la figura se gira.
     * Esto es un problema, por que Box2D no funciona de esa manera, Box2D ubica y gira los
     * figuras de la primera forma que explique, lo que ocasiona un incompatibilidad al querer
     * hacer coincidir la textura de Raylib con el cubrimiento de Box2D
     * Por lo que un objeto ubicado por Raylib en la posicion (0, 0) con rotacion de 20 grados
     * no estara en el mismo lugar que un objeto de Box2D con las mismas caracteristicas
     * Lo que hago simplemente es modificar la posicion del rectangulo para que coincida con
     * la posicion de Box2D
     */
    static Rectangle arreglarPosicion(Rectangle rect);

    /*
     * Dibujar el contorno de un rectangulo con angulo de rotacion
     */
    static void DrawRectangleLinesPro(Rectangle rect, Vector2 protacion, float angulo, Color color);

    /*
     * Convierte un angulo a radianes
     */
    static float aRadianes(const float grados);
    
    /*
     * Convierte un angulo a grados
     */
    static float aGrados(const float radianes);

    /*
     * Calcula y devuelve los puntos de los vertices del rectangulo
     */
    static std::vector<Vector2> retVerticesRectangulo(Rectangle rect, Vector2 protacion, float angulo);

    /*
     * Calcular la pendiente de una linea
     */
    static float pendiente(const Vector2 p1, const Vector2 p2);

    /*
     * Convertir un vector de Box2D a un vetor de Raylib
     */
    static Vector2 aVectorRaylib(const b2Vec2 &vector);

    /*
     * Convertir un vector de Raylib a un vetor de Box2D
     */
    static b2Vec2 aVectorBox2D(const Vector2 vector);
};


#endif /* UTIL_HPP */
