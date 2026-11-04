/*
Fernanda Jiménez Estrada
A01206671
*/

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;

template <class T>
class DLink {
private:
    T value;
    DLink<T>* next;
    DLink<T>* prev;

    DLink(T val) : value(val), next(0), prev(0) {}

    DLink(T val, DLink<T>* nxt, DLink<T>* prv)
        : value(val), next(nxt), prev(prv) {}

    friend class DList<T>;

public:
    T getValue() const {
        return value;
    }

    DLink<T>* getNext() const {
        return next;
    }

    DLink<T>* getPrev() const {
        return prev;
    }
};


template <class T>
class DList {
private:
    DLink<T>* head;
    DLink<T>* tail;
    int size;

    DLink<T>* split(DLink<T>* node);

    DLink<T>* mergeNodes(DLink<T>* izquierda, DLink<T>* derecha,
                     int criterio, bool (*comparar)(T, T, int));
    DLink<T>* mergeSortNodes(DLink<T>* node,
                            int criterio,
                            bool (*comparar)(T, T, int));

public:
    DList() : head(0), tail(0), size(0) {}

    ~DList();

    void insertion(T val);
    int search(T val) const;
    void update(int index, T val);
    T deleteAt(int index);

    void mergeSort(int criterio, bool (*comparar)(T, T, int));

    void clear();

    std::string toStringForward() const;
    std::string toStringBackward() const;

    int getSize() const;
    DLink<T>* getHead() const;
    DLink<T>* getTail() const;
};


template <class T>
DList<T>::~DList() {
    clear();
}

// Complejidad de clear:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion elimina todos los nodos de la lista.
// Para hacerlo recorre la estructura completa desde head
// hasta que ya no quedan nodos.
template <class T>
void DList<T>::clear() {

    while (head != 0) {

        DLink<T>* node = head;

        head = head->next;

        delete node;
    }

    tail = 0;
    size = 0;
}

// Complejidad de insertion:
// Mejor caso: O(1)
// Caso promedio: O(1)
// Peor caso: O(1)
// Se utiliza tail para insertar directamente al final,
 // por lo que no es necesario recorrer la lista.
