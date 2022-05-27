#include "GestorFisicas.hpp"
#include "ObjetoAyudas.hpp"
#include "Config.hpp"
#include "Convertir.hpp"

#include <box2d/b2_collision.h>
#include <algorithm>
#include <iostream>

// Comprueba si un accesorio pertenece al grupo de colision consultado
inline bool CheckGrupoColision(const b2Fixture *accesorio, FGrupoColision colision)
{
    const b2Filter &filtro = accesorio->GetFilterData();
    return (filtro.categoryBits & colision) > 0;
}


GestorFisicas::GestorFisicas()
{
    gravedad.Set(0.f, 0.f);
    mundoBox2D = new b2World(gravedad);
    mundoBox2D->SetContactListener(this);
    velocidadIteraciones = Config::VELOCIDAD_ITER;
    posicionIteraciones = Config::POSICION_ITER;
}

GestorFisicas::~GestorFisicas()
{
    if (mundoBox2D)
    {
        delete mundoBox2D;
        mundoBox2D = nullptr;
    }
    if (cuerposBox2D.size() > 0)
        for (auto &fcuerpo : cuerposBox2D)
            delete fcuerpo;
}

b2Body *GestorFisicas::crearCuerpoBox2D(const b2BodyDef *def)
{
    return mundoBox2D->CreateBody(def);
}

void GestorFisicas::destruirCuerpoBox2D(b2Body *cuerpo)
{
    mundoBox2D->DestroyBody(cuerpo);
}

FisicasCuerpo *GestorFisicas::crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas)
{
    FisicasCuerpo *nuevo = new FisicasCuerpo(objeto, fbanderas);
    cuerposBox2D.push_back(nuevo);
    return nuevo;
}

FisicasCuerpo *GestorFisicas::crearFCuerpo(Objeto *objeto, FCuerpoBanderas fbanderas, const FMaterial &material,
                                           FGrupoColision miGrupo, FGrupoColision colisionarCon)
{
    FisicasCuerpo *nuevo = crearFCuerpo(objeto, fbanderas);
    if (nuevo)
        nuevo->agregarColisionador(material, miGrupo, colisionarCon);
    return nuevo;
}

void GestorFisicas::destruirFCuerpo(FisicasCuerpo *cuerpo)
{
    if (!cuerpo)
        return;
    cuerposBox2D.erase(std::remove(cuerposBox2D.begin(), cuerposBox2D.end(), cuerpo), cuerposBox2D.end());
    delete cuerpo;
}

void GestorFisicas::actualizarFisicas()
{
    mundoBox2D->Step(1.f / 60.f, velocidadIteraciones, posicionIteraciones);
}

void GestorFisicas::limpiarFuerzas()
{
    mundoBox2D->ClearForces();
}

void GestorFisicas::BeginContact(b2Contact *contacto)
{
    FisicasCuerpo *fcuerpo1 = (FisicasCuerpo *) contacto->GetFixtureA()->GetBody()->GetUserData().pointer;
    Objeto *o1 = fcuerpo1->objeto;
    FisicasCuerpo *fcuerpo2 = (FisicasCuerpo *) contacto->GetFixtureB()->GetBody()->GetUserData().pointer;
    Objeto *o2 = fcuerpo2->objeto;

    if (contacto->IsTouching())
    {
        o1->habilitarProcesadoFisicas = true;
        o2->habilitarProcesadoFisicas = true;
        std::cout << "Colisionando: " << o1->nombre << " - " << o2->nombre << std::endl;
        int npuntosContacto = contacto->GetManifold()->pointCount;
        b2WorldManifold puntosMundiales;

        contacto->GetWorldManifold(&puntosMundiales);
        std::cout << "Puntos de Contacto Mundiales..." << std::endl;
        for (int i = 0; i < npuntosContacto; ++i)
        {
            Rectangle r = {Convertir::MetrosEnPixeles(puntosMundiales.points[i].x), Convertir::MetrosEnPixeles(puntosMundiales.points[i].y), 10.f, 10.f};
            DrawRectangleRec(r, GREEN);
            std::cout << "( " << puntosMundiales.points[i].x << ", " << puntosMundiales.points[i].y << ")" << std::endl;
        }
    }
}

void GestorFisicas::EndContact(b2Contact *contacto)
{
    // Nada por el momento
}

#include <iostream>

