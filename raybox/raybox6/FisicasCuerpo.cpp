#include "FisicasCuerpo.hpp"

FisicasCuerpo::FisicasCuerpo(Objeto *_objeto, const FMaterial &_fmaterial, b2BodyType _ftipo)
{
    objeto = _objeto;
    fmaterial = _fmaterial;
    ftipo = _ftipo;
}

void FisicasCuerpo::Destruir(b2World *mundo)
{
    if (accesorioBox2D != nullptr)
    {
        cuerpoBox2D->DestroyFixture(accesorioBox2D);
        accesorioBox2D = nullptr;
    }
    if (cuerpoBox2D != nullptr)
    {
        mundo->DestroyBody(cuerpoBox2D);
        cuerpoBox2D = nullptr;
    }
}

void FisicasCuerpo::Iniciar(b2World *mundo)
{
    b2BodyDef bdef;
    bdef.type = ftipo;
    bdef.position.Set(objeto->posicion.x, objeto->posicion.y);
    bdef.angle = objeto->anguloRotacion * DEG2RAD;
    cuerpoBox2D = mundo->CreateBody(&bdef);

    b2PolygonShape shape;
    shape.SetAsBox(objeto->espacio.width / 2.f, objeto->espacio.height / 2.f);

    b2FixtureDef fdef;
    fdef.shape = &shape;
    fdef.density = fmaterial.densidad;
    fdef.friction = fmaterial.friccion;
    fdef.restitution = fmaterial.restitucion;
    accesorioBox2D = cuerpoBox2D->CreateFixture(&fdef);
}

Vector2 FisicasCuerpo::retPosicion()
{
    b2Vec2 posicion = cuerpoBox2D->GetPosition();
    return (Vector2) {posicion.x, posicion.y};
}

float FisicasCuerpo::retAngulo()
{
    return cuerpoBox2D->GetAngle() * RAD2DEG;
} 

void FisicasCuerpo::transformar(const Vector2 posicion, float angulo)
{
    cuerpoBox2D->SetTransform(b2Vec2(posicion.x, posicion.y), angulo * DEG2RAD);
}

void FisicasCuerpo::aplicarImpulsoLineal(const Vector2 fuerzaImpulso, const Vector2 puntoImpulsoObjetivo)
{
    b2Vec2 impulso(fuerzaImpulso.x, fuerzaImpulso.y);
    b2Vec2 punto(puntoImpulsoObjetivo.x,  puntoImpulsoObjetivo.y);
    cuerpoBox2D->ApplyLinearImpulse(impulso, punto, true);
}

void FisicasCuerpo::agregarDataUsuario(Objeto *objeto)
{
    cuerpoBox2D->SetUserData(objeto);
}

