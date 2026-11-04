#include <iostream>
#include <fstream>
#include <sstream>
#include "mascota.h"
#include "dlist.h"

using namespace std;

void guardarMascotas(DList<Mascota> &listaMascotas,
                     string nombreArchivo);

// Complejidad de mostrarMascotas:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos de la DList
// desde head hasta llegar al final.
// Cada mascota se consulta e imprime una sola vez.
// Por lo tanto, la complejidad de mostrarMascotas es O(n).
void mostrarMascotas(DList<Mascota> &listaMascotas) {

    DLink<Mascota>* actual = listaMascotas.getHead();

    while (actual != 0) {

        Mascota mascota = actual->getValue();

        cout << mascota.get_id() << " | "
             << mascota.get_nombre() << " | "
             << mascota.get_especie() << " | "
             << mascota.get_raza() << " | "
             << mascota.get_color() << " | "
             << mascota.get_tamano() << " | "
             << mascota.get_zona() << " | "
             << mascota.get_fecha() << endl;

        actual = actual->getNext();
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

// Complejidad de buscarPorZona:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos de la DList,
// ya que pueden existir varias mascotas registradas
// en la misma zona.
// Por lo tanto, incluso si encuentra una coincidencia
// al inicio, continua recorriendo la lista completa.
// La complejidad de buscarPorZona es O(n).
void buscarPorZona(DList<Mascota> &listaMascotas, string zonaBuscada) {

    DLink<Mascota>* actual = listaMascotas.getHead();

    bool encontrada = false;

    while (actual != 0) {

        Mascota mascota = actual->getValue();

        if (mascota.get_zona() == zonaBuscada) {

            cout << mascota.get_id() << " | "
                 << mascota.get_nombre() << " | "
                 << mascota.get_especie() << " | "
                 << mascota.get_raza() << " | "
                 << mascota.get_color() << " | "
                 << mascota.get_tamano() << " | "
                 << mascota.get_zona() << " | "
                 << mascota.get_fecha() << endl;

            encontrada = true;
        }

        actual = actual->getNext();
    }

    if (!encontrada) {
        cout << "No se encontraron mascotas en esa zona." << endl;
    }
}

// Complejidad de cargarMascotas:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion lee los n registros almacenados en el archivo.
// Cada mascota se inserta al final de la DList mediante
// insertion(), cuya complejidad es O(1).
// n * O(1) = O(n)
// Por lo tanto, la complejidad de cargarMascotas es O(n).
void cargarMascotas(DList<Mascota> &listaMascotas, string nombreArchivo){

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

        listaMascotas.insertion(nuevaMascota);

        guardarMascotas(listaMascotas, "mascotas.txt");
        cout << "Mascota registrada correctamente." << endl;
    }

    archivo.close();
}

// Complejidad de guardarMascotas:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos de la DList
// y escribe cada mascota una sola vez en el archivo.
// Por lo tanto, la complejidad de guardarMascotas es O(n).
void guardarMascotas(DList<Mascota> &listaMascotas,
                     string nombreArchivo) {

    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo para guardar." << endl;
        return;
    }

    DLink<Mascota>* actual = listaMascotas.getHead();

    while (actual != 0) {

        Mascota mascota = actual->getValue();

        archivo << mascota.get_id() << "|"
                << mascota.get_nombre() << "|"
                << mascota.get_especie() << "|"
                << mascota.get_raza() << "|"
                << mascota.get_color() << "|"
                << mascota.get_tamano() << "|"
                << mascota.get_zona() << "|"
                << mascota.get_fecha() << endl;

        actual = actual->getNext();
    }

    archivo.close();

    cout << "Datos guardados correctamente." << endl;
}

