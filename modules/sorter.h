#ifndef SORTER
#define SORTER

#include "processor.h"

float get_seismic_level(City city);

float get_risk_percent(City city);

int quickSortPartition(City *cities, int start, int end, float (*get_attribute)(City city));
void quickSort(City *cities, int start, int end, float (*get_attribute)(City city));

#endif  
