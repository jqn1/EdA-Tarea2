#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "modules/processor.h"
#include "modules/sorter.h"

int main(int argc, char *argv[])
{

    if (argc != 4) // error en caso de cantidad de argumentos invalida
    {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    // asignar variables a los argumentos
    char *input_name = argv[1];
    char *output_name = argv[3];
    int cities_to_priorize = atoi(argv[2]);

    // inicializar el array de struct tipo City y la variable para saber la cantidad de ciudades
    City *cities = NULL;
    int cities_size = 0;
    // parsear csv
    csv_processor(input_name, &cities, &cities_size);

    if (cities_size < cities_to_priorize) {
        printf("Error, el usuario quiere imprimir mas ciudades de las que hay validadas, se imprimira solo la cantidad de ciudades validas\n");
        cities_to_priorize = cities_size;
    }

    //ordenar datos
    quickSort(cities, 0, cities_size - 1, compare_cities);
    seismic_level_3_null(cities, cities_size, compare_cities); // insertar valores de sismic level 3 nulos al medio de su grupo

    // escribir archivo de salida
    csv_output(cities, cities_size, output_name, cities_to_priorize);

    // liberar memoria al final del programa
    free(cities);
    return 0;
}