// Complejidad de registrarMascota:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// Crear la nueva mascota e insertarla al final de la DList
// mediante insertion() tiene complejidad O(1).
// Despues se llama a guardarMascotas(), que recorre
// los n nodos para actualizar el archivo y cuesta O(n).
// O(1) + O(n) = O(n)
// Por lo tanto, la complejidad final de registrarMascota
// es O(n).
void registrarMascota(DList<Mascota> &listaMascotas) {

    int id;
    string nombre;
    string especie;
    string raza;
    string color;
    string tamano;
    string zona;
    string fecha;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Especie: ";
    getline(cin, especie);

    cout << "Raza: ";
    getline(cin, raza);

    cout << "Color: ";
    getline(cin, color);

    cout << "Tamano: ";
    getline(cin, tamano);

    cout << "Zona: ";
    getline(cin, zona);

    cout << "Fecha (AAAA-MM-DD): ";
    getline(cin, fecha);

    Mascota nuevaMascota(id, nombre, especie, raza,
                         color, tamano, zona, fecha);

    listaMascotas.insertion(nuevaMascota);

    guardarMascotas(listaMascotas, "mascotas.txt");

    cout << "Mascota registrada correctamente." << endl;
}

// Complejidad de eliminarMascota:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// Primero se recorre la DList para encontrar el ID,
// lo cual puede requerir hasta n comparaciones.
// Despues se utiliza deleteAt(), que en el peor caso
// puede recorrer nuevamente hasta n nodos.
// Finalmente se llama a guardarMascotas(), que recorre
// toda la lista para actualizar el archivo.
// O(n) + O(n) + O(n) = O(n)
// Por lo tanto, la complejidad final de eliminarMascota
// es O(n).
void eliminarMascota(DList<Mascota> &listaMascotas) {

    int idBuscado;
    int posicion = 0;
    int posicionEncontrada = -1;

    cout << "Ingresa el ID de la mascota que quieres eliminar: ";
    cin >> idBuscado;

    DLink<Mascota>* actual = listaMascotas.getHead();

    while (actual != 0) {

        Mascota mascota = actual->getValue();

        if (mascota.get_id() == idBuscado) {
            posicionEncontrada = posicion;
            break;
        }

        actual = actual->getNext();
        posicion++;
    }

    if (posicionEncontrada == -1) {
        cout << "No se encontro una mascota con ese ID." << endl;
        return;
    }

    listaMascotas.deleteAt(posicionEncontrada);

    guardarMascotas(listaMascotas, "mascotas.txt");

    cout << "Mascota eliminada correctamente." << endl;
}

int main() {

    DList<Mascota> listaMascotas;

    cargarMascotas(listaMascotas, "mascotas.txt");

    cout << "Se cargaron " << listaMascotas.getSize() << " mascotas." << endl;

    int opcion;
    do {
        cout << "===== PETFINDER =====" << endl;
        cout << "1. Mostrar mascotas" << endl;
        cout << "2. Ordenar por fecha" << endl;
        cout << "3. Ordenar por zona" << endl;
        cout << "4. Buscar por zona" << endl;
        cout << "5. Registrar mascota" << endl;
        cout << "6. Eliminar mascota" << endl;
        cout << "7. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        if (opcion == 1) {
            mostrarMascotas(listaMascotas);
        }
        else if (opcion == 2) {
            listaMascotas.mergeSort(1, compararMascotas);
            mostrarMascotas(listaMascotas);
        }
        else if (opcion == 3) {
            listaMascotas.mergeSort(2, compararMascotas);
            mostrarMascotas(listaMascotas);
        }
        else if (opcion == 4) {
            string zonaBuscada;

            cout << "Ingresa la zona que quieres buscar: ";
            cin.ignore();
            getline(cin, zonaBuscada);

            buscarPorZona(listaMascotas, zonaBuscada);
        }
        else if (opcion == 5) {
            registrarMascota(listaMascotas);
        }
        else if (opcion == 6) {
            eliminarMascota(listaMascotas);
        }
        else if (opcion == 7) {
            cout << "Saliendo de PetFinder..." << endl;
        }
        else {
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 7);

    return 0;
}