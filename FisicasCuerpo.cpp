#include "FisicasCuerpo.hpp"
#include "Motor.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <iostream>

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
    defCuerpo.fixedRotation = checkBanderas(FCUERPO_FIJO);

    if (objeto != nullptr)
    {
        defCuerpo.position = Convertir::VectorRaylibEnBox2d(objeto->posicion);
        defCuerpo.angle = Convertir::GradosEnRadianes(objeto->angulo);
        defCuerpo.userData.pointer = reinterpret_cast<uintptr_t>(this);
    }
    cuerpoBox2D = Motor::retMotor().retGestorFisicas()->crearCuerpoBox2D(&defCuerpo);
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
        Motor::retMotor().retGestorFisicas()->destruirCuerpoBox2D(cuerpoBox2D);
        cuerpoBox2D = nullptr;
    }
}

void FisicasCuerpo::mostrar() const
{
    Vector2 posicion = retPosicion();
    float angulo = retAngulo();
    std::cout << "Fisica P: (" << posicion.x << ", " << posicion.y << ") - A: " << angulo << std::endl;
}

void FisicasCuerpo::dibujar()
{
    Vector2 posicion = retPosicion();
    float angulo = retAngulo();
    Rectangle r = {posicion.x, posicion.y, objeto->espacio.width, objeto->espacio.height};
    r = Convertir::MetrosEnPixeles(r);
    Util::DrawRectangleLinesPro(r, (Vector2) {r.width / 2.f, r.height / 2.f}, angulo, BLUE);
}

FisicasColisionador *FisicasCuerpo::agregarColisionador(const FMaterial &material, FGrupoColision miGrupo, FGrupoColision colisionarCon)
{
    fcolisionador = new FisicasColisionador(this, material, miGrupo, colisionarCon);
    return fcolisionador;
}

b2Body *FisicasCuerpo::retCuerpoBox2D() const
{
    return cuerpoBox2D;
}

Vector2 FisicasCuerpo::retPosicion() const
{
    const b2Vec2 &posicion = cuerpoBox2D->GetPosition();
    return Convertir::VectorBox2dEnRaylib(posicion);
}

float FisicasCuerpo::retAngulo() const
{
    return Convertir::RadianesEnGrados(cuerpoBox2D->GetAngle());
}

Vector2 FisicasCuerpo::retVelocidadLineal() const
{
    return Convertir::VectorBox2dEnRaylib(cuerpoBox2D->GetLinearVelocity());
}

bool FisicasCuerpo::checkBanderas(FCuerpoBanderas bandera) const
{
    return (fbanderas & bandera) > 0;
}

void FisicasCuerpo::ingPosicion(const Vector2 &posicion)
{
    cuerpoBox2D->SetTransform(Convertir::VectorRaylibEnBox2d(posicion), cuerpoBox2D->GetAngle());
}

void FisicasCuerpo::ingAngulo(float angulo)
{
    cuerpoBox2D->SetTransform(cuerpoBox2D->GetPosition(), Convertir::GradosEnRadianes(angulo));
}

void FisicasCuerpo::transformar(const Vector2 &posicion, float angulo)
{
    cuerpoBox2D->SetTransform(Convertir::VectorRaylibEnBox2d(posicion), Convertir::GradosEnRadianes(angulo));
}

void FisicasCuerpo::limpiarFuerzas()
{
    cuerpoBox2D->SetLinearVelocity((b2Vec2) {0.f, 0.f});
    cuerpoBox2D->SetAngularVelocity(0.f);
}

void FisicasCuerpo::ingVelocidadLineal(const Vector2 &velocidad)
{
    cuerpoBox2D->SetLinearVelocity(Convertir::VectorRaylibEnBox2d(velocidad));
}

void FisicasCuerpo::aplicarFuerza(const Vector2 &fuerza, const Vector2 &punto)
{
    cuerpoBox2D->ApplyForce(Convertir::VectorRaylibEnBox2d(fuerza), Convertir::VectorRaylibEnBox2d(punto), true);
}

void FisicasCuerpo::aplicarImpulso(const Vector2 &impulso, const Vector2 &punto)
{
    cuerpoBox2D->ApplyLinearImpulse(Convertir::VectorRaylibEnBox2d(impulso), Convertir::VectorRaylibEnBox2d(punto), true);
}


