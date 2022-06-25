#include "Mapa.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Convertir.hpp"
#include "Util.hpp"
#include "ObjetoAyudas.hpp"

#include <algorithm>

ContornoMapa::ContornoMapa(TipoObstaculo tobstaculo)
{
    auto info = dataObstaculo[tobstaculo];
    // La mitad de las dimensiones del muro
    float anchoMedio = Config::DIM_MURO.x * 0.5f;
    float altoMedio = Config::DIM_MURO.y * 0.5f;

    for (float i = anchoMedio; i <= (Config::DIM_VENTANA.x + anchoMedio) /* que pase uno de largo*/; i+=Config::DIM_MURO.x)
    {
        // Lado superior
        obstaculos.push_back(new Obstaculo((Vector2) {i, altoMedio}, tobstaculo));
        // Lado inferior
        obstaculos.push_back(new Obstaculo((Vector2) {i, Config::DIM_VENTANA.y - altoMedio}, tobstaculo));
    }
    for (float i = Config::DIM_VENTANA.y  - anchoMedio; i >= (Config::DIM_MURO.y + anchoMedio); i-=Config::DIM_MURO.x)
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

/** FONDO MAPA **/

FondoMapa::FondoMapa()
{
    sprite = Motor::retMotor().retGestorSprites()->retSprite("mapa1");
}

FondoMapa::~FondoMapa()
{
}

void FondoMapa::dibujar()
{
    Rectangle vespacio = Convertir::MetrosEnPixeles({20.f, 15.f, 40.f, 30.f});
    if (sprite != nullptr)
        DrawTexturePro(sprite->textura, sprite->espacio, vespacio, (Vector2) {vespacio.width * 0.5f, vespacio.height * 0.5f}, 0.0f, RAYWHITE);
}

/** MAPA **/

Mapa::Mapa(int _nivel)
{
    nivel = _nivel;
    marco = new ContornoMapa(OBSTACULO_MURO_GRIS_PURO);
    fondo = new FondoMapa();
    cargarInfo();
    for (auto &objMapa : dataMapa.at(nivel))
    {
        if (objMapa.tobjeto.tobst != -1)
            objetos.push_back(new Obstaculo(objMapa.posicion, objMapa.tobjeto.tobst, objMapa.tam));
        else
            objetos.push_back(new Equipamiento(objMapa.posicion, objMapa.tobjeto.tequi));
    }
}

Mapa::~Mapa()
{
    if (marco)
    {
        delete marco;
        marco = nullptr;
    }
    if (objetos.size() > 0)
    {
        for (auto &objeto : objetos)
            delete objeto;
        objetos.clear();
    }
    if (fondo)
    {
        delete fondo;
        fondo = nullptr;
    }
}

void Mapa::actualizar(float dt)
{
    marco->actualizar(dt);
    for (auto &objeto : objetos)
        objeto->actualizar(dt);
}

void Mapa::dibujar()
{
    fondo->dibujar();
    marco->dibujar();
    for (auto &objeto : objetos)
        objeto->dibujar();
}

void Mapa::cargarInfo()
{

#define TO (TipoObstaculo)
#define TE (TipoEquipamiento)

    std::vector<infoMapa> info;
    info = {
        // Obstaculos
        {{OBSTACULO_CARPA, TE -1}, {19.f, 13.f}, {10.f, 10.f}},
        {{OBSTACULO_CARPA, TE -1}, {5.f, 11.f}, {2.f, 2.f}},        
        {{OBSTACULO_CARPA, TE -1}, {5.f, 13.f}, {2.f, 2.f}}, 
        {{OBSTACULO_CARPA, TE -1}, {5.f, 15.f}, {2.f, 2.f}},
        {{OBSTACULO_CARPA, TE -1}, {33.f, 11.f}, {2.f, 2.f}},
        {{OBSTACULO_CARPA, TE -1}, {33.f, 13.f}, {2.f, 2.f}},
        {{OBSTACULO_CARPA, TE -1}, {33.f, 15.f}, {2.f, 2.f}},
        {{OBSTACULO_CARPA, TE -1}, {17.f, 27.f}, {2.f, 2.f}},
        {{OBSTACULO_CARPA, TE -1}, {19.f, 27.f}, {2.f, 2.f}},        
        {{OBSTACULO_CARPA, TE -1}, {21.f, 27.f}, {2.f, 2.f}},

        // Equipamiento - El tamanio no se usa
        {{TO -1, EQUIP_RAYO}, {5.f, 5.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_FUEGO}, {19.f, 5.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_AURA}, {35.f, 5.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_RAYO}, {5.f, 23.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_FLOREAL}, {19.f, 23.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_FURIA}, {35.f, 23.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_VIDA}, {11.f, 13.f}, {2.f, 2.f}},
        {{TO -1, EQUIP_VIDA}, {27.f, 13.f}, {2.f, 2.f}}
    };

    dataMapa[1] = std::move(info);

#undef TO
#undef TE

}
