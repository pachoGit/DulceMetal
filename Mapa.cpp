#include "Mapa.hpp"
#include "Config.hpp"
#include "Convertir.hpp"
#include "Util.hpp"

#include <algorithm>

ContornoMapa::ContornoMapa(TipoObstaculo tobstaculo)
{
    auto info = dataObstaculo[tobstaculo];
    // La mitad de las dimensiones del muro
    float anchoMedio = Config::DIM_MURO.x * 0.5f;
    float altoMedio = Config::DIM_MURO.y * 0.5f;

    for (float i = anchoMedio; i <= Config::DIM_VENTANA.x; i+=info.second.x)
    {
        // Lado superior
        obstaculos.push_back(new Obstaculo((Vector2) {i, altoMedio}, tobstaculo));
        // Lado inferior
        obstaculos.push_back(new Obstaculo((Vector2) {i, Config::DIM_VENTANA.y - altoMedio}, tobstaculo));
    }
    for (float i = Config::DIM_VENTANA.y - Config::DIM_MURO.y - anchoMedio; i >= (Config::DIM_MURO.y + anchoMedio); i-=info.second.x)
    {
        // Lado izquierdo, de abajo hacia arriba
        Obstaculo *n1 = new Obstaculo((Vector2) {altoMedio, i}, tobstaculo);
        n1->ingAngulo(-90.f);
        obstaculos.push_back(n1);
        // Lado derecho, de abajo hacia arriba
        Obstaculo *n2 = new Obstaculo((Vector2) {Config::DIM_VENTANA.x - altoMedio, i}, tobstaculo);
        n2->ingAngulo(90.f);
        obstaculos.push_back(n2);
    }
}

ContornoMapa::~ContornoMapa()
{
    if (obstaculos.size() > 0)
        for (auto &obstaculo : obstaculos)
            delete obstaculo;
    obstaculos.clear();
}

void ContornoMapa::actualizar(float dt)
{
    for (auto &obstaculo : obstaculos)
        obstaculo->actualizar(dt);
}

void ContornoMapa::dibujar()
{
    for (auto &obstaculo : obstaculos)
        obstaculo->dibujar();
}

Mapa::Mapa()
{
    marco = new ContornoMapa(OBSTACULO_MURO_GRIS_RACE);
    
    // Algunos arboles
    obstaculos.push_back(new Obstaculo({5.f, 5.f}, OBSTACULO_ARBOL));
    obstaculos.push_back(new Obstaculo({35.f, 5.f}, OBSTACULO_ARBOL));
    obstaculos.push_back(new Obstaculo({5.f, 23.f}, OBSTACULO_ARBOL));
    obstaculos.push_back(new Obstaculo({35.f, 23.f}, OBSTACULO_ARBOL));
    // Una carpa en medio :D
    obstaculos.push_back(new Obstaculo({20.f, 14.f}, OBSTACULO_CARPA));

    equipamientos.push_back(new Equipamiento({7.f, 7.f}, EQUIP_RAYO));
    equipamientos.push_back(new Equipamiento({36.f, 7.f}, EQUIP_FUEGO));
    equipamientos.push_back(new Equipamiento({7.f, 25.f}, EQUIP_VIDA));
    equipamientos.push_back(new Equipamiento({37.f, 25.f}, EQUIP_FLOREAL));
}

Mapa::~Mapa()
{
    if (marco)
    {
        delete marco;
        marco = nullptr;
    }
    if (obstaculos.size() > 0)
    {
        for (auto &obstaculo : obstaculos)
            delete obstaculo;
        obstaculos.clear();
    }
    if (equipamientos.size() > 0)
    {
        for (auto &equipamiento : equipamientos)
            delete equipamiento;
        equipamientos.clear();
    }
}

void Mapa::actualizar(float dt)
{
    marco->actualizar(dt);
    for (auto &obstaculo : obstaculos)
        obstaculo->actualizar(dt);
    for (auto &equipamiento : equipamientos)
        equipamiento->actualizar(dt);
}

void Mapa::dibujar()
{
    marco->dibujar();
    for (auto &obstaculo : obstaculos)
        obstaculo->dibujar();
    for (auto &equipamiento : equipamientos)
        equipamiento->dibujar();
}
