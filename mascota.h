#ifndef MASCOTA_H
#define MASCOTA_H   

#include <string>

using namespace std;

class Mascota{
    private:
    int id;
    string nombre;
    string especie;
    string raza;
    string color;
    string tamano;
    string zona;
    string fecha;

    public:
    Mascota(): id(0), nombre(""), especie(""), raza(""), 
    color(""), tamano(""), zona(""), fecha("") {}

    Mascota(int c_id, string c_nombre, string c_especie,
        string c_raza, string c_color, string c_tamano,
        string c_zona, string c_fecha)
    : id(c_id), nombre(c_nombre), especie(c_especie),
      raza(c_raza), color(c_color), tamano(c_tamano),
      zona(c_zona), fecha(c_fecha) {}

    int get_id() {
    return id;
    }
    
    string get_nombre() {
    return nombre;
    }

    string get_especie() {
    return especie;
    }

    string get_raza() {
    return raza;
    }

    string get_color() {
    return color;
    }
    
    string get_tamano() {
    return tamano;
    }

    string get_zona() {
    return zona;
    }

    string get_fecha() {
    return fecha;
    }

    void set_nombre(string c_nombre) {
    nombre = c_nombre;
    }

    void set_especie(string c_especie) {
    especie = c_especie;
    }

    void set_raza(string c_raza) {
    raza = c_raza;
    }

    void set_color(string c_color) {
    color = c_color;
    }

    void set_tamano(string c_tamano) {
    tamano = c_tamano;
    }

    void set_zona(string c_zona) {
    zona = c_zona;
    }

    void set_fecha(string c_fecha) {
    fecha = c_fecha;
    }

    void set_id(int c_id) {
    id = c_id;
    }
};

#endif