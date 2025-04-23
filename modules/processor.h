#ifndef PROCESSOR 
#define PROCESSOR   

typedef struct {
    char city_name[15];
    int seismic_level;
    float risk_percent;
    int is_null;
}City;

void csv_processor(char *filename, City **cities, int *index);
void csv_output(City *cities, int size, char *filename, int cities_to_priorize);

#endif //
