#include "Motor.hpp"

Motor::Motor() {}

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
}

void Motor::destruirModulos()
{
    if (gTexturas != nullptr)
        delete gTexturas;
    if (gSprites != nullptr)
        delete gSprites;
}

GestorTexturas *Motor::retGestorTexturas() const
{
    return gTexturas;
}

GestorSprites *Motor::retGestorSprites() const
{
    return gSprites;
}
