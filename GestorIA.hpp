#ifndef GESTORIA_HPP
#define GESTORIA_HPP

#include "Objeto.hpp"
#include "Enemigo.hpp"
#include "Jugador.hpp"
#include "Mapa.hpp"

#include <vector>
#include <map>

struct NodoDistancia
{
    Objeto *objeto; // Objeto
    float distancia;  // La distancia a la que esta el objeto
    // Color colorLinea; // Color de la linea de esta union
    
    inline bool operator < (const NodoDistancia &otro)
    {
        return ((int) distancia < (int) otro.distancia);
    }
};

class GestorIA
{
  private:

    // Una referencia al jugador (solo lectura)
    Jugador *jugador;

    // Una referencia al mapa (solo lectura)
    Mapa *mapa;

    // Todos los objetos que son manejados por la IA
    std::vector<Enemigo *> enemigos;

    // La informacion de un bot que tiene de los demas objetos del mapa
    std::map<Enemigo *, std::vector<NodoDistancia>> MapaDistancias;

  private:

    // Actualizar los enemigos
    void actualizarEnemigos(float dt);

    // Construir el mapa de distancias en cada paso de tiempo
    void contruirMapaDistancias();

    // DEBUG: Dibujar el mapa de distancias en cada paso de tiempo
    void dibujarMapaDistancias() const;

    // Temporal: Girar todos los bots a 90 grados
    void girarEnemigos();

    // Calcula el angulo al que tiene que rotar el bot, para poder llegar directamente al objeto
    int calcularAngulo(Enemigo *enemigo, Objeto *objeto);

    // Obtiene el primer objeto (mas cercano) segun el tipo, del mapa de distancias
    Objeto *retObjeto(Enemigo *enemigo, TipoClaseObjeto tipo);

    // Consulta banderas de estados al enemigo
    inline bool checkEstadoAtaque(Enemigo *enemigo, EstadoAtaque consulta);

    // Agrega banderas de estados al enemigo
    inline void agregarEstadoAtaque(Enemigo *enemigo, EstadoAtaque nuevo);

    // Elimina banderas de estados al enemigo
    inline void quitarEstadoAtaque(Enemigo *enemigo, EstadoAtaque quitar);

    // En cada paso del juego, se va a construir o mantener el estado de ataque enemigo
    // No solo estado de ataque, si no tambien, cuando va a recoger arma por ejemplo
    void construirEstadoDeAtaque();

    // Es decir, mover y realizar las acciones de los autos hacia sus destinos :D
    void ejecutarEstadoDeAtaque();

  public:

    GestorIA(Jugador *_jugador, Mapa *_mapa);
    
    ~GestorIA();

    // Actualizar todos los objetos que gestiona la clase
    void actualizar(float dt);

    // Dibujar todos los objetos que gestiona la clase
    void dibujar();
};


#endif /* GESTORIA_HPP */
