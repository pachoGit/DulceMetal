#ifndef GESTORTEXTURAS_HPP
#define GESTORTEXTURAS_HPP

#include <string>
#include <vector>

#include <raylib.h>

struct InfoTextura
{
    std::string nombre;
    Texture2D textura;

    InfoTextura(std::string _nombre, Texture2D _textura)
    {
        nombre = _nombre;
        textura = _textura;
    }
};

class GestorTexturas
{
  private:
    
    std::vector<InfoTextura *> texturas;

  public:

    GestorTexturas();

    ~GestorTexturas();

    void cargarTexturas();

    Texture2D retTextura(std::string nombre) const;

};


#endif /* GESTORTEXTURAS_HPP */
