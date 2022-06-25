#include "GestorIA.hpp"
#include "Convertir.hpp"
#include "Util.hpp"
#include "ObjetoAyudas.hpp"
#include "Motor.hpp"

#include <string>
#include <algorithm>

GestorIA::GestorIA(Jugador *_jugador, Mapa *_mapa) : MapaDistancias{}, jugador(_jugador), mapa(_mapa)
{
    cargarInfo();
    unsigned iauto = 1;
    for (auto &enemigo : dataEnemigo.at(_mapa->nivel))
        enemigos.push_back(new Enemigo(enemigo.posicion, enemigo.tauto, iauto++));
}

GestorIA::~GestorIA()
{
    if (enemigos.size() > 0)
    {
        for (auto &enemigo : enemigos)
        {
            delete enemigo;
            enemigo = nullptr;
        }
        enemigos.clear();
    }
    MapaDistancias.clear();
}

void GestorIA::actualizar(float dt)
{
    contruirMapaDistancias();
    actualizarEnemigos(dt);
    enemigos.erase(std::remove_if(enemigos.begin(), enemigos.end(), [](Enemigo *e) {
                                                                        if (e->marcadoParaBorrar && !e->animacion->estaCorriendo)
                                                                        {
                                                                            delete e;
                                                                            return true;
                                                                        }
                                                                        return false;
                                                                    }), enemigos.end());
}

void GestorIA::dibujar()
{
    auto calcularRayo = [&] (const Enemigo *enemigo) {
                            Vector2 inicio = enemigo->posicion;
                            Vector2 fin = {enemigo->posicion.x + 5.0f, enemigo->posicion.y + 5.0f};
                            return std::make_pair(Convertir::MetrosEnPixeles(inicio), Convertir::MetrosEnPixeles(fin));
                        };

    for (auto &enemigo : enemigos)
    {
        enemigo->dibujar();
        auto puntos = calcularRayo(enemigo);
        //DrawLineV(puntos.first, puntos.second, RED);
    }
    dibujarMapaDistancias();
}


#include <utility>

void GestorIA::actualizarEnemigos(float dt)
{
    for (auto &enemigo : enemigos)
    {
        enemigo->actualizar(dt);
        if (enemigo->vida <= 0)
            enemigo->explotar();
    }
    //girarEnemigos();
    construirEstadoDeAtaque();
    ejecutarEstadoDeAtaque();
}

void GestorIA::contruirMapaDistancias()
{
    for (unsigned i = 0; i < enemigos.size(); ++i)
    {
        Enemigo *actual = enemigos.at(i);
        std::vector<NodoDistancia> dactual;
        // Distancia con los otros enemigos
        for (unsigned j = 0; j < enemigos.size(); ++j)
        {
            if (i == j) continue;
            Enemigo *otro = enemigos.at(j);
            dactual.push_back({otro, Util::distancia(actual->posicion, otro->posicion)});
        }
        // Distancia con el jugador
        dactual.push_back({jugador, Util::distancia(actual->posicion, jugador->posicion)});
        // Distancia con los otros objetos que se interactuan en el mapa (obstaculos, equipamiento)
        for (auto &obj_mapa : mapa->objetos)
            dactual.push_back({obj_mapa, Util::distancia(actual->posicion, obj_mapa->posicion)});

        // Ordenamos las distancias
        std::sort(dactual.begin(), dactual.end());
        MapaDistancias[actual] = std::move(dactual);
    }
}

// Las lineas no se dibujan...que raro :D
void GestorIA::dibujarMapaDistancias() const
{
    // Dibujamos el mapa de distancias
    for (const auto &[enemigo, distancias] : MapaDistancias)
    {
        std::string cadena;
        for (auto &distancia : distancias)
        {
            if (!(distancia.objeto->esClaseEnemigo()))
                continue;
            Enemigo *otro = ObjetoEnEnemigo(distancia.objeto);
            cadena.append("[");
            cadena.append(std::to_string(otro->ID));
            cadena.append(", ");
            cadena.append(std::to_string(static_cast<int>(distancia.distancia)));
            cadena.append("]");
            // Dibujar la linea que une al enemigo con el resto de enemigos
            //DrawLineV(Convertir::MetrosEnPixeles(enemigo->posicion), Convertir::MetrosEnPixeles(otro->posicion), BLUE);
        }
        // Dibujar las distancias que les une con el resto de enemigos
        //DrawText(cadena.c_str(), Convertir::MetrosEnPixeles(enemigo->espacio.x), Convertir::MetrosEnPixeles(enemigo->espacio.y) + 10, 5, BLACK);
    }
}

//#include <iostream>

void GestorIA::girarEnemigos()
{
    // Mover los autos a la derecha en 90 grados :D
    for (auto &enemigo : enemigos)
    {
        int ang_final = calcularAngulo(enemigo, jugador);
        enemigo->girarHasta(ang_final);
    }
}

