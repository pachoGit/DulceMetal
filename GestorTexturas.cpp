#include "GestorTexturas.hpp"

GestorTexturas::GestorTexturas() {}

GestorTexturas::~GestorTexturas()
{
    if (texturas.size() > 0)
    {
        for (auto &t : texturas)
        {
            UnloadTexture(t->textura);
            delete t;
        }
        texturas.clear();
    }
}

void GestorTexturas::cargarTexturas()
{
    // Esta ruta es cuando es ejecutado desde la carpeta producto
    //texturas.push_back(new InfoTextura("principal", LoadTexture("../recursos/texturas.png")));
    texturas.push_back(new InfoTextura("principal", LoadTexture("../recursos/textura_autos.png")));
}

Texture2D GestorTexturas::retTextura(std::string nombre) const
{
    Texture2D tex = {0};
    for (auto &t : texturas)
        if (t->nombre == nombre)
            return t->textura;
    return tex;
}

