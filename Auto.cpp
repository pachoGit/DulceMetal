#include "Auto.hpp"
#include "Motor.hpp"
#include "Config.hpp"
#include "Bala.hpp"
#include "Util.hpp"
#include "Convertir.hpp"

#include <algorithm>

Auto::Auto(Vector2 _posicion, TipoAuto _tipo, unsigned _ID) : Objeto(_posicion)
{
    tipoAuto = _tipo;
    ID = _ID;
    auto data = dataAuto.at(tipoAuto);
    espacio.width = Config::DIM_AUTO.x;
    espacio.height = Config::DIM_AUTO.y;
    sprite = Motor::retMotor().retGestorSprites()->retSprite(data.nombre);
    velocidad = {3.0f, 3.0f};
    tipoClase = CLASE_AUTO;
    fcuerpo = Motor::retMotor().retGestorFisicas()->crearFCuerpo(this,
                                                                 FCUERPO_DEFECTO,
                                                                 FMaterial(80.f, 0.0f, 0.0f),
                                                                 FGRUPO_AUTO,
                                                                 (FGrupoColision) (FGRUPO_AUTO | FGRUPO_JUGADOR | FGRUPO_OBSTACULO | FGRUPO_BALA | FGRUPO_EQUIPAMIENTO));
    vida = Config::MAX_VIDA;
    nombre = "Auto";
    inventario = new Inventario();
    tipoBala = BALA_FUEGO;
    iniciarBarraVida();
}

Auto::~Auto()
{
    // Borrar las balas
    if (balas.size() > 0)
    {
        for (auto &bala : balas)
            delete bala;
        balas.clear();
    }
    if (barraVida != nullptr)
    {
        delete barraVida;
        barraVida = nullptr;
    }
    if (inventario != nullptr)
    {
        delete inventario;
        inventario = nullptr;
    }
}

void Auto::actualizar(float dt)
{
    if (animacion != nullptr)
    {
        animacion->actualizar(dt);
        return;
    }
    procesarFisicas();
    sincronizarObjetoConFisicas();
    for (auto &bala : balas)
        bala->actualizar(dt);
    actualizarBarraVida();
    eliminarBalasDeMemoria();
}

void Auto::procesarFisicas()
{
    actualizarFriccion();
}

void Auto::dibujar()
{
    Objeto::dibujar();
    barraVida->dibujar();
    for (auto bala : balas)
        bala->dibujar();
    // Debug fisicas
    //fcuerpo->dibujar();
}

b2Vec2 Auto::retVelocidadLateral()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return b2Vec2();
    b2Vec2 normal = cuerpo->GetWorldVector(b2Vec2(1.0f, 0.0f));
    return b2Dot(normal, cuerpo->GetLinearVelocity()) * normal;
}

b2Vec2 Auto::retVelocidadDelantera()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return b2Vec2();
    b2Vec2 normal = cuerpo->GetWorldVector(b2Vec2(0.0f, 1.0f));
    return b2Dot(normal, cuerpo->GetLinearVelocity()) * normal;
}

void Auto::reducirRotacion()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    cuerpo->ApplyAngularImpulse(0.1f * cuerpo->GetInertia() * -cuerpo->GetAngularVelocity(), true);
}

void Auto::detenerRotacion()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    cuerpo->ApplyAngularImpulse(cuerpo->GetInertia() * -cuerpo->GetAngularVelocity(), true);
}


void Auto::detenerAuto()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    b2Vec2 v = cuerpo->GetLinearVelocity();
    // TODO: No detener el auto al seco :D
    cuerpo->ApplyLinearImpulse(/* 1.0f * */cuerpo->GetMass() * -v, cuerpo->GetWorldCenter(), true);
}

void Auto::actualizarFriccion()
{
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    if (cuerpo == nullptr)
        return;
    // Eliminar la velocidad lateral
    b2Vec2 impulso = cuerpo->GetMass() * -retVelocidadLateral();
    cuerpo->ApplyLinearImpulse(impulso, cuerpo->GetWorldCenter(), true);

    // Reducir la rotacion
    reducirRotacion();
    
    // Reducir la velocidad delantera
    b2Vec2 vdelantera = retVelocidadDelantera();
    float v = vdelantera.Normalize();
    float arrastre = -2 * v;
    cuerpo->ApplyLinearImpulse(arrastre * vdelantera, cuerpo->GetWorldCenter(), true);
}