template <class T>
void DList<T>::insertion(T val) {

    DLink<T>* node = new DLink<T>(val);

    if (head == 0) {

        head = node;
        tail = node;

    } else {

        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    size++;
}

// Complejidad de search:
// Mejor caso: O(1)
// Caso promedio: O(n)
// Peor caso: O(n)
// La busqueda comienza en head y avanza nodo por nodo.
// Si el valor esta al inicio se encuentra inmediatamente.
// Si esta al final o no existe, se recorre toda la lista.
template <class T>
int DList<T>::search(T val) const {

    DLink<T>* current = head;
    int position = 0;

    while (current != 0) {

        if (current->value == val) {
            return position;
        }

        current = current->next;
        position++;
    }

    return -1;
}

// Complejidad de update:
// Mejor caso: O(1)
// Caso promedio: O(n)
// Peor caso: O(n)
// Para actualizar un elemento se recorre la lista desde head
// hasta llegar al indice indicado.
// Si el indice es 0, el acceso es inmediato.
// Si esta cerca del final, se recorren hasta n nodos.
template <class T>
void DList<T>::update(int index, T val) {

    if (index < 0 || index >= size) {
        return;
    }

    DLink<T>* current = head;

    for (int position = 0; position < index; position++) {
        current = current->next;
    }

    current->value = val;
}

// Complejidad de deleteAt:
// Mejor caso: O(1)
// Caso promedio: O(n)
// Peor caso: O(n)
// Para eliminar un nodo se recorre la lista desde head
// hasta llegar al indice indicado.
// Si se elimina el primer nodo, no es necesario recorrer la lista.
// Si el nodo esta cerca del final, pueden recorrerse hasta n nodos.
// Una vez localizado el nodo, reconectar prev y next es O(1).
template <class T>
T DList<T>::deleteAt(int index) {

    if (index < 0 || index >= size) {
        return T();
    }

    DLink<T>* removed = head;

    for (int position = 0; position < index; position++) {
        removed = removed->next;
    }

    if (removed->prev != 0) {

        removed->prev->next = removed->next;

    } else {

        head = removed->next;
    }

    if (removed->next != 0) {

        removed->next->prev = removed->prev;

    } else {

        tail = removed->prev;
    }

    T result = removed->value;

    delete removed;

    size--;

    return result;
}

// Complejidad de toStringForward:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos desde head hasta tail
// para construir la representacion de la lista.
template <class T>
std::string DList<T>::toStringForward() const {

    std::stringstream aux;

    DLink<T>* p = head;

    aux << "[";

    while (p != 0) {

        aux << p->value;

        if (p->next != 0) {
            aux << ", ";
        }

        p = p->next;
    }

    aux << "]";

    return aux.str();
}

// Complejidad de toStringBackward:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion recorre todos los nodos desde tail hasta head
// para construir la representacion de la lista.
template <class T>
std::string DList<T>::toStringBackward() const {

    std::stringstream aux;

    DLink<T>* p = tail;

    aux << "[";

    while (p != 0) {

        aux << p->value;

        if (p->prev != 0) {
            aux << ", ";
        }

        p = p->prev;
    }

    aux << "]";

    return aux.str();
}

// Complejidad de getSize:
// Mejor caso: O(1)
// Caso promedio: O(1)
// Peor caso: O(1)
// La funcion regresa directamente el valor almacenado en size,
// por lo que no necesita recorrer la lista.
template <class T>
int DList<T>::getSize() const {

    return size;
}

// Complejidad de getHead:
// Mejor caso: O(1)
// Caso promedio: O(1)
// Peor caso: O(1)
// La funcion regresa directamente el apuntador head.
template <class T>
DLink<T>* DList<T>::getHead() const {

    return head;
}

// Complejidad de getTail:
// Mejor caso: O(1)
// Caso promedio: O(1)
// Peor caso: O(1)
// La funcion regresa directamente el apuntador tail.
template <class T>
DLink<T>* DList<T>::getTail() const {

    return tail;
}

// Complejidad de split:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion utiliza dos apuntadores para encontrar la mitad
// de la lista. Aunque rapido avanza dos nodos a la vez,
// el numero de operaciones sigue creciendo de forma lineal
// con respecto al numero de nodos.
template <class T>
DLink<T>* DList<T>::split(DLink<T>* node) {

    DLink<T>* lento = node;
    DLink<T>* rapido = node;

    while (rapido->next != 0 && rapido->next->next != 0) {
        lento = lento->next;
        rapido = rapido->next->next;
    }

    DLink<T>* segundaMitad = lento->next;

    lento->next = 0;

    if (segundaMitad != 0) {
        segundaMitad->prev = 0;
    }

    return segundaMitad;
}

// Complejidad de mergeNodes:
// Mejor caso: O(n)
// Caso promedio: O(n)
// Peor caso: O(n)
// La funcion combina dos mitades ordenadas.
// En cada llamada se coloca un nodo en la lista resultado
// hasta que una de las dos mitades queda vacia.
// El numero de operaciones crece linealmente con la
// cantidad total de nodos que se estan combinando.
template <class T>
DLink<T>* DList<T>::mergeNodes(DLink<T>* izquierda,
                                DLink<T>* derecha,
                                int criterio,
                                bool (*comparar)(T, T, int)) {

    if (izquierda == 0) {
        return derecha;
    }

    if (derecha == 0) {
        return izquierda;
    }

    DLink<T>* resultado;

    if (!comparar(derecha->value, izquierda->value, criterio)) {

        resultado = izquierda;

        resultado->next = mergeNodes(
            izquierda->next,
            derecha,
            criterio,
            comparar
        );

    } else {

        resultado = derecha;

        resultado->next = mergeNodes(
            izquierda,
            derecha->next,
            criterio,
            comparar
        );
    }

    if (resultado->next != 0) {
        resultado->next->prev = resultado;
    }

    resultado->prev = 0;

    return resultado;
}

// Complejidad de mergeSortNodes:
// Mejor caso: O(n log n)
// Caso promedio: O(n log n)
// Peor caso: O(n log n)
//
// La lista se divide recursivamente en dos mitades.
// Hay aproximadamente log n niveles de division y en cada
// nivel se procesan en total n nodos entre split y mergeNodes.
// T(n) = 2T(n/2) + O(n)
// Por lo tanto, la complejidad es O(n log n).
template <class T>
DLink<T>* DList<T>::mergeSortNodes(DLink<T>* node,
                                    int criterio,
                                    bool (*comparar)(T, T, int)) {

    if (node == 0 || node->next == 0) {
        return node;
    }

    DLink<T>* segundaMitad = split(node);

    DLink<T>* izquierda = mergeSortNodes(
        node,
        criterio,
        comparar
    );

    DLink<T>* derecha = mergeSortNodes(
        segundaMitad,
        criterio,
        comparar
    );

    return mergeNodes(
        izquierda,
        derecha,
        criterio,
        comparar
    );
}

// Complejidad de mergeSort:
// Mejor caso: O(n log n)
// Caso promedio: O(n log n)
// Peor caso: O(n log n)
// mergeSortNodes ordena la lista en O(n log n).
// Despues se recorre la lista una vez para actualizar tail,
// lo cual cuesta O(n).
// O(n log n) + O(n) = O(n log n)
// Por lo tanto, la complejidad final de mergeSort
// es O(n log n).
template <class T>
void DList<T>::mergeSort(int criterio,
                         bool (*comparar)(T, T, int)) {

    head = mergeSortNodes(head, criterio, comparar);

    tail = head;

    if (tail != 0) {
        while (tail->next != 0) {
            tail = tail->next;
        }
    }
}

#endif