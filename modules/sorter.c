#include <strings.h> // for strcasecmp
#include <string.h>
#include <ctype.h>
#include "processor.h"
#include "sorter.h"


float get_seismic_level(City city) {
    return city.seismic_level;
}

float get_risk_percent(City city) {
    return city.risk_percent;
}


int quickSortPartition(City *cities, int start, int end, float (*get_attribute)(City city)) {
    City *pivot = &cities[end];
    float pivot_value = get_attribute(*pivot);
    int i = start - 1;

    for (int j = start; j < end; j++) {
        float j_value = get_attribute(cities[j]);

        if (j_value >= pivot_value) {
            i++;
            //swap i and j
            City temp = cities[i];
            cities[i] = cities[j];
            cities[j] = temp;
        }
    }
    // insert pivot in between
    City temp = cities[i + 1];
    cities[i + 1] = *pivot;
    *pivot = temp;


    return (i + 1);
}

void quickSort(City *cities, int start, int end, float (*get_attribute)(City city)) {
    if (start < end) {
        int index = quickSortPartition(cities, start, end, get_attribute);

        quickSort(cities, start, index - 1, get_attribute);
        quickSort(cities, index + 1, end, get_attribute);
    }
}


int compare_reverse_cities(const void *a, const void *b) {
    const City *city_a = (const City *)a;
    const City *city_b = (const City *)b;
    
    const char *name_a = city_a->city_name;
    const char *name_b = city_b->city_name;
    
    while (*name_a && *name_b) {
        int diff = tolower(*name_a) - tolower(*name_b);
        if (diff != 0) return -diff; // Invierte el orden
        name_a++;
        name_b++;
    }
    return -(*name_a - *name_b);
}
