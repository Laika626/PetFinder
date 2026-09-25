#include <iostream>
#include <fstream>
#include <sstream>
#include "mascota.h"

using namespace std;

void mostrarMascotas(Mascota mascotas[], int numMascotas) {
    for (int i = 0; i < numMascotas; i++) {
        cout << mascotas[i].get_id() << " | "
             << mascotas[i].get_nombre() << " | "
             << mascotas[i].get_especie() << " | "
             << mascotas[i].get_raza() << " | "
             << mascotas[i].get_color() << " | "
             << mascotas[i].get_tamano() << " | "
             << mascotas[i].get_zona() << " | "
             << mascotas[i].get_fecha() << endl;
    }
}

void ordenarPorFecha(Mascota mascotas[], int numMascotas) {
    for (int i = 1; i < numMascotas; i++) {
        Mascota actual = mascotas[i];
        int j = i - 1;
        while (j >= 0 && mascotas[j].get_fecha() > actual.get_fecha()) {
            mascotas[j + 1] = mascotas[j];
            j--;
        }
        mascotas[j + 1] = actual;
    }
}

void ordenarPorZona(Mascota mascotas[], int numMascotas) {
    for (int i = 1; i < numMascotas; i++) {
        Mascota actual = mascotas[i];
        int j = i - 1;
        while (j >= 0 && mascotas[j].get_zona() > actual.get_zona()) {
            mascotas[j + 1] = mascotas[j];
            j--;
        }
        mascotas[j + 1] = actual;
    }
}

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

    int opcion;
    do {
        cout << "===== PETFINDER =====" << endl;
        cout << "1. Mostrar mascotas" << endl;
        cout << "2. Ordenar por fecha" << endl;
        cout << "3. Ordenar por zona" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        if (opcion == 1) {
            mostrarMascotas(mascotas, numMascotas);
        }
        else if (opcion == 2) {
            ordenarPorFecha(mascotas, numMascotas);
            mostrarMascotas(mascotas, numMascotas);
        }
        else if (opcion == 3) {
            ordenarPorZona(mascotas, numMascotas);
            mostrarMascotas(mascotas, numMascotas);
        }
        else if (opcion == 4) {
            cout << "Saliendo de PetFinder..." << endl;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 4);

    return 0;
}