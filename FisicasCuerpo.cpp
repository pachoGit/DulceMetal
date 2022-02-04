#include "FisicasCuerpo.hpp"
#include "Motor.hpp"
#include "Util.hpp"

FisicasCuerpo::FisicasCuerpo(Objeto *_objeto, FCuerpoBanderas _fbanderas) :
        cuerpoBox2D(nullptr),
        objeto(_objeto),
        fbanderas(_fbanderas),
        fcolisionador(nullptr)
{
    b2BodyDef defCuerpo;

    defCuerpo.type = b2_dynamicBody; // Por defecto
    bool esEstatico = checkBanderas(FCUERPO_ESTATICO);
    if (esEstatico)
        defCuerpo.type = b2_staticBody;

    defCuerpo.bullet = checkBanderas(FCUERPO_PROYECTIL);
    //defCuerpo.enabled = checkBanderas(FCUERPO_ACTIVO);
    //defCuerpo.userData.pointer = reinterpret_cast<uintptr_t>(this);
    
    if (objeto)
    {
        defCuerpo.position = Util::aVectorBox2D(objeto->posicion);
        defCuerpo.angle = Util::aRadianes(objeto->angulo); //  objeto->angulo * DEG2RAD;
    }
    cuerpoBox2D = Motor::retMotor().retMundoFisicas()->CreateBody(&defCuerpo);
    fcolisionador = nullptr;
}

FisicasCuerpo::~FisicasCuerpo()
{
    if (fcolisionador)
    {
        delete fcolisionador;
        fcolisionador = nullptr;
    }
    if (cuerpoBox2D)
    {
        Motor::retMotor().retMundoFisicas()->DestroyBody(cuerpoBox2D);
        cuerpoBox2D = nullptr;
    }
}

b2Body *FisicasCuerpo::retCuerpoBox2D() const
{
    return cuerpoBox2D;
}

Vector2 FisicasCuerpo::retPosicion() const
{
    const b2Vec2 &posicion = cuerpoBox2D->GetPosition();
    return Util::aVectorRaylib(posicion);
}

float FisicasCuerpo::retAngulo() const
{
    return cuerpoBox2D->GetAngle() * RAD2DEG;
}

FisicasColisionador *FisicasCuerpo::agregarColisionador(const FMaterial &material)
{
    fcolisionador = new FisicasColisionador(this, material);
    return fcolisionador;
}

bool FisicasCuerpo::checkBanderas(FCuerpoBanderas bandera) const
{
    return (fbanderas & bandera) > 0;
}