void Auto::iniciarBarraVida()
{
    Vector2 np = Convertir::MetrosEnPixeles(posicion);
    np.x -= Convertir::MetrosEnPixeles(espacio.width) * 0.5;
    np.y -= Convertir::MetrosEnPixeles(espacio.height) * 0.5 + 10;
    barraVida = new BarraVida(np, vida);
}

void Auto::actualizarBarraVida()
{
    Vector2 np = Convertir::MetrosEnPixeles(posicion);
    np.x -= Convertir::MetrosEnPixeles(espacio.width) * 0.5;      
    np.y -= Convertir::MetrosEnPixeles(espacio.height) * 0.5 + 10;
    barraVida->actualizar(np, vida);
}

void Auto::disparar()
{
    std::vector<Vector2> vertices = Util::retVerticesRectangulo(espacio, (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, angulo);
    Vector2 arribaIzquierda = vertices.at(0);
    Vector2 arribaDerecha = vertices.at(1);

    if (tipoBala != BALA_BASICA)
    {

        Bala *b1 = new Bala(Util::retPuntoCentral(arribaIzquierda, arribaDerecha), tipoBala, ID);
        b1->ingAngulo(angulo);
        balas.push_back(b1);
        inventario->disminuir(tipoBala, 1); // Quitar la bala lanzada del inventario
    }
    else
    {
        Bala *b1 = new Bala((Vector2){arribaIzquierda.x, arribaIzquierda.y}, tipoBala, ID);
        b1->ingAngulo(angulo);
        Bala *b2 = new Bala((Vector2){arribaDerecha.x, arribaDerecha.y}, tipoBala, ID);
        b2->ingAngulo(angulo);
        balas.push_back(b1);
        balas.push_back(b2);
    }
}

void Auto::explotar()
{
    if (marcadoParaBorrar == true)
        return;
    if (animacion != nullptr)
    {
        delete animacion;
        animacion = nullptr;
    }
    animacion = new Animacion(posicion, dataAuto.at(tipoAuto).texplosion);
    marcadoParaBorrar = true;
}


void Auto::impulsarHaciaAdelante()
{
    if (fcuerpo == nullptr)
        return;
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    float longitud = espacio.height;
    b2Vec2 impulso(longitud * std::sin(cuerpo->GetAngle()), longitud * std::cos(cuerpo->GetAngle()) * -1);
    cuerpo->ApplyLinearImpulse(10.0f * impulso, cuerpo->GetWorldCenter(), true);
}

void Auto::impulsarHaciaAtras()
{
    if (fcuerpo == nullptr)
        return;
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    float longitud = espacio.height;
    b2Vec2 impulso(longitud * std::sin(cuerpo->GetAngle()), longitud * std::cos(cuerpo->GetAngle()) * -1);
    cuerpo->ApplyLinearImpulse(-(10.0f * impulso), cuerpo->GetWorldCenter(), true);
}

void Auto::girarHaciaDerecha()
{
    if (fcuerpo == nullptr)
        return;
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    cuerpo->ApplyAngularImpulse(2.0f, true);
}

void Auto::girarHaciaIzquierda()
{
    if (fcuerpo == nullptr)
        return;
    b2Body *cuerpo = fcuerpo->retCuerpoBox2D();
    cuerpo->ApplyAngularImpulse(-2.0f, true);
}

void Auto::eliminarBalasDeMemoria()
{
    balas.erase(std::remove_if(balas.begin(), balas.end(), [] (Bala *bala) {
                if (bala->marcadoParaBorrar && !bala->animacion->estaCorriendo)
                {
                    delete bala;
                    return true;
                }
                return false;
            }), balas.end());
}

void Auto::girarHasta(int anguloDestino)
{
    int iangulo = (int) angulo; // Conversion a entero
    if (anguloDestino == iangulo)
    {
        detenerRotacion();
    }
    else
    {
        if (iangulo < anguloDestino)
            girarHaciaDerecha();
        else
            girarHaciaIzquierda();
    }
}

