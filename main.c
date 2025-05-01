#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "modules/processor.h"
#include "modules/sorter.h"

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Uso: %s <input> <N> <output>\n", argv[0]);
        return 1;
    }

    char *input_name = argv[1];
    int cities_to_priorize = atoi(argv[2]);
    char *output_name = argv[3];

    City *cities = NULL;
    int cities_size = 0;
    csv_processor(input_name, &cities, &cities_size);
    printf("Cities size: %d", cities_size);

    // Lista original
    printf("Lista original:\n");
    // for(int i = 0; i < cities_size; i++) {
    //     printf("City: %s, Siesmic_Level: %d, Risk_Percent: %.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    // }

    //ordenar
    quickSort(cities, 0, cities_size - 1, compare_cities);
    seismic_level_3_null(cities, cities_size, compare_cities); // insertar valores de sismic level 3 nulos al medio de su grupo

    // escribir archivo de salida
    csv_output(cities, cities_size, output_name, cities_to_priorize);
    // liberar memoria al final del programa
    free(cities);
    return 0;
}
