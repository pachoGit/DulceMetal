#ifndef BARRAVIDA_HPP
#define BARRAVIDA_HPP

#include <raylib.h>

class BarraVida
{
  private:

    // Posicion y dimensiones iniciales de rectangulo que representa la barra
    Rectangle espacio;

  public:
    
    // Posicion actual de la barra
    Vector2 posicion;

    // Cantidad de espacio que estara pintado la barra
    int anchoPintado;

  public:

    /**
     * @param _posicion    - Posicion inicial de la barra
     * @param anchoPintado - Ancho inicial que estara pintado la barra [0, Config::MAX_VIDA]
     */
    BarraVida(Vector2 _posicion, int _anchoPintado);

    ~BarraVida();

    void actualizar(Vector2 posicion, int anchoPintado);

    void dibujar();
};

#endif /* BARRAVIDA_HPP */
