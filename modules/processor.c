#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

void csv_processor(char *filename, City **cities, int *index)
{
    // esta funcion parsea el csv en un array de structs City y calcula el tamaño de este 

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
        if (column == NULL) {
            printf("Error: Nombre de ciudad faltante, registro ignorado\n");
            continue;
        }
        
        // guardar nombre de ciudad para mensajes de error
        char city_name_temp[50];
        strcpy(city_name_temp, column);
        
        // leer columna seismic_level y manejar caso null
        column = strtok(NULL, ",");
        if (column == NULL) {
            printf("Error, seismic_level faltante para la ciudad %s. registro ignorado.\n", city_name_temp);
            continue;
        }
        
        int seismic_level = atoi(column);
        if (seismic_level < 1 || seismic_level > 5) {
            printf("Error, seismic level invalido para la ciudad %s. Debe estar entre 1 y 5. Registro ignorado.\n", city_name_temp);
            continue;
        }
        
        // leer columna risk_percent y manejar caso null
        column = strtok(NULL, ",");
        int is_null = 0;
        float risk_percent = 0;
        
        if (column != NULL && strlen(column) > 0) {
            char *endptr;
            risk_percent = strtof(column, &endptr);
            
            if (risk_percent < 0 || risk_percent > 100) {
                printf("Error, risk_percent invalido para la ciudad %s. registro ignorado.\n", city_name_temp);
                continue;
            }
            
            is_null = 0;
        } else {
            is_null = 1;
        }
        
        // escribir datos en el struct
        strcpy((*cities)[*index].city_name, city_name_temp);
        (*cities)[*index].seismic_level = seismic_level;
        (*cities)[*index].risk_percent = risk_percent;
        (*cities)[*index].is_null = is_null;
        (*index)++;
    }

    fclose(file);

    return;
}

void csv_output(City *cities, int size, char *filename, int cities_to_priorize)
{
    // esta funcion escribe el archivo de salida considerando el tamaño que pidio el usuario

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
        fprintf(file, "%s,%d,",
                cities[i].city_name,
                cities[i].seismic_level);
        if (cities[i].is_null == 0)
        {
            fprintf(file, "%.2f\n",
                    cities[i].risk_percent);
        }
        else
        {
            fprintf(file, " \n");
        }
    }

    fclose(file);
    printf("CSV generado como %s con %d ciudades", filename, cities_to_priorize);
    return;
}
