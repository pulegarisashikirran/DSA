#include <stdio.h>

void selectionSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;

        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[min])
                min = j;
        }

        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

int main()
{
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the array elements:\n");

    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    selectionSort(arr, n);

    printf("Sorted array:\n");

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}


Output:
Enter the size of the array: 5
Enter the array elements:
50
20
40
10
30
Sorted array:
10 20 30 40 50
