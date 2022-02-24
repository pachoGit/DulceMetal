#ifndef FISICASCUERPO_HPP
#define FISICASCUERPO_HPP

#include "FisicasDefs.hpp"
#include "FisicasColisionador.hpp"
#include "Objeto.hpp"

class FisicasColisionador;
class Objeto;

class FisicasCuerpo
{
  private:
    
    // Representacion de las fisicas de Box2D
    b2Body *cuerpoBox2D;

  public:
    
    // Objeto al que le pertenecen las fisicas
    Objeto *objeto;

    // Propiedades del cuerpo
    FCuerpoBanderas fbanderas;
    
    // La forma (shape) y el accesorio (fixture) del cuerpo
    FisicasColisionador *fcolisionador;

  public:
    
    FisicasCuerpo(Objeto *_objeto, FCuerpoBanderas _fbanderas);

    ~FisicasCuerpo();

    // Mostrar posicion y angulo en la salida estandar
    void mostrar() const;

    void dibujar();

    FisicasColisionador *agregarColisionador(const FMaterial &material, FGrupoColision miGrupo, FGrupoColision colisionarCon);

    b2Body *retCuerpoBox2D() const;

    // Obtener la posicion del objeto de fisicas
    Vector2 retPosicion() const;

    // Obtener el angulo en grados
    float retAngulo() const;

    // Obtener la velocidad
    Vector2 retVelocidadLineal() const;

    // Cambiar la posicion
    void ingPosicion(const Vector2 &posicion);

    // Cambiar el angulo de rotacion - en grados
    void ingAngulo(float angulo);

    // Tranformar la posicion y angulo
    void transformar(const Vector2 &posicion, float angulo);

    // Limpiar las fuerzas acumuladas por el objeto
    void limpiarFuerzas();

    void ingVelocidadLineal(const Vector2 &velocidad);

  private:
    
    inline bool checkBanderas(FCuerpoBanderas bandera) const;
};

#endif /* FISICASCUERPO_HPP */
