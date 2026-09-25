# PetFinder

## Descripción

PetFinder es un sistema desarrollado en C++ para almacenar y organizar registros de mascotas perdidas.

Cada mascota contiene:

- ID
- Nombre
- Especie
- Raza
- Color
- Tamaño
- Zona
- Fecha del reporte

En este primer avance, el programa carga los registros desde el archivo `mascotas.txt`, los almacena como objetos de tipo `Mascota` y permite ordenarlos por fecha o por zona utilizando el algoritmo Insertion Sort.

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
4. Salir
Selecciona una opcion:
```

Las opciones permiten mostrar los registros, ordenarlos por fecha, ordenarlos alfabéticamente por zona o salir del programa.

---

## Algoritmo de ordenamiento

Para este avance se implementó manualmente **Insertion Sort**.

El algoritmo toma cada elemento del arreglo y lo compara con los elementos anteriores hasta encontrar la posición en la que debe colocarse.

En PetFinder se utiliza para dos criterios:

### Ordenamiento por fecha

```cpp
mascotas[j].get_fecha() > actual.get_fecha()
```

Las fechas utilizan el formato `AAAA-MM-DD`, por lo que pueden compararse correctamente como cadenas de texto.

### Ordenamiento por zona

```cpp
mascotas[j].get_zona() > actual.get_zona()
```

Esto permite ordenar las zonas alfabéticamente.

---

## Análisis de complejidad

### Peor caso: O(n²)

El peor caso de Insertion Sort ocurre cuando los elementos se encuentran en el orden contrario al que se desea obtener.

En este caso, cada elemento debe compararse con todos los elementos anteriores.

La cantidad de comparaciones puede representarse como:

```text
1 + 2 + 3 + ... + (n - 1)
```

que equivale a:

```text
n(n - 1) / 2
```

Por lo tanto, la complejidad temporal en el peor caso es:

```text
O(n²)
```

Este análisis aplica tanto al ordenamiento por fecha como al ordenamiento por zona.

---

## Justificación

Se eligió Insertion Sort porque el proyecto actualmente trabaja con una cantidad pequeña de registros y es un algoritmo sencillo de implementar y comprender.

Además, permite utilizar la misma lógica para ordenar diferentes atributos de las mascotas, cambiando únicamente el criterio de comparación.

La fecha y la zona fueron seleccionadas porque son datos relevantes para un sistema de búsqueda de mascotas perdidas.

---

## SICT0301 - Evalúa los componentes

Se realizó el análisis de complejidad del algoritmo Insertion Sort utilizado en el programa.

Su complejidad temporal en el peor caso es:

```text
O(n²)
```

---

## SICT0302 - Toma decisiones

Se seleccionó Insertion Sort para organizar los registros por fecha y zona.

El algoritmo es adecuado para este primer avance debido a la cantidad pequeña de datos utilizada actualmente y permite cumplir con las necesidades de ordenamiento del sistema.

---

## Estado actual del proyecto

PetFinder actualmente permite:

- Cargar mascotas desde `mascotas.txt`.
- Almacenar objetos de tipo `Mascota`.
- Mostrar los registros.
- Ordenar por fecha.
- Ordenar por zona.
- Utilizar un menú interactivo.
- Detectar opciones inválidas.