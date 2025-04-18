#include <stdlib.h>
#include "modules/processor.h"



int main(int argc, char *argv []) {
    

    City *cities = NULL;
    int index = 0;
    csv_processor(argv[1], &cities, &index);


    






    free(cities);


    return 0;

}
