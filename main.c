#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "modules/processor.h"
#include "modules/sorter.h"

int compare_reverse_cities(const void *a, const void *b)
{
    const City *city_a = (const City *)a;
    const City *city_b = (const City *)b;

    // Crear copias locales para comparar
    char copy_a[16];
    char copy_b[16];

    strncpy(copy_a, city_a->city_name, sizeof(copy_a));
    strncpy(copy_b, city_b->city_name, sizeof(copy_b));
    copy_a[sizeof(copy_a) - 1] = '\0';
    copy_b[sizeof(copy_b) - 1] = '\0';

    to_lowercase(copy_a);
    to_lowercase(copy_b);

    return strcmp(copy_b, copy_a);
}

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

    quickSort(cities, 0, cities_size - 1, compare_cities);
    // escribir archivo de salida
    csv_output(cities, cities_size, output_name, cities_to_priorize);
    // liberar memoria al final del programa
    free(cities);
    return 0;
}
