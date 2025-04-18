# TICS311: Tarea # 2

Universidad Adolfo Ibáñez
Asignatura: Estructura de datos y algoritmos
Fecha de entrega: 25 de abril de 2025

## Objetivos

```
. Manejo avanzado de estructuras de datos en C.
. Implementación de algoritmos de ordenamiento.
. Procesamiento de archivos CSV.
```
## 1. Earthquake Alert System

### 1.1 Contexto

Su equipo ha sido contratado para desarrollar un sistema de priorización de ciudades en riesgo sísmico.
Han recibido un archivo CSV con datos de monitoreo en el siguiente formato:

```
city_name seismic_level risk_percent
Santiago 5 89.
Valparaíso 3
Concepción 4 75.
```
Puede esperar un archivo CSV con número de filas mayor a 1,000 y con datos faltantes (como en el caso de
Valparaíso en el ejemplo anterior, en el que falta risk_percent ). En caso de tener datos faltantes, debe
tomarse en cuenta el punto 3 del criterio de priorización descrito a continuación.

### 1.2 Criterios de Priorización

```
. Nivel Sísmico (1-5): Mayor valor = mayor prioridad.
. Porcentaje de Riesgo: Mayor valor = mayor prioridad.
. Valores faltantes:
Niveles 1-2: Baja prioridad (final de su categoría).
Nivel 3: Prioridad media (mitad de su categoría).
Niveles 4-5: Alta prioridad (inicio de su categoría).
. Desempate: Orden alfabético inverso (Z-A).
```
## 2. Especificaciones Técnicas

### 2.1 Entrada del Programa


```
./tarea2 input.csv 15 output.txt
```
```
input.csv: Archivo con datos sísmicos (>= 1000 registros).
15 : Cantidad de ciudades a priorizar (N_Cities).
output.txt: Archivo de salida con N_Cities nombres de ciudades ordenadas por orden de
prioridad. Debe incluir la infomación de seismic_level y risk_percent.
```
### 2.2 Requisitos de Implementación

```
. Usar una estructura de datos eficiente para manejar >1,000 registros.
. Implementar quicksort como algoritmo de ordenamiento.
. Validar la integridad de los datos:
Campos numéricos fuera de rango.
Registros corruptos.
Campos vacíos.
. Manejo de memoria dinámica:
Es obligatorio usar malloc o similar y free para gestionar estructuras dinámicas como
arreglos o listas enlazadas.
Liberar toda la memoria al final del programa para evitar fugas de memoria.
```
## 3. Ejemplo de Ejecución

Archivo de entrada (ejemplo):

```
city_name seismic_level risk_percent
Calama 1 39.
San Antonio 5
Melipilla 1 66.
Punta Arenas 1 33.
Talca 3 49.
Coyhaique 1
Angol 3 73.
Linares 1 84.
Rancagua 3
San Fernando 3 97.
Punta Arenas 2 79.
Puerto Montt 4 30.
Concepción 5 90.
```

```
city_name seismic_level risk_percent
Viña del Mar 1
```
Salida esperada (para N_Cities=9):

```
city_name seismic_level risk_percent
San Antonio 5
Concepción 5 90.
Puerto Montt 4 30.
San Fernando 3 97.
Angol 3 73.
Rancagua 3
Talca 3 49.
Punta Arenas 2 79.
Linares 1 84.
```
## 4. Entrega

```
. Formato: El proyecto debe ser entregado con la siguiente estructura:
```
```
grupoX-T2/
├── Makefile
├── main.c
└── modules/
├── processor.h // Implementación de funciones
├── processor.c // para procesar datos
├── sorter.h // Implementación de funciones
├── sorter.c // para ordenar datos
├── validator.h // Implementación de funciones
└── validator.c //para validar datos
```
```
. Requisitos:
Se debe subir una entrega por grupo.
Compilación con GCC.
Manejo de errores detallado.
Comentarios en principales funciones.
Breve reporte de la solución desarrollada.
```
Penalizaciones:

```
-1 punto/día de retraso.
-2 puntos por warnings de compilación.
```

### Estructura Inicial de Código

```
#include <stdio.h>
#include <stdlib.h>
typedef struct {
char city_name[ 50 ];
int seismic_level;
float risk_percent;
} CityData;
int main(int argc, char *argv[]) {
if (argc != 4 ) {
printf("Uso: %s <input> <N> <output>\n", argv[ 0 ]);
return 1 ;
}
// Implementación pendiente
return 0 ;
}
```
### Nota:

```
Optimización para grandes volúmenes de datos:
Procesa el archivo CSV línea por línea en lugar de cargarlo completamente en memoria.
Algoritmos de ordenamiento:
Implementa el algoritmo QuickSort para ordenar los datos.
Considera el criterio de desempate (orden alfabético inverso) al implementar el ordenamiento.
Validación de datos:
Verifica que los valores numéricos estén dentro del rango esperado.
Maneja registros corruptos o campos vacíos según las reglas de priorización.
```


