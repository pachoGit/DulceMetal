#ifndef OBJETO_HPP
#define OBJETO_HPP

#include <raylib.h>
#include <cmath>

#include "GestorSprites.hpp"
#include "FisicasCuerpo.hpp"
#include "Animacion.hpp"
class FisicasCuerpo;

enum TipoClaseObjeto
{
    CLASE_BASE, // es decir, de tipo "Objeto"
    CLASE_AUTO,
    CLASE_BALA,
    CLASE_MURO,
    CLASE_JUGADOR
};

class Objeto
{
  public:

    // Posicion y dimensiones del objeto (en metros)
    Rectangle espacio;

    // Posicion actual del objeto (en metros)
    Vector2 posicion;
    
    // Velocidad del objeto (en metros)
    Vector2 velocidad;

    // Sprite del objeto
    Sprite *sprite;

    // Angulo de rotacion del objeto (en grados)
    float angulo;

    // Indica si el objeto debe dibujarse
    bool visible;

    // Fisicas
    FisicasCuerpo *fcuerpo;

    // Habilitar para el procesado de las fisicas
    bool habilitarProcesadoFisicas;

    // Identificar la clase de un objeto
    TipoClaseObjeto tipoClase;

    // Cualquier tipo de animacion que objeto tenga que realizar
    Animacion *animacion;

    // Nombre del objeto
    std::string nombre;

    // Indica si el objeto se debe eliminar (de memoria)
    bool marcadoParaBorrar;
    
  public:
    
    Objeto(Vector2 _posicion);

    /**** Funciones principales ****/
    virtual ~Objeto() = 0;

    virtual void actualizar(float dt) = 0;
    
    virtual void procesarFisicas() = 0;

    virtual void dibujar() = 0;

    /**** Funciones del procesado de Fisicas ****/

    // Inicializa la variable "fcuerpo"
    virtual void generarFisicasIniciales() = 0;

    // Ingresar las fisicas para este cuerpo
    void ingFCuerpo(FisicasCuerpo *_fcuerpo);

    // Sincronizar los datos de las fisicas con el objeto
    void sincronizarFisicasConObjeto();

    // Sincronizar los datos del objeto con las fisicas
    void sincronizarObjetoConFisicas();

    /****  Funciones de ayuda de la clase Objeto ****/

    // Identificar la clase de un objeto
    inline bool esClaseBase() const { return (tipoClase == CLASE_BASE); }
    inline bool esClaseBala() const { return (tipoClase == CLASE_BALA); }
    inline bool esClaseAuto() const { return (tipoClase == CLASE_AUTO); }
    inline bool esClaseJugador() const { return (tipoClase == CLASE_JUGADOR); }

    /**** Funciones extras o de debug ****/

    // Mostrar la posicion y angulo del objeto por la salida estandar
    void mostrar() const;


};

#endif /* OBJETO_HPP */
