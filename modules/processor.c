#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"



void csv_processor(char *filename, City **cities, int *index) {
    // esta funcion parsea el csv en un array de structs tipo City, y devuelve el tamaño de este

    char *column; //puntero para leer columnas
    char buffer[1024]; // almacenar linea

    // leer archivo
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
      printf("Error, archivo nulo");
      return ;
    }
    
    // Contar cantidad de filas para asignar memoria dinamicamente al array cities
    int count = 0;
    fgets(buffer, sizeof(buffer), file);  // Leer y saltar la cabecera
    while (fgets(buffer, sizeof(buffer), file)) {
        count++;
    }
    // printf("count %d\n", count);

    // Asignar memoria para cities 
    *cities = malloc(count * sizeof(City));
    if (*cities == NULL) {
        printf("Error al asignar memoria\n");
        fclose(file);
        return ;
    }

    // Volver al inicio del archivo para leer los datos
    fseek(file, 0, SEEK_SET);  

    // Leer la primera linea (nombres de columnas) para no almacenarlas en el struct
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {

        // Eliminar el salto de línea del final de la línea leída
        buffer[strcspn(buffer, "\n")] = '\0';


        // leer columna city_name
        column = strtok(buffer, ",");
        // printf("index %d\n",*index);
        strcpy((*cities)[*index].city_name, column); 
        // printf("%s\n", (*cities)[*index].city_name);

        //leer columna seismic_level y manejar caso null
        column = strtok(NULL, ",");
        if (column != NULL){
            // printf("columna seismic level %d\n",atoi(column));
            (*cities)[*index].seismic_level = atoi(column);
        }

        // leer columna risk_percent y manejar caso null
        column = strtok(NULL, ",");
        if (column != NULL){
            // printf("columna risk%f\n",atof(column));
            (*cities)[*index].risk_percent = atof(column);
        }
        (*index)++; 

    }

    fclose(file);


   return ;

    
}
