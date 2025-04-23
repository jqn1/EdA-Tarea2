#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

void csv_processor(char *filename, City **cities, int *index)
{
    // esta funcion parsea el csv en un array de structs tipo City, y devuelve el tamaño de este

    char *column;      // puntero para leer columnas
    char buffer[1024]; // almacenar linea

    // leer archivo
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error, archivo nulo\n");
        return;
    }

    // Contar cantidad de filas para asignar memoria dinamicamente al array cities
    int count = 0;
    fgets(buffer, sizeof(buffer), file); // Leer y saltar la cabecera
    while (fgets(buffer, sizeof(buffer), file))
    {
        count++;
    }
    // printf("count %d\n", count);

    // Asignar memoria para cities
    *cities = malloc(count * sizeof(City));
    if (*cities == NULL)
    {
        printf("Error al asignar memoria\n");
        fclose(file);
        return;
    }

    // Volver al inicio del archivo para leer los datos
    fseek(file, 0, SEEK_SET);

    // Leer la primera linea (nombres de columnas) para no almacenarlas en el struct
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file))
    {

        // Eliminar el salto de línea del final de la línea leída
        buffer[strcspn(buffer, "\n")] = '\0';

        // leer columna city_name
        column = strtok(buffer, ",");
        // printf("index %d\n",*index);
        strcpy((*cities)[*index].city_name, column);
        // printf("%s\n", (*cities)[*index].city_name);

        // leer columna seismic_level y manejar caso null
        column = strtok(NULL, ",");
        if (column != NULL)
        {
            // printf("columna seismic level %d\n",atoi(column));
            (*cities)[*index].seismic_level = atoi(column);
        }

        // leer columna risk_percent y manejar caso null
        column = strtok(NULL, ",");
        if (column != NULL)
        {
            // printf("columna risk%f\n",atof(column));
            (*cities)[*index].risk_percent = atof(column);
            (*cities)[*index].is_null = 0;
        }else {

            (*cities)[*index].risk_percent = 0;
            (*cities)[*index].is_null = 1;

        }
        (*index)++;
    }

    fclose(file);

    return;
}

void csv_output(City *cities, int size, char *filename, int cities_to_priorize)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("no se pudo escribir el archivo de salida");
        return;
    }

    // encabezado
    fprintf(file, "city_name,seismic_level,risk_percent\n");

    // escribir datos del array de struct
    for (int i = 0; i < cities_to_priorize; i++)
    {
        fprintf(file, "%s,%d,%.2f\n",
                cities[i].city_name,
                cities[i].seismic_level,
                cities[i].risk_percent);
    }

    fclose(file);
    printf("CSV generado como %s con %d ciudades", filename, cities_to_priorize);
    return;
}
