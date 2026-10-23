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

En este avance, el programa carga los registros desde el archivo `mascotas.txt`, los almacena como objetos de tipo `Mascota` dentro de un `vector` y permite mostrarlos, ordenarlos por fecha o zona y realizar búsquedas por zona.

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

Al iniciar, el programa carga automáticamente la información de `mascotas.txt` y muestra el siguiente menú:

```text
===== PETFINDER =====
1. Mostrar mascotas
2. Ordenar por fecha
3. Ordenar por zona
4. Buscar por zona
5. Salir
Selecciona una opcion:
```

Las opciones permiten mostrar todos los registros, ordenarlos por fecha, ordenarlos alfabéticamente por zona, buscar mascotas registradas en una zona determinada o salir del programa.

---

## Estructura de datos

Para almacenar los registros se utiliza:

```cpp
vector<Mascota> mascotas;
```

En el primer avance se utilizaba un arreglo con una capacidad máxima de 100 mascotas. En este avance se cambió a `vector` porque la cantidad de registros puede aumentar conforme crezca PetFinder y no es conveniente establecer un límite fijo.

Las principales operaciones utilizadas son:

```text
Acceso por índice: O(1)
size(): O(1)
push_back(): O(1) amortizado
push_back() cuando requiere redimensionamiento: O(n)
Recorrido completo del vector: O(n)
```

El acceso por índice también es útil para la implementación de Merge Sort.

---

## Carga de información

Los registros se cargan desde el archivo:

```text
mascotas.txt
```

mediante la función:

```cpp
cargarMascotas(mascotas, "mascotas.txt");
```

Cada línea del archivo contiene los datos de una mascota separados por `|`.

Ejemplo:

```text
1|Luna|Perro|Husky|Gris|Mediano|Juriquilla|2026-09-20
```

La función recorre los registros del archivo y agrega cada mascota al `vector` utilizando `push_back()`.

Su complejidad es:

```text
O(n)
```

donde `n` representa la cantidad de mascotas almacenadas en el archivo.

---

## Algoritmo de ordenamiento

Como corrección del primer avance, se reemplazó Insertion Sort por **Merge Sort**.

Merge Sort divide los registros en mitades hasta obtener elementos individuales y posteriormente vuelve a unir las partes de forma ordenada.

La misma implementación se utiliza para ordenar con diferentes criterios, evitando tener dos algoritmos prácticamente iguales.

### Ordenamiento por fecha

Cuando el criterio seleccionado es fecha, se comparan los registros mediante:

```cpp
a.get_fecha() < b.get_fecha()
```

Las fechas utilizan el formato `AAAA-MM-DD`, por lo que pueden compararse correctamente como cadenas de texto.

### Ordenamiento por zona

Cuando el criterio seleccionado es zona, se utiliza:

```cpp
a.get_zona() < b.get_zona()
```

Esto permite ordenar las zonas alfabéticamente.

---

## Análisis de complejidad de Merge Sort

La relación de recurrencia de Merge Sort es:

```text
T(n) = 2T(n/2) + O(n)
```

El algoritmo divide el conjunto de datos en aproximadamente `log n` niveles.

En cada nivel se procesan en total `n` elementos al realizar la combinación de las mitades.

Por lo tanto:

```text
Mejor caso: O(n log n)
Caso promedio: O(n log n)
Peor caso: O(n log n)
```

La función `merge()` recorre los elementos de las dos mitades para volver a colocarlos en el orden correcto, por lo que tiene complejidad:

```text
O(n)
```

Además, utiliza vectores temporales para almacenar las dos mitades, por lo que la complejidad espacial adicional es:

```text
O(n)
```

---

## Búsqueda por zona

PetFinder permite consultar las mascotas registradas en una zona determinada.

La función recorre el `vector` completo porque pueden existir varias mascotas registradas en la misma zona.

Por ejemplo:

```text
Juriquilla
```

puede regresar uno o varios registros.

La función realiza `n` comparaciones con respecto a la zona buscada, por lo que:

```text
T(n) = n
```

y su complejidad es:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

En esta implementación se recorre todo el vector incluso después de encontrar una coincidencia, ya que pueden existir más mascotas en la misma zona.

---

## Justificación

Se seleccionó `vector<Mascota>` porque permite almacenar una cantidad dinámica de registros sin establecer un máximo fijo.

También se reemplazó Insertion Sort por Merge Sort para mejorar la eficiencia del sistema conforme aumente la cantidad de mascotas almacenadas.

Insertion Sort puede tener una complejidad de:

```text
O(n²)
```

mientras que Merge Sort mantiene:

```text
O(n log n)
```

en el mejor caso, caso promedio y peor caso.

La fecha y la zona se mantienen como criterios de ordenamiento porque son datos importantes para un sistema de búsqueda de mascotas perdidas.

La búsqueda por zona también permite consultar información relacionada con la ubicación en la que fue reportada una mascota.

---

## SICT0301 - Evalúa los componentes

Se realizó el análisis de complejidad de las principales operaciones utilizadas en el programa.

Para `vector`:

```text
Acceso por índice: O(1)
size(): O(1)
push_back(): O(1) amortizado
Recorrido completo: O(n)
```

Para Merge Sort:

```text
Mejor caso: O(n log n)
Caso promedio: O(n log n)
Peor caso: O(n log n)
```

Para la búsqueda por zona:

```text
Mejor caso: O(n)
Caso promedio: O(n)
Peor caso: O(n)
```

También se analizó la función `merge()`, cuya complejidad temporal es:

```text
O(n)
```

---

## SICT0302 - Toma decisiones

Se seleccionó `vector<Mascota>` porque el número de registros puede aumentar conforme crezca PetFinder.

A diferencia de un arreglo fijo, el `vector` permite agregar nuevos elementos dinámicamente y mantiene acceso por índice en `O(1)`.

También se seleccionó Merge Sort porque presenta una mejor escalabilidad que Insertion Sort.

Su complejidad de `O(n log n)` permite ordenar una mayor cantidad de registros de forma más eficiente que un algoritmo con complejidad `O(n²)`.

Además, se utiliza un solo algoritmo de ordenamiento con un criterio parametrizado para fecha o zona, evitando duplicar código.

---

## SICT0303 - Implementa acciones científicas

El programa permite cargar información directamente desde el archivo:

```text
mascotas.txt
```

Los registros son convertidos en objetos de tipo `Mascota` y almacenados dentro del `vector`.

También se pueden consultar los datos mediante la función de búsqueda por zona.

Esto permite que el usuario cargue y consulte información utilizando la estructura de datos implementada.

---

## Estado actual del proyecto

PetFinder actualmente permite:

- Cargar mascotas desde `mascotas.txt`.
- Almacenar objetos de tipo `Mascota` utilizando `vector`.
- Mostrar todos los registros.
- Ordenar por fecha utilizando Merge Sort.
- Ordenar por zona utilizando Merge Sort.
- Utilizar un solo algoritmo con diferentes criterios de ordenamiento.
- Buscar mascotas por zona.
- Utilizar un menú interactivo.
- Detectar opciones inválidas.
- Analizar la complejidad de las principales operaciones utilizadas.