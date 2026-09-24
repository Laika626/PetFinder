#include <iostream>
#include <fstream>
#include <sstream>
#include "mascota.h"

using namespace std;

int main() {

    Mascota mascotas[100];
    int numMascotas = 0;

    ifstream archivo("mascotas.txt");
    if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return 1;
    }

    string linea;

    while (getline(archivo, linea)) {
    stringstream ss(linea);
    string idTexto;
    string nombre;
    string especie;
    string raza;
    string color;
    string tamano;
    string zona;
    string fecha;

    getline(ss, idTexto, '|');
    getline(ss, nombre, '|');
    getline(ss, especie, '|');
    getline(ss, raza, '|');
    getline(ss, color, '|');
    getline(ss, tamano, '|');
    getline(ss, zona, '|');
    getline(ss, fecha, '|');
    
    int id = stoi(idTexto);

    Mascota nuevaMascota(id, nombre, especie, raza,
                     color, tamano, zona, fecha);

    mascotas[numMascotas] = nuevaMascota;
    numMascotas++;

    }

    cout << "Se cargaron " << numMascotas << " mascotas." << endl;

    return 0;
}