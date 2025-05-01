#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "processor.h"

void to_lowercase(char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

// Función de comparación para quickSort
// Orden inverso (Z-A)
int compare_cities(const void *a, const void *b) {
    const City *city_a = (const City *)a;
    const City *city_b = (const City *)b;

    // 1. Comparar por nivel sísmico (mayor nivel = mayor prioridad)
    if (city_a->seismic_level != city_b->seismic_level) {
        return city_b->seismic_level - city_a->seismic_level;
    }

    // 2. Manejar valores vacíos en risk_percent según seismic_level
    if (city_a->is_null || city_b->is_null) {
        if (city_a->seismic_level == 5 || city_a->seismic_level == 4) {
            if (city_a->is_null && !city_b->is_null) {
                return -1; // city_a tiene prioridad
            }
            if (city_b->is_null && !city_a->is_null) {
                return 1; // city_b tiene prioridad
            }
        // } else if (city_a->seismic_level == 3) {
        //     // Para seismic_level 3, colocar valores nulos en el medio
        //     if (city_a->is_null && !city_b->is_null) {
        //         return 1; // city_a al medio, menor prioridad
        //     }
        //     if (city_b->is_null && !city_a->is_null) {
        //         return -1; // city_b al medio, menor prioridad
        //     }
        } else if (city_a->seismic_level == 2 || city_a->seismic_level == 1) {
            if (city_a->is_null && !city_b->is_null) {
                return 1; // city_a al final, menor prioridad
            }
            if (city_b->is_null && !city_a->is_null) {
                return -1; // city_b al final, menor prioridad
            }
        }
    }

    // 3. Comparar por porcentaje de riesgo (mayor porcentaje = mayor prioridad)
    if (city_a->risk_percent != city_b->risk_percent) {
        return (city_b->risk_percent > city_a->risk_percent) ? 1 : -1;
    }

    // 4. Desempatar por orden alfabético inverso (Z-A)
    char name_a[64], name_b[64];
    strncpy(name_a, city_a->city_name, sizeof(name_a));
    strncpy(name_b, city_b->city_name, sizeof(name_b));
    name_a[sizeof(name_a) - 1] = '\0';
    name_b[sizeof(name_b) - 1] = '\0';

    to_lowercase(name_a);
    to_lowercase(name_b);

    return strcmp(name_b, name_a); // Orden inverso (Z-A)
}

int quickSortPartition(City *cities, int low, int high, int (*compare)(const void *, const void *)) {
    City pivot = cities[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(&cities[j], &pivot) < 0) {
            i++;
            City temp = cities[i];
            cities[i] = cities[j];
            cities[j] = temp;
        }
    }

    City temp = cities[i + 1];
    cities[i + 1] = cities[high];
    cities[high] = temp;

    return i + 1;
}

// Implementación de quickSort
void quickSort(City *cities, int low, int high, int (*compare)(const void *, const void *)) {
    if (low < high) {
        int pivot_index = quickSortPartition(cities, low, high, compare);
        quickSort(cities, low, pivot_index - 1, compare);
        quickSort(cities, pivot_index + 1, high, compare);
    }
}


void seismic_level_3_null(City *cities, int size, int (*compare)(const void *, const void *)) {
    int start = -1;
    int end = -1;
    int not_null_count = 0;
    int null_count = 0;
    float median;
    for (int i = 0; i < size; i++) {
        if (cities[i].seismic_level == 3 && cities[i].is_null == 0) {
            not_null_count++;
            if(start == -1) {
                start = i;
            }
            end = i;
        }
    }
    //calcular mediana
    if (not_null_count % 2 == 0) {
        int median_index1 = ((start) + (end)) / 2; 
        int median_index2 = median_index1 + 1;
        median = (cities[median_index1].risk_percent + cities[median_index2].risk_percent) / 2;
    } else {
        int median_index = ((start) + (end)) / 2; 
        median = cities[median_index].risk_percent;
    }
    //imputar mediana a datos nulos;
    for (int i = 0; i < size; i++) {
        if (cities[i].seismic_level == 3 && cities[i].is_null == 1) {
            //printf("mediana: %f",median);
            null_count++;
            cities[i].risk_percent = median;
        }
    }
    // printf("nullcount %d\n",null_count);
    // printf("start %d\n",start);
    // printf("end %d\n",end);
    //ordenar la parte del array con sismic level 3
    quickSort(cities, start, end + null_count, compare);

    //devolver los valores nulos a 0
    for (int i = 0; i < size; i++) {
        if (cities[i].seismic_level == 3 && cities[i].is_null == 1) {
            cities[i].risk_percent = 0;
        }
    }
}