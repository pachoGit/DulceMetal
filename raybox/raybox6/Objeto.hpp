#ifndef OBJETO_HPP
#define OBJETO_HPP

#include "Comun.hpp"
#include "FisicasCuerpo.hpp"

class FisicasCuerpo;
struct FMaterial;

class Objeto
{
  public:

    Rectangle espacio;

    Vector2 posicion;

    Vector2 velocidad;

    // Angulo de rotacion el grados
    float anguloRotacion;
    
    // Color del objeto
    Color color;

    // Fisicas de este cuerpo
    FisicasCuerpo *fcuerpo;

    // Para no mover otros objetos
    bool habilitarControles;

    // Para identificar el objeto
    std::string nombre;

  public:
    
    Objeto(Rectangle _espacio, Vector2 _posicion, float _anguloRotacion);

    void Destruir(b2World *mundo);

    void actualizar(float dt);
    
    void dibujar();

    void agregarFisicas(const FMaterial &fmaterial, b2BodyType ftipo, b2World *mundo);

    void sincronizarObjetoConFisicas();

    void sincronizarFisicasConObjeto();

  private:
    
    void DrawRectangleLinesPro(Rectangle rect, Vector2 protacion, float angulo, Color color);
};


#endif /* OBJETO_HPP */
