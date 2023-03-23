#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct minMax
{
    int min;
    int max;
} minMax;

void initArray(int *array)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        array[i] = i * i;
        printf("%d\n", array[i]);
    }
}

minMax *getMinMax(int *array, const int SIZE)
{
    minMax *obj = (minMax *)malloc(sizeof(minMax));
    obj->min, obj->max = array[0];
    for (int i = 1; i < SIZE; i++)
    {
        if (array[i] < obj->min)
        {
            obj->min = array[i];
            continue;
        }
        if (array[i] > obj->max)
            obj->max = array[i];
    }
    return obj;
}

int main()
{
    int *arrayPtr = (int *)malloc(sizeof(int) * MAX_SIZE);
    initArray(arrayPtr);
    minMax *minMax_ = getMinMax(arrayPtr, MAX_SIZE);
    printf("Max: %d\nMin: %d\n", minMax_->max, minMax_->min);
    free(minMax_);
    free(arrayPtr);
    return 0;
}
