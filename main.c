#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "modules/processor.h"
#include "modules/sorter.h"

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

int compare_reverse_cities(const void *a, const void *b) {
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

    // Se agregan valores risk_percent a datos nulos para facilitar ordenamiento.
    // seismic_level 5 y 4 => risk_percent = 101                        Quedan al top
    // seismic_level 3 => risk_percent = average de seismic_level 3     Quedan al medio
    // seismic_level 1 y 2 => risk_percent = -1                         Quedan al final
    float average;
    float acc = 0;
    int l3_count = 0;
    for (int i=0; i<cities_size; i++){
        if (cities[i].is_null == 0 && cities[i].seismic_level == 3){
            acc+=cities[i].risk_percent;
            l3_count+=1;
        }
    }
    average = acc/l3_count;
    for (int i=0; i<cities_size; i++){
        if (cities[i].is_null == 1){

            if (cities[i].seismic_level == 4 || cities[i].seismic_level == 5){
                cities[i].risk_percent = 101;
            } else if (cities[i].seismic_level == 3)
            {
                cities[i].risk_percent = average;
            } else {
                cities[i].risk_percent = -1;
            }
        }
        
    }

    // primer sort
    quickSort(cities, 0, cities_size - 1, get_seismic_level);
    printf("\n Primer Sort: \n");
    // for(int i = 0; i < cities_size; i++) {
    //     printf("City: %s, Siesmic_Level: %d, Risk_Percent: %.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    // }

    // segundo sort según risk_percent;
    int l1_seismic_count = 0;
    int l2_seismic_count = 0;
    int l3_seismic_count = 0;
    int l4_seismic_count = 0;
    int l5_seismic_count = 0;
    for (int i = 0; i < cities_size; i++)
    {
        if (cities[i].seismic_level == 1)
            l1_seismic_count++;
        else if (cities[i].seismic_level == 2)
            l2_seismic_count++;
        else if (cities[i].seismic_level == 3)
            l3_seismic_count++;
        else if (cities[i].seismic_level == 4)
            l4_seismic_count++;
        else if (cities[i].seismic_level == 5)
            l5_seismic_count++;
    }
    printf("l1_count: %d, l2_count: %d, l3_count: %d, l4_count: %d, l5_count: %d \n", l1_seismic_count, l2_seismic_count, l3_seismic_count, l4_seismic_count, l5_seismic_count);
    printf("total: %d", l1_seismic_count + l2_seismic_count + l3_seismic_count + l4_seismic_count + l5_seismic_count);
    // se hace un quicksort por cada nivel sismico
    quickSort(cities, 0, l5_seismic_count - 1, get_risk_percent);
    quickSort(cities, l5_seismic_count, l5_seismic_count + l4_seismic_count - 1, get_risk_percent);
    quickSort(cities, l5_seismic_count + l4_seismic_count, l5_seismic_count + l4_seismic_count + l3_seismic_count - 1, get_risk_percent);
    quickSort(cities, l5_seismic_count + l4_seismic_count + l3_seismic_count, l5_seismic_count + l4_seismic_count + l3_seismic_count + l2_seismic_count - 1, get_risk_percent);
    quickSort(cities, l5_seismic_count + l4_seismic_count + l3_seismic_count + l2_seismic_count, l5_seismic_count + l4_seismic_count + l3_seismic_count + l2_seismic_count + l1_seismic_count - 1, get_risk_percent);
    printf("\n Segundo Sort: \n");
    // for (int i = 0; i < cities_size; i++)
    // {
    //     printf("City: %s, Siesmic_Level: %d, Risk_Percent: %.2f, is_null: %d\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent, cities[i].is_null);
    // }

    // Tercer sory por nombre de ciudades orden Z-A
    // Problemas con esto: 
    // Para ciudades con siesmic_level 5
    // - Si cities_to_priorize es suficientemente grande para que abarque ciudades 
    // con risk_percent alto, entonces es posible que dicha ciudad quede arriba del listado
    // que una ciudad sin risk_percent
    // Hay más errores en los demás niveles. 
    qsort(cities, cities_to_priorize, sizeof(City), compare_reverse_cities);


    // escribir archivo de salida
    csv_output(cities, cities_size, output_name, cities_to_priorize);
    // liberar memoria al final del programa
    free(cities);
    return 0;
}
