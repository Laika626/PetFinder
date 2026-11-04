# PetFinder

## Descripción

PetFinder es un sistema desarrollado en C++ para almacenar, organizar y consultar registros de mascotas perdidas.

Cada mascota contiene:

- ID
- Nombre
- Especie
- Raza
- Color
- Tamaño
- Zona
- Fecha del reporte

En este avance, el programa carga los registros desde el archivo `mascotas.txt`, los almacena como objetos de tipo `Mascota` dentro de una lista doblemente ligada `DList<Mascota>` y permite mostrarlos, ordenarlos por fecha o zona, realizar búsquedas por zona, registrar nuevas mascotas y eliminar registros.

Los cambios realizados al registrar o eliminar una mascota se guardan automáticamente en `mascotas.txt`.

Como corrección del primer avance, se reemplazó Insertion Sort por Merge Sort para utilizar un algoritmo de ordenamiento más eficiente conforme aumente la cantidad de registros.

---

## Cómo usar el programa

Compilar desde la terminal:

```bash
g++ main.cpp -o petfinder
```

Ejecutar:

```bash
./petfinder
```

Al iniciar, el programa carga automáticamente la información almacenada en `mascotas.txt` y muestra el siguiente menú:

```text
===== PETFINDER =====
1. Mostrar mascotas
2. Ordenar por fecha
3. Ordenar por zona
4. Buscar por zona
5. Registrar mascota
6. Eliminar mascota
7. Salir
Selecciona una opcion:
```

Las opciones permiten mostrar los registros, ordenarlos, buscar mascotas en una zona, registrar nuevas mascotas, eliminar registros o salir del programa.

---

## Estructura de datos

Para almacenar las mascotas se utiliza una lista doblemente ligada:

```cpp
DList<Mascota> listaMascotas;
```

Cada nodo de la lista contiene un objeto y dos apuntadores:

```cpp
T value;
DLink<T>* next;
DLink<T>* prev;
```

La lista también mantiene:

```cpp
DLink<T>* head;
DLink<T>* tail;
int size;
```

Se seleccionó `DList` porque PetFinder necesita almacenar una cantidad dinámica de mascotas sin establecer un límite fijo de registros.

Además, la estructura permite recorrer los datos hacia adelante y hacia atrás mediante los apuntadores `next` y `prev`.

---

## Complejidad de la DList

### insertion()

La inserción se realiza directamente al final utilizando `tail`.

```text
Mejor caso: O(1)
Caso promedio: O(1)
Peor caso: O(1)
```

No es necesario recorrer la lista para insertar un nuevo nodo.

### search()

La búsqueda comienza desde `head` y avanza nodo por nodo.

```text
Mejor caso: O(1)
Caso promedio: O(n)
Peor caso: O(n)
```

El mejor caso ocurre cuando el elemento se encuentra al inicio. El peor caso ocurre cuando está al final o no existe.

### update()

Para actualizar un elemento se recorre la lista desde `head` hasta encontrar el índice indicado.

```text
Mejor caso: O(1)
Caso promedio: O(n)
Peor caso: O(n)
```

### deleteAt()

Primero se localiza el nodo correspondiente al índice solicitado.

```text
Mejor caso: O(1)
Caso promedio: O(n)
Peor caso: O(n)
```

Una vez localizado el nodo, la reconexión de los apuntadores `next` y `prev` se realiza en `O(1)`.

### clear()

La función elimina todos los nodos de la lista.

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

### toStringForward() y toStringBackward()

Ambas funciones recorren todos los nodos de la lista.

```text
O(n)
```

### getSize(), getHead() y getTail()

Estas funciones regresan directamente un valor o apuntador almacenado.

```text
O(1)
```

---

## Carga de información

Los registros se cargan desde:

```text
mascotas.txt
```

Cada línea contiene una mascota y sus datos están separados por `|`.

Ejemplo:

```text
1|Luna|Perro|Husky|Gris|Mediano|Juriquilla|2026-09-20
```

La función `cargarMascotas()` crea un objeto `Mascota` por cada registro y lo inserta en la lista mediante:

```cpp
listaMascotas.insertion(nuevaMascota);
```

Como se recorren los `n` registros del archivo y cada inserción es `O(1)`:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

---

## Algoritmo de ordenamiento

Para ordenar las mascotas se utiliza Merge Sort adaptado a la lista doblemente ligada.

La misma implementación se utiliza para dos criterios:

```text
1 -> Fecha
2 -> Zona
```

Esto evita tener dos algoritmos de ordenamiento duplicados.

### Ordenamiento por fecha

Se comparan las fechas de las mascotas.

Las fechas utilizan el formato:

```text
AAAA-MM-DD
```

por lo que pueden compararse correctamente como cadenas de texto.

### Ordenamiento por zona

Se comparan las zonas para ordenarlas alfabéticamente.

---

## Complejidad de Merge Sort

Merge Sort divide recursivamente la lista en dos mitades y posteriormente vuelve a unirlas de forma ordenada.

La relación de recurrencia es:

```text
T(n) = 2T(n/2) + O(n)
```

Por lo tanto:

```text
Mejor caso: O(n log n)
Caso promedio: O(n log n)
Peor caso: O(n log n)
```

La función `split()` recorre parte de la lista para localizar su punto medio:

