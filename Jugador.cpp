#include "Jugador.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"

Jugador::Jugador(Vector2 _posicion) : Objeto(_posicion)
{
    espacio.width = Config::auto_espacio.width;
    espacio.height = Config::auto_espacio.height;

    sprite = Motor::retMotor().retGestorSprites()->retSprite("auto1");
    vida = 0;
    velocidad = 50.f;
}

Jugador::~Jugador()
{
    // Borrar las balas
}

void Jugador::actualizar(float dt)
{
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        angulo += 0.5f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        angulo -= 0.5f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        posicion.x += std::sin(angulo * DEG2RAD) * dt * velocidad;
        posicion.y -= std::cos(angulo * DEG2RAD) * dt * velocidad;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        posicion.x -= std::sin(angulo * DEG2RAD) * dt * velocidad;
        posicion.y += std::cos(angulo * DEG2RAD) * dt * velocidad;
    }
    if (IsKeyPressed(KEY_SPACE))
        disparar();
    for (auto &bala : balas)
        bala->actualizar(dt);
}

void Jugador::dibujar()
{
    Objeto::dibujar();
    for (auto bala : balas)
        bala->dibujar();
}

void Jugador::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(Util::arreglarPosicion(espacio), (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);
    Bala *b1 = new Bala((Vector2){arribaIzquierda.x, arribaIzquierda.y});
    b1->angulo = angulo;
    Bala *b2 = new Bala((Vector2){arribaDerecha.x, arribaDerecha.y});
    b2->angulo = angulo;

    balas.push_back(b1);
    balas.push_back(b2);
}
