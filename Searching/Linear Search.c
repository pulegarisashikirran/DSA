#include <stdio.h>
int linearSearch(int arr[], int n, int target)
{
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == target)
        {
            return i;
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

    printf("Enter the array elements:\n");

    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the element to search: ");
    scanf("%d", &target);

    result = linearSearch(arr, n, target);

    if(result == -1)
        printf("Element not found");
    else
        printf("Element found at index %d", result);

    return 0;
}

Output:
Enter the size of the array: 5
Enter the array elements:
10
20
30
40
50
Enter the element to search: 30
Element found at index 2
