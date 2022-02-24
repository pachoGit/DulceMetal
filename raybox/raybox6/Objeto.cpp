#include "Objeto.hpp"

Objeto::Objeto(Rectangle _espacio, Vector2 _posicion, float _anguloRotacion)
{
    espacio = _espacio;
    posicion = _posicion;
    anguloRotacion = _anguloRotacion;
    color = RED;
    velocidad = (Vector2) {100.f, 100.f};
    fcuerpo = nullptr;
    habilitarControles = false;
    nombre = "Objeto";
}

void Objeto::Destruir(b2World *mundo)
{
    if (fcuerpo != nullptr)
    {
        fcuerpo->Destruir(mundo);
        delete fcuerpo;
        fcuerpo = nullptr;
    }
}

void Objeto::actualizar(float dt)
{
    if (habilitarControles == false)
    {
        if (fcuerpo->cuerpoBox2D->GetType() != b2_staticBody)
            sincronizarObjetoConFisicas();
        return;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        anguloRotacion += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        anguloRotacion -= 1.0f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        posicion.x += std::sin(anguloRotacion * DEG2RAD) * dt * velocidad.x;
        posicion.y -= std::cos(anguloRotacion * DEG2RAD) * dt * velocidad.y;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        posicion.x -= std::sin(anguloRotacion * DEG2RAD) * dt * velocidad.x;
        posicion.y += std::cos(anguloRotacion * DEG2RAD) * dt * velocidad.y;
    }
    // 
    sincronizarFisicasConObjeto();
}

void Objeto::dibujar()
{
    espacio.x = posicion.x;
    espacio.y = posicion.y;

    auto arreglarPosicion = [&] () {
                                Rectangle nuevo;
                                nuevo.x = espacio.x + (espacio.width / 2.f);
                                nuevo.y = espacio.y + (espacio.height / 2.f);
                                nuevo.width =  espacio.width;
                                nuevo.height = espacio.height;
                                return nuevo;
                            };

    DrawRectanglePro(arreglarPosicion(), (Vector2) {espacio.width / 2.f, espacio.height / 2.f}, anguloRotacion, color);
    // Dibujar las fisicas
    
    Rectangle r_fisicas = {fcuerpo->retPosicion().x + (espacio.width / 2.f), fcuerpo->retPosicion().y + (espacio.height /2.f), espacio.width, espacio.height};
    DrawRectangleLinesPro(r_fisicas, (Vector2) {r_fisicas.width / 2.f, r_fisicas.height / 2.f}, fcuerpo->retAngulo(), BLUE);
}

void Objeto::agregarFisicas(const FMaterial &fmaterial, b2BodyType ftipo, b2World *mundo)
{
    fcuerpo = new FisicasCuerpo(this, fmaterial, ftipo);
    if (fcuerpo == nullptr)
        return;
    fcuerpo->Iniciar(mundo);
    fcuerpo->agregarDataUsuario(this);
}

void Objeto::sincronizarObjetoConFisicas()
{
    posicion = fcuerpo->retPosicion();
    anguloRotacion = fcuerpo->retAngulo();
}

void Objeto::sincronizarFisicasConObjeto()
{
    fcuerpo->transformar(posicion, anguloRotacion);
}

void Objeto::DrawRectangleLinesPro(Rectangle rect, Vector2 protacion, float angulo, Color color)
{
    Vector2 arribaIzquierda = {0};
    Vector2 arribaDerecha = {0};
    Vector2 abajoIzquierda = {0};
    Vector2 abajoDerecha = {0};

    float senoRotacion = std::sin(angulo * DEG2RAD);
    float cosenoRotacion = std::cos(angulo * DEG2RAD);
    float x = rect.x;
    float y = rect.y;
    float dx = -protacion.x;
    float dy = -protacion.y;

    arribaIzquierda.x = x + dx * cosenoRotacion - dy * senoRotacion;
    arribaIzquierda.y = y + dx * senoRotacion   + dy * cosenoRotacion;

    arribaDerecha.x = x + (dx + rect.width) * cosenoRotacion - dy * senoRotacion;
    arribaDerecha.y = y + (dx + rect.width) * senoRotacion   + dy * cosenoRotacion;

    abajoIzquierda.x = x + dx * cosenoRotacion - (dy + rect.height) * senoRotacion;
    abajoIzquierda.y = y + dx * senoRotacion   + (dy + rect.height) * cosenoRotacion;
    
    abajoDerecha.x = x + (dx + rect.width) * cosenoRotacion - (dy + rect.height) * senoRotacion;
    abajoDerecha.y = y + (dx + rect.width) * senoRotacion   + (dy + rect.height) * cosenoRotacion;
    

    DrawLineV(arribaIzquierda, arribaDerecha, color);
    DrawLineV(arribaDerecha, abajoDerecha, color);
    DrawLineV(abajoDerecha, abajoIzquierda, color);
    DrawLineV(abajoIzquierda, arribaIzquierda, color);
}

