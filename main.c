#include <stdlib.h>
#include <stdio.h>
#include "modules/processor.h"
#include "modules/sorter.h"


int main(int argc, char *argv []) {
    

    City *cities = NULL;
    int cities_size = 0;
    csv_processor(argv[1], &cities, &cities_size);


    

     
    for(int i = 0; i<cities_size; i++) {
        printf("City: %s, Siesmic_Level: %d, Risk_Percent: %.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    }

    //primer sort
    quickSort(cities, 0, cities_size - 1, get_seismic_level);
    printf("\n Primer Sort: \n");
    for(int i = 0; i<cities_size; i++) {
        printf("City: %s, Siesmic_Level: %d, Risk_Percent: %.2f\n", cities[i].city_name, cities[i].seismic_level, cities[i].risk_percent);
    }




    // liberar memoria al final del programa
    free(cities);
    return 0;

}
