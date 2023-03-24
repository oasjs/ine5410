#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

void inputArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        int num;
        scanf("%d", &num);
        arr[i] = num;
    }
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int sortAscending(int *num1, int *num2)
{
    return (*num1 - *num2);
}

int sortDescending(int *num1, int *num2)
{
    // printf("num2 %d - num1 %d = %d\n", *num2, *num1, *num2 - *num1);
    return (*num2 - *num1);
}

void sort(int *arr, int size, int (*compare)(int *, int *))
{
    int count;
    for (int i = 0; i < size - 1; i++)
    {
        int diff = compare(&arr[i], &arr[i + 1]);
        int chosenIndex;
        if (diff > 0)
            chosenIndex = i + 1;
        else
            chosenIndex = i;
        // Loops over the next indexes and gets the lowest/highest
        for (int j = i + 2; j < size; j++)
        {
            count++;
            int nextDiff = compare(&arr[i], &arr[j]);
            if (nextDiff > 0)
            {
                if (nextDiff > diff)
                {
                    diff = nextDiff;
                    chosenIndex = j;
                }
            }
        }
        int temp = arr[chosenIndex];
        arr[chosenIndex] = arr[i];
        arr[i] = temp;
    }
    printf("Count: %d\n", count);
}

int main()
{
    int arr[MAX_SIZE];
    int size;
    /*
     * Input array size and elements.
     */
    printf("Enter array size: ");
    scanf("%d", &size);
    printf("Enter elements in array: ");
    inputArray(arr, size);
    printf("\n\nElements before sorting: ");
    printArray(arr, size);
    // Sort and print sorted array in ascending order.
    printf("\n\nArray in ascending order: ");
    sort(arr, size, sortAscending);
    printArray(arr, size);
    // Sort and print sorted array in descending order.
    printf("\nArray in descending order: ");
    sort(arr, size, sortDescending);
    printArray(arr, size);
    return 0;
}