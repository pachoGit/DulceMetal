#include "Motor.hpp"

Motor::Motor()
{
    gTexturas = nullptr;
    gSprites = nullptr;
    mundoFisicas = nullptr;
}

Motor::~Motor() {}

Motor &Motor::retMotor()
{
    static Motor motor;
    return motor;
}

void Motor::iniciarModulos()
{
    gTexturas = new GestorTexturas();
    gSprites = new GestorSprites();
    mundoFisicas = new b2World((b2Vec2) {0.f, 10.f});
}

void Motor::destruirModulos()
{
    if (gTexturas != nullptr)
        delete gTexturas;
    if (gSprites != nullptr)
        delete gSprites;
    if (mundoFisicas != nullptr)
        delete mundoFisicas;
}

GestorTexturas *Motor::retGestorTexturas() const
{
    return gTexturas;
}

GestorSprites *Motor::retGestorSprites() const
{
    return gSprites;
}

b2World *Motor::retMundoFisicas() const
{
    return mundoFisicas;
}
