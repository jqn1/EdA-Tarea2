#ifndef SORTER
#define SORTER

#include "processor.h"

float get_seismic_level(City *cities, int index);

float get_risk_percent(City *cities, int index);

int quickSortPartition(City *cities, int start, int end, float (*get_attribute)(City *cities, int index));
void quickSort(City *cities, int start, int end, float (*get_attribute)(City *cities, int index));

#endif  