void GestorFisicas::PreSolve(b2Contact *contacto, const b2Manifold *colector)
{
    b2Fixture *accesorioA = contacto->GetFixtureA();
    b2Fixture *accesorioB = contacto->GetFixtureB();

    Objeto *o1 = retObjetoDeFixture(contacto->GetFixtureA());
    Objeto *o2 = retObjetoDeFixture(contacto->GetFixtureB());

    if (o1 == nullptr || o2 == nullptr)
        return;
    
    bool habilitarColision = false;
    
    if (CheckGrupoColision(accesorioA, FGRUPO_OBSTACULO))
    {
        // Colision de un objeto con algun obstaculo (mapa o muro)
        habilitarColision = DeberiaColisionar_ObstaculoConObjeto(contacto, accesorioA, accesorioB);
    }

    else if (CheckGrupoColision(accesorioB, FGRUPO_OBSTACULO))
    {
        // Colision de un objeto con algun obstaculo (mapa o muro)
        habilitarColision = DeberiaColisionar_ObstaculoConObjeto(contacto, accesorioB, accesorioA);
    }
    else
    {
        habilitarColision = DeberiaColisionar_ObjetoConObjeto(contacto, accesorioA, accesorioB);
    }

    contacto->SetEnabled(habilitarColision);
}

void GestorFisicas::PostSolve(b2Contact *contacto, const b2ContactImpulse *impulso)
{
    // Nada por el momento
}

bool GestorFisicas::DeberiaColisionar_ObstaculoConObjeto(b2Contact *contacto, b2Fixture *obstaculoAccesorio, b2Fixture *objetoAccesorio)
{
    Objeto *objeto = retObjetoDeFixture(objetoAccesorio);
    if (!objeto)
        return false;
    if (objeto->esClaseBala())
    {
        Bala *bala = ObjetoEnBala(objeto);
        bala->explotar(); // Colisiono un obstaculo con una bala...entonces explotamos
        return false;
    }
    return true;
}

bool GestorFisicas::DeberiaColisionar_ObjetoConObjeto(b2Contact *contacto, b2Fixture *objetoAccesorioA, b2Fixture *objetoAccesorioB)
{
    // Colision entre autos, si debe suceder
    if (CheckGrupoColision(objetoAccesorioA, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_JUGADOR)) &&
        CheckGrupoColision(objetoAccesorioB, (FGrupoColision) (FGRUPO_AUTO | FGRUPO_ENEMIGO | FGRUPO_JUGADOR)))
        return true;

    Objeto *objetoA = retObjetoDeFixture(objetoAccesorioA);
    Objeto *objetoB = retObjetoDeFixture(objetoAccesorioB);
    
    if (!objetoA || !objetoB)
        return false;

    // Resto de colision
    // Bala con Auto
    if (objetoA->esClaseBala() && !objetoB->esClaseEquipamiento())
        ResolverColision_AutoConBala(objetoB, objetoA);
    if (objetoB->esClaseBala() && !objetoA->esClaseEquipamiento())
        ResolverColision_AutoConBala(objetoA, objetoB);

    // Equipamiento con Auto
    if (objetoA->esClaseEquipamiento() && (objetoB->esClaseAuto() || objetoB->esClaseEnemigo() || objetoB->esClaseJugador()))
        ResolverColision_AutoConEquipamiento(objetoB, objetoA);
    if (objetoB->esClaseEquipamiento() && (objetoA->esClaseAuto() || objetoA->esClaseEnemigo() || objetoA->esClaseJugador()))
        ResolverColision_AutoConEquipamiento(objetoA, objetoB);

    return false; // Ante cualquier otra colision (bala - equipamiento, auto - equipamiento)
}

void GestorFisicas::ResolverColision_AutoConBala(Objeto *ovehiculo, Objeto *obala)
{
    Bala *bala = ObjetoEnBala(obala);
    // La verdad es que no se por que no funciona solo convirtiendo a "Auto"
    Auto *vehiculo = (ovehiculo->esClaseJugador() ? ObjetoEnJugador(ovehiculo) : ObjetoEnAuto(ovehiculo));

    // TODO: Si alguno de los 2 es null entonces hay acciones que se dejaron por alto
    // Talvez imprimir un mensaje a aqui. Pero hasta este momento ninguno los dos deberia
    // ser null, lo unico es que el cuando convertir un "Objeto" a "Auto", entonces daba null
    // por que la clase era "Jugador". Extranio la verdad :D
    if (!bala || !vehiculo)
        return;
    if (bala->autor == vehiculo->ID) // El mismo auto que disparo, normalmente solo sucede cuando comienza el disparo
        return;
    if (!bala->marcadoParaBorrar)
    {
        vehiculo->vida -= bala->efecto;
        bala->explotar();
    }
}

void GestorFisicas::ResolverColision_AutoConEquipamiento(Objeto *ovehiculo, Objeto * oequipamiento)
{
    Equipamiento *equipamiento = ObjetoEnEquipamiento(oequipamiento);
    Auto *vehiculo = (ovehiculo->esClaseJugador() ? ObjetoEnJugador(ovehiculo) : ObjetoEnAuto(ovehiculo));
    if (!equipamiento || !vehiculo)
        return;

    if (equipamiento->visible)
    {
        if (equipamiento->tipo == EQUIP_VIDA)
            vehiculo->vida += equipamiento->ganancia;
        else
            vehiculo->inventario->ingresar(equipamiento->tipoBala, equipamiento->ganancia);
        equipamiento->desaparecer(); // Desaparecer
    }
}
