#ifndef FISICAS_DEFS_HPP
#define FISICAS_DEFS_HPP

#include <raylib.h>
#include <Box2D.h>

#define BIT(n) (1 << n)

/*
 * Tipos de cuerpo, de acuerdo a las reglas de Box2D
 */
enum FCuerpoBanderas
{
    FCUERPO_DEFECTO =   BIT(0),  // Cuerpo dinamico por defecto
    FCUERPO_ESTATICO =  BIT(1), // Cuerpo estatico
    FCUERPO_PROYECTIL = BIT(2),     // Aplicar la caracteristica "bullet" de Box2D
    FCUERPO_FIJO =      BIT(3)     // Evitar que el cuerpo rote
};

/*
 * Grupos de colision
 */
enum FGrupoColision
{
    FGRUPO_JUGADOR =   BIT(0),
    FGRUPO_BALA =      BIT(1),
    FGRUPO_OBSTACULO = BIT(2),
    FGRUPO_AUTO =      BIT(3),
    FGRUPO_ARMA =      BIT(4),

    FGRUPO_TODO = 0xFFFF
};

/*
 * Propiedades fisicas de un cuerpo
 */
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


#endif /* FISICAS_DEFS_HPP */
