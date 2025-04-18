#ifndef CSV_CONVERT  
#define CSV_CONVERT   

typedef struct {
    char city_name[15];
    int seismic_level;
    float risk_percent;
}City;

void csv_processor(char *filename, City **cities, int *index);

#endif //
