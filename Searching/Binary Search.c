#include <stdio.h>
int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(arr[mid] == target)
        {
            return mid;
        }
        else if(arr[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int n, target, result;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the sorted array elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
                                
    printf("Enter the element to search: ");
    scanf("%d", &target);

    result = binarySearch(arr, n, target);

    if(result == -1)
        printf("Element not found");
    else
        printf("Element found at index %d", result);

    return 0;
}

// U can write this after for loop in main function to Check whether the array is sorted
for(int i = 0; i < n - 1; i++)
{
    if(arr[i] > arr[i + 1])
    {
        printf("Array is not sorted");
        return 0;
    }
}   //If you want your program to detect unsorted input, use this code.


Output:
Enter the size of the array: 5
Enter the sorted array elements:
10
20
30
40
50
Enter the element to search: 40
Element found at index 3
