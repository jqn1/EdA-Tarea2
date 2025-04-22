#include <stdlib.h>
#include <stdio.h>
#include "modules/processor.h"



int main(int argc, char *argv []) {
    

    City *cities = NULL;
    int cities_size = 0;
    csv_processor(argv[1], &cities, &cities_size);


    

    






    // liberar memoria al final del programa
    free(cities);
    return 0;

}
