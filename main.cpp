#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "mascota.h"

using namespace std;

// Mostrar mascotas
// T(n) = n
// Complejidad: O(n)
// La funcion recorre todos los elementos del vector
// para imprimir la informacion de cada mascota.
void mostrarMascotas(vector<Mascota> &mascotas) {
    for (int i = 0; i < mascotas.size(); i++) {
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

bool compararMascotas(Mascota a, Mascota b, int criterio) {
    if (criterio == 1) {
        return a.get_fecha() < b.get_fecha();
    }
    else {
        return a.get_zona() < b.get_zona();
    }
}

// Funcion merge
// Complejidad temporal: O(n)
// Complejidad espacial: O(n)
// La funcion copia los elementos de las dos mitades en vectores
// temporales y despues los recorre para volver a colocarlos
// ordenados en el vector original.
// En total se procesan n elementos, por eso el tiempo es O(n).
// Se utilizan vectores temporales que pueden almacenar en conjunto
// hasta n elementos, por eso el espacio adicional es O(n).
void merge(vector<Mascota> &mascotas, int izquierda, int mitad,
           int derecha, int criterio) {

    vector<Mascota> izquierdaTemp;
    vector<Mascota> derechaTemp;

    for (int i = izquierda; i <= mitad; i++) {
        izquierdaTemp.push_back(mascotas[i]);
    }

    for (int i = mitad + 1; i <= derecha; i++) {
        derechaTemp.push_back(mascotas[i]);
    }

    int i = 0;
    int j = 0;
    int k = izquierda;

    while (i < izquierdaTemp.size() && j < derechaTemp.size()) {

        if (compararMascotas(izquierdaTemp[i], derechaTemp[j], criterio)) {
            mascotas[k] = izquierdaTemp[i];
            i++;
        }
        else {
            mascotas[k] = derechaTemp[j];
            j++;
        }

        k++;
    }

    while (i < izquierdaTemp.size()) {
        mascotas[k] = izquierdaTemp[i];
        i++;
        k++;
    }

    while (j < derechaTemp.size()) {
        mascotas[k] = derechaTemp[j];
        j++;
        k++;
    }
}
// Merge Sort
// Mejor caso: O(n log n)
// Caso promedio: O(n log n)
// Peor caso: O(n log n)
// El arreglo se divide en mitades hasta llegar a elementos individuales.
// Esto genera aproximadamente log n niveles de division.
// En cada nivel, la funcion merge recorre en total n elementos.
// Por eso:
// T(n) = 2T(n/2) + O(n)
// y la complejidad resultante es:
// O(n log n)
void mergeSort(vector<Mascota> &mascotas, int izquierda,
               int derecha, int criterio) {

    if (izquierda < derecha) {
        int mitad = (izquierda + derecha) / 2;

        mergeSort(mascotas, izquierda, mitad, criterio);
        mergeSort(mascotas, mitad + 1, derecha, criterio);

        merge(mascotas, izquierda, mitad, derecha, criterio);
    }
}

// Busqueda secuencial por zona
// T(n) = n
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todas las mascotas del vector,
// incluso si encuentra una coincidencia, ya que pueden
// existir varias mascotas registradas en la misma zona.
void buscarPorZona(vector<Mascota> &mascotas, string zonaBuscada) {

    bool encontrada = false;

    for (int i = 0; i < mascotas.size(); i++) {

        if (mascotas[i].get_zona() == zonaBuscada) {

            cout << mascotas[i].get_id() << " | "
                 << mascotas[i].get_nombre() << " | "
                 << mascotas[i].get_especie() << " | "
                 << mascotas[i].get_raza() << " | "
                 << mascotas[i].get_color() << " | "
                 << mascotas[i].get_tamano() << " | "
                 << mascotas[i].get_zona() << " | "
                 << mascotas[i].get_fecha() << endl;

            encontrada = true;
        }
    }

    if (!encontrada) {
        cout << "No se encontraron mascotas en esa zona." << endl;
    }
}
void cargarMascotas(vector<Mascota> &mascotas, string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
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

        mascotas.push_back(nuevaMascota);
    }

    archivo.close();
}

int main() {
    // Estructura principal: vector<Mascota>
    // Acceso por indice: O(1)
    // size(): O(1)
    // Insercion al final con push_back(): O(1) amortizado
    // En el peor caso, push_back() puede ser O(n) si el vector
    // necesita aumentar su capacidad y copiar los elementos.
    vector<Mascota> mascotas;

    cargarMascotas(mascotas, "mascotas.txt");

    cout << "Se cargaron " << mascotas.size() << " mascotas." << endl;

    int opcion;
    do {
        cout << "===== PETFINDER =====" << endl;
        cout << "1. Mostrar mascotas" << endl;
        cout << "2. Ordenar por fecha" << endl;
        cout << "3. Ordenar por zona" << endl;
        cout << "4. Buscar por zona" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        if (opcion == 1) {
            mostrarMascotas(mascotas);
        }
        else if (opcion == 2) {
            mergeSort(mascotas, 0, mascotas.size() - 1, 1);
            mostrarMascotas(mascotas);
        }
        else if (opcion == 3) {
            mergeSort(mascotas, 0, mascotas.size() - 1, 2);
            mostrarMascotas(mascotas);
        }
        else if (opcion == 4) {
            string zonaBuscada;

            cout << "Ingresa la zona que quieres buscar: ";
            cin.ignore();
            getline(cin, zonaBuscada);

            buscarPorZona(mascotas, zonaBuscada);
        }
        else if (opcion == 5) {
            cout << "Saliendo de PetFinder..." << endl;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 5);

    return 0;
}