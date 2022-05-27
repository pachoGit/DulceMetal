#include "GestorIA.hpp"
#include "Convertir.hpp"
#include "Util.hpp"

#include <string>
#include <algorithm>

GestorIA::GestorIA(Jugador *_jugador, Mapa *_mapa) : MapaDistancias{}, jugador(_jugador), mapa(_mapa)
{
    unsigned contador = 1; // El auto "0" es el jugador
    enemigos.push_back(new Enemigo({10.f, 10.f}, AUTO_AZUL, contador++));
    enemigos.push_back(new Enemigo({10.f, 18.f}, AUTO_AZUL, contador++));
    enemigos.push_back(new Enemigo({30.f, 10.f}, AUTO_AZUL, contador++));
    enemigos.push_back(new Enemigo({30.f, 18.f}, AUTO_AZUL, contador++));

    // Configuramos el estado de ataque de cada enemigo
    // Los dos primeros atacan al jugador
    enemigos.at(0)->estadoAtaque = (EstadoAtaque) (E_ATACANDO_JUGADOR);
    enemigos.at(1)->estadoAtaque = (EstadoAtaque) (E_ATACANDO_JUGADOR);
}

GestorIA::~GestorIA()
{
    if (enemigos.size() > 0)
    {
        for (auto &enemigo : enemigos)
            delete enemigo;
        enemigos.clear();
    }
    MapaDistancias.clear();
}

void GestorIA::actualizar(float dt)
{
    actualizarEnemigos(dt);
    contruirMapaDistancias();
}

void GestorIA::dibujar()
{
    for (auto &enemigo : enemigos)
        enemigo->dibujar();
    dibujarMapaDistancias();
}

void GestorIA::actualizarEnemigos(float dt)
{
    for (auto &enemigo : enemigos)
    {
        enemigo->actualizar(dt);
        if (enemigo->vida <= 0)
            enemigo->explotar();
    }

    girarEnemigos();

    enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(), [] (Enemigo *enemigo) {
                                                                        if (enemigo->marcadoParaBorrar && !enemigo->animacion->estaCorriendo)
                                                                        {
                                                                            delete enemigo;
                                                                            return true;
                                                                        }
                                                                        return false;
                                                                    }), enemigos.end());
}

void GestorIA::contruirMapaDistancias()
{
    for (unsigned i = 0; i < enemigos.size(); ++i)
    {
        Enemigo *actual = enemigos.at(i);
        std::vector<NodoDistancia> dactual;
        for (unsigned j = 0; j < enemigos.size(); ++j)
        {
            if (i == j) continue;
            Enemigo *otro = enemigos.at(j);
            dactual.push_back({otro, Util::distancia(actual->posicion, otro->posicion)});
        }
        MapaDistancias[enemigos.at(i)] = std::move(dactual);
    }
}

void GestorIA::dibujarMapaDistancias() const
{
    // Dibujamos el mapa de distancias
    for (const auto &[enemigo, distancias] : MapaDistancias)
    {
        std::string cadena;
        for (auto &distancia : distancias)
        {
            cadena.append("[");
            cadena.append(std::to_string(distancia.enemigo->ID));
            cadena.append(", ");
            cadena.append(std::to_string(static_cast<int>(distancia.distancia)));
            cadena.append("]");
            DrawLineV(Convertir::MetrosEnPixeles(enemigo->posicion), Convertir::MetrosEnPixeles(distancia.enemigo->posicion), BLUE);
        }
        DrawText(cadena.c_str(), Convertir::MetrosEnPixeles(enemigo->espacio.x), Convertir::MetrosEnPixeles(enemigo->espacio.y) + 10, 5, BLACK);
    }
}

//#include <iostream>

void GestorIA::girarEnemigos()
{
    // Mover los autos a la derecha en 90 grados :D
    for (auto &enemigo : enemigos)
    {
        Vector2 pos_enemigo = enemigo->posicion;
        Vector2 pos_jugador = jugador->posicion;
        
        int ang_inclinacion = 0;
        int ang_final = 0;
        int ang_enemigo = (enemigo->angulo < 0 ? 360 + enemigo->angulo : enemigo->angulo);
        ang_enemigo = ang_enemigo % 360;
        if (pos_enemigo.y < pos_jugador.y) // El bot esta mas arriba que el auto
        {
            // sin(angulo) = cateto opuesto / hipotenusa
            ang_inclinacion = Convertir::RadianesEnGrados(std::asin(std::abs(pos_jugador.x - pos_enemigo.x) / Util::distancia(pos_jugador, pos_enemigo)));
            ang_final = (pos_enemigo.x < pos_jugador.x ? (180 - ang_inclinacion) : (180 + ang_inclinacion));
        }
        else // El  bot esta mas abajo que el auto
        {
            ang_inclinacion = Convertir::RadianesEnGrados(std::asin(std::abs(pos_jugador.y - pos_enemigo.y) / Util::distancia(pos_jugador, pos_enemigo)));
            ang_final = (pos_enemigo.x < pos_jugador.x ? (90 - ang_inclinacion) : (270 + ang_inclinacion));
        }
        enemigo->girarHasta(ang_final);
        /*
        if (checkBanderasEstadoAtaque(enemigo->estadoAtaque, E_ATACANDO_JUGADOR))
            enemigo->impulsarHaciaAdelante();
        */
    }
}
