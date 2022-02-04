#ifndef FISICAS_DEFS_HPP
#define FISICAS_DEFS_HPP

#include <raylib.h>
#include <Box2D.h>

/*
 * Tipos de cuerpo, de acuerdo a las reglas de Box2D
 */
enum FCuerpoBanderas
{
    FCUERPO_DEFECTO = 1 << 0,  // Cuerpo dinamico por defecto
    FCUERPO_ESTATICO = 1 << 1, // Cuerpo estatico
    FCUERPO_PROYECTIL = 1 << 2,     // Aplicar la caracteristica "bullet" de Box2D
    FCUERPO_FIJO = 1 << 3,     // Evitar que el cuerpo rote
    FCUERPO_ACTIVO = 1 << 4 // El cuerpo esta despierto o activo
};

/*
 * Propiedades fisicas de un cuerpo
 */
struct FMaterial
{
  public:
    float friccion;
    float restitucion;
    float densidad;

  public:
    FMaterial()
    {
        friccion = 0.f;
        restitucion = 0.f;
        densidad = 0.f;
    }
};


#endif /* FISICAS_DEFS_HPP */
