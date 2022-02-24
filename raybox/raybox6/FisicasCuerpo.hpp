#ifndef FISICASCUERPO_HPP
#define FISICASCUERPO_HPP

#include "Comun.hpp"
#include "Objeto.hpp"

class Objeto;
struct FMaterial;

struct FMaterial
{
  public:

    float densidad;
    float friccion;
    float restitucion;

  public:

    FMaterial()
    {
        densidad = 0.f;
        friccion = 0.f;
        restitucion = 0.f;
    }

    FMaterial(float _densidad, float _friccion, float _restitucion)
    {
        densidad = _densidad;
        friccion = _friccion;
        restitucion = _restitucion;
    }
};

class FisicasCuerpo
{
  public:
    
    b2Body *cuerpoBox2D;

    b2Fixture *accesorioBox2D;

    Objeto *objeto;

    FMaterial fmaterial;

    b2BodyType ftipo;

  public:
    
    FisicasCuerpo(Objeto *_objeto, const FMaterial &_fmaterial, b2BodyType _ftipo);
    
    void Destruir(b2World *mundo);

    void Iniciar(b2World *mundo);

    Vector2 retPosicion();

    float retAngulo();

    void transformar(const Vector2 posicion, float angulo);

    void aplicarImpulsoLineal(const Vector2 fuerzaImpulso, const Vector2 puntoImpulsoObjetivo);

    void agregarDataUsuario(Objeto *objeto);
};

#endif /* FISICASCUERPO_HPP */
