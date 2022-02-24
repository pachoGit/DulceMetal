#include "Motor.hpp"

Motor::Motor()
{
    gTexturas = nullptr;
    gSprites = nullptr;
    gFisicas = nullptr;
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
    gFisicas = new GestorFisicas();
}

void Motor::destruirModulos()
{
    if (gTexturas != nullptr)
        delete gTexturas;
    if (gSprites != nullptr)
        delete gSprites;
    if (gFisicas != nullptr)
        delete gFisicas;
}

GestorTexturas *Motor::retGestorTexturas() const
{
    return gTexturas;
}

GestorSprites *Motor::retGestorSprites() const
{
    return gSprites;
}

GestorFisicas *Motor::retGestorFisicas() const
{
    return gFisicas;
}
