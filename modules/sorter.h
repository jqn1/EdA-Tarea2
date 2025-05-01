#ifndef SORTER
#define SORTER

#include "processor.h"
void to_lowercase(char *str);

int quickSortPartition(City *cities, int low, int high, int (*compare)(const void *, const void *));
void quickSort(City *cities, int low, int high, int (*compare)(const void *, const void *));
int compare_cities(const void *a, const void *b);

#endif  
