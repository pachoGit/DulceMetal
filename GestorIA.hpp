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
    Enemigo *enemigo; // Objeto
    float distancia;  // La distancia a la que esta el objeto
    // Color colorLinea; // Color de la linea de esta union
};

inline bool checkBanderasEstadoAtaque(EstadoAtaque estado, EstadoAtaque destino)
{
    return (estado & destino) > 0;
}

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

  public:

    GestorIA(Jugador *_jugador, Mapa *_mapa);
    
    ~GestorIA();

    // Actualizar todos los objetos que gestiona la clase
    void actualizar(float dt);

    // Dibujar todos los objetos que gestiona la clase
    void dibujar();
};


#endif /* GESTORIA_HPP */