```text
O(n)
```

La función `mergeNodes()` combina las mitades ordenadas:

```text
O(n)
```

La función completa `mergeSort()` mantiene:

```text
O(n log n)
```

---

## Justificación del algoritmo

En el primer avance se utilizó Insertion Sort, cuya complejidad en el peor caso puede llegar a:

```text
O(n²)
```

Se decidió reemplazarlo por Merge Sort porque PetFinder puede aumentar su cantidad de registros.

Merge Sort mantiene:

```text
O(n log n)
```

en el mejor caso, caso promedio y peor caso.

Esto permite que el algoritmo tenga un mejor comportamiento conforme aumenta la cantidad de mascotas almacenadas.

---

## Mostrar mascotas

La función `mostrarMascotas()` recorre todos los nodos de la DList desde `head` hasta el final.

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

---

## Búsqueda por zona

PetFinder permite consultar todas las mascotas registradas en una zona determinada.

La función recorre la lista completa porque pueden existir varias mascotas registradas en la misma zona.

Por ejemplo:

```text
Juriquilla
```

puede regresar varios registros.

Por lo tanto:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

---

## Registrar mascota

El usuario puede registrar una nueva mascota directamente desde el programa.

Después de solicitar sus datos, se crea un objeto `Mascota` y se inserta mediante:

```cpp
listaMascotas.insertion(nuevaMascota);
```

La inserción tiene complejidad:

```text
O(1)
```

Después se llama a `guardarMascotas()` para actualizar automáticamente `mascotas.txt`.

Como guardar todos los registros cuesta `O(n)`:

```text
O(1) + O(n) = O(n)
```

Por lo tanto:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

---

## Eliminar mascota

Para eliminar una mascota se solicita su ID.

Primero se recorre la lista para encontrar el registro:

```text
O(n)
```

Después se utiliza:

```cpp
listaMascotas.deleteAt(posicionEncontrada);
```

que puede requerir otro recorrido:

```text
O(n)
```

Finalmente se actualiza `mascotas.txt`:

```text
O(n)
```

Entonces:

```text
O(n) + O(n) + O(n) = O(n)
```

Por lo tanto:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

---

## Escritura de archivos

La función `guardarMascotas()` recorre todos los nodos de la DList y escribe cada mascota en `mascotas.txt`.

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

El archivo se actualiza automáticamente cuando se registra o elimina una mascota.

---

## Complejidad final del programa

Las principales operaciones tienen las siguientes complejidades:

```text
Cargar mascotas: O(n)
Mostrar mascotas: O(n)
Buscar por zona: O(n)
Registrar mascota: O(n)
Eliminar mascota: O(n)
Guardar mascotas: O(n)
Ordenar con Merge Sort: O(n log n)
```

Para un flujo donde se cargan, ordenan y muestran los registros:

```text
O(n) + O(n log n) + O(n)
```

El término dominante es:

```text
O(n log n)
```

Por lo tanto, la complejidad final de ese flujo es:

```text
O(n log n)
```

---

## SICT0301 - Evalúa los componentes

Se realizó el análisis de complejidad de la estructura `DList` y de sus principales operaciones.

También se analizaron las funciones:

- `cargarMascotas()`
- `mostrarMascotas()`
- `buscarPorZona()`
- `guardarMascotas()`
- `registrarMascota()`
- `eliminarMascota()`
- Merge Sort

La operación con mayor crecimiento en los flujos que utilizan ordenamiento es:

```text
O(n log n)
```

---

## SICT0302 - Toma decisiones

Se seleccionó `DList<Mascota>` porque PetFinder necesita una estructura dinámica que permita aumentar la cantidad de registros durante la ejecución.

La lista doblemente ligada permite insertar nuevas mascotas sin establecer un tamaño máximo y facilita el recorrido de los registros mediante apuntadores.

También se seleccionó Merge Sort debido a su complejidad de:

```text
O(n log n)
```

que presenta una mejor escalabilidad que Insertion Sort con `O(n²)`.

---

## SICT0303 - Implementa acciones científicas

PetFinder carga los registros existentes desde:

```text
mascotas.txt
```

directamente hacia la estructura `DList<Mascota>`.

El programa permite consultar la información mediante:

- Mostrar mascotas.
- Buscar mascotas por zona.

También permite modificar la estructura mediante:

- Registrar mascotas.
- Eliminar mascotas.

Cuando se realizan cambios, el archivo `mascotas.txt` se actualiza automáticamente, permitiendo conservar la información después de cerrar el programa.

---

## Estado actual del proyecto

PetFinder actualmente permite:

- Cargar mascotas desde `mascotas.txt`.
- Almacenar registros utilizando `DList<Mascota>`.
- Trabajar con una cantidad dinámica de datos.
- Mostrar todas las mascotas.
- Ordenar por fecha utilizando Merge Sort.
- Ordenar por zona utilizando Merge Sort.
- Utilizar un solo algoritmo con diferentes criterios de comparación.
- Buscar mascotas por zona.
- Registrar nuevas mascotas.
- Guardar automáticamente los registros.
- Eliminar mascotas.
- Actualizar automáticamente el archivo después de eliminar.
- Trabajar con aproximadamente 30 registros de prueba.
- Analizar la complejidad de la estructura, algoritmos y funciones principales.