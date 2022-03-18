#ifndef ANIMACION_HPP
#define ANIMACION_HPP

#include <raylib.h>

#include "GestorSprites.hpp"

class Animacion
{
  public:
    
    // Posicion y dimension de la animacion (en pixeles)
    Rectangle espacio;

    // Lista de sprites para la animacion
    SpriteAnimado *animacion;

    // Angulo de rotacion de la animacion (en grados)
    float angulo;

    // Cuadro actual de la animacion
    int cuadroActual;

    // Velocidad de cada cuadro (fps)
    int velocidadCuadro;

    // Contador de cuadros de la ejecucion
    int contadorCuadro;

    // True para reproducir por siempre
    bool enBucle;

    // Informa si la animacion esta ejecutandose
    bool estaCorriendo;

  public:
    
    Animacion(Vector2 _posicion, std::string nombre, int _velocidadCuadro);

    ~Animacion();
    
    void actualizar(float dt);

    void dibujar();

};


#endif /* ANIMACION_HPP */