int GestorIA::calcularAngulo(Enemigo *enemigo, Objeto *objeto)
{
    Vector2 pos_enemigo = enemigo->posicion;
    Vector2 pos_objeto = objeto->posicion;
        
    int ang_inclinacion = 0;
    int ang_final = 0;
    int ang_enemigo = (enemigo->angulo < 0 ? 360 + enemigo->angulo : enemigo->angulo);
    ang_enemigo = ang_enemigo % 360;
    if (pos_enemigo.y < pos_objeto.y) // El bot esta mas arriba que el auto
    {
        // sin(angulo) = cateto opuesto / hipotenusa
        ang_inclinacion = Convertir::RadianesEnGrados(std::asin(std::abs(pos_objeto.x - pos_enemigo.x) / Util::distancia(pos_objeto, pos_enemigo)));
        ang_final = (pos_enemigo.x < pos_objeto.x ? (180 - ang_inclinacion) : (180 + ang_inclinacion));
    }
    else // El  bot esta mas abajo que el auto
    {
        ang_inclinacion = Convertir::RadianesEnGrados(std::asin(std::abs(pos_objeto.y - pos_enemigo.y) / Util::distancia(pos_objeto, pos_enemigo)));
        ang_final = (pos_enemigo.x < pos_objeto.x ? (90 - ang_inclinacion) : (270 + ang_inclinacion));
    }
    return ang_final;
}

Objeto *GestorIA::retObjeto(Enemigo *enemigo, TipoClaseObjeto tipo)
{
    auto distancias = MapaDistancias[enemigo];
    for (auto &distancia : distancias)
        if (distancia.objeto->tipoClase == tipo)
            return distancia.objeto;
    return nullptr;
}

bool GestorIA::checkEstadoAtaque(Enemigo *enemigo, EstadoAtaque consultar)
{
    return (enemigo->estadoAtaque & consultar) > 0;
}

void GestorIA::agregarEstadoAtaque(Enemigo *enemigo, EstadoAtaque nuevo)
{
    enemigo->estadoAtaque = (EstadoAtaque) (enemigo->estadoAtaque | nuevo);
}

void GestorIA::quitarEstadoAtaque(Enemigo *enemigo, EstadoAtaque quitar)
{
    enemigo->estadoAtaque = (EstadoAtaque) (enemigo->estadoAtaque & ~quitar);
}

void GestorIA::construirEstadoDeAtaque()
{
    for (auto &enemigo : enemigos)
    {
        if (enemigo->inventario->estaVacio())
        {
            agregarEstadoAtaque(enemigo, E_RECARGANDO);
            quitarEstadoAtaque(enemigo, E_NADA);
        }
        else
        {
            if (jugador->checkEstadoAtaque(J_NOATACADO))
            {
                agregarEstadoAtaque(enemigo, E_ATACANDO_JUGADOR);
                quitarEstadoAtaque(enemigo, E_RECARGANDO);
                quitarEstadoAtaque(enemigo, E_NADA);
                jugador->agregarEstadoAtaque(J_ATACADO_1);
            }
            else
            {
                if (jugador->checkEstadoAtaque(J_ATACADO_1) && jugador->checkEstadoAtaque(J_ATACADO_2))
                {
                    // Ir hacia bot
                    agregarEstadoAtaque(enemigo, E_ATACANDO_BOT);
                    quitarEstadoAtaque(enemigo, E_RECARGANDO);
                    quitarEstadoAtaque(enemigo, E_ATACANDO_JUGADOR);
                }
                else
                {
                    agregarEstadoAtaque(enemigo, E_ATACANDO_JUGADOR);
                    quitarEstadoAtaque(enemigo, E_RECARGANDO);
                    quitarEstadoAtaque(enemigo, E_NADA);
                    if (jugador->checkEstadoAtaque(J_ATACADO_1))
                        jugador->agregarEstadoAtaque(J_ATACADO_2);
                    else
                        jugador->agregarEstadoAtaque(J_ATACADO_1);
                }
            }
        }
    }
}

void GestorIA::ejecutarEstadoDeAtaque()
{
    for (auto &enemigo : enemigos)
    {
        Objeto *objetivo = nullptr;
        int ang_hacia = 0;
        if (checkEstadoAtaque(enemigo, E_RECARGANDO))
        {
            objetivo = retObjeto(enemigo, CLASE_EQUIPAMIENTO); // Lo trae aunque este invisible
            if (!objetivo) continue;
            ang_hacia = calcularAngulo(enemigo, objetivo);
            enemigo->girarHasta(ang_hacia);
            if (static_cast<int>(enemigo->angulo) == ang_hacia)
                enemigo->impulsarHaciaAdelante();
            continue;
        }
        if (checkEstadoAtaque(enemigo, E_ATACANDO_BOT))
        {
            objetivo = retObjeto(enemigo, CLASE_ENEMIGO);
            if (!objetivo) continue;
            ang_hacia = calcularAngulo(enemigo, objetivo);
            enemigo->girarHasta(ang_hacia);
            if (static_cast<int>(enemigo->angulo) == ang_hacia)
                enemigo->impulsarHaciaAdelante();
            continue;
        }
        if (checkEstadoAtaque(enemigo, E_ATACANDO_JUGADOR))
        {
            objetivo = retObjeto(enemigo, CLASE_JUGADOR);
            if (!objetivo) continue;
            ang_hacia = calcularAngulo(enemigo, objetivo);
            enemigo->girarHasta(ang_hacia);
            if (static_cast<int>(enemigo->angulo) == ang_hacia)
                enemigo->impulsarHaciaAdelante();
            continue;
        }
    }
}

void GestorIA::cargarInfo()
{
    std::vector<infoEnemigo> info;
    
    info = {
        {AUTO_NARANJA,  {11.f, 5.f}},
        {AUTO_AZUL,     {27.f, 5.f}},
        {AUTO_AMARILLO, {11.f, 21.f}},
        {AUTO_NEGRO,    {27.f, 21.f}}
    };

    dataEnemigo[1] = std::move(info);
}
