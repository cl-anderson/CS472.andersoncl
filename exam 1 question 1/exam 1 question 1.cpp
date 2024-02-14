// exam 1 question 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// purpose: insertion and modified insertion sort functions.
// the modified insertion sort is faster because instead of using a linear search to find the spot
// each element moves to, we use a binary search. So instead of a O(n) (linear efficiency),
// it's O(log n) (logarithmic efficiency). The binary search gets faster as the list is progressively 
// more sorted.
//
// sources: https://www.geeksforgeeks.org/insertion-sort/?ref=lbp, https://www.geeksforgeeks.org/binary-insertion-sort/?ref=lbp

#include <iostream>

template <typename T>
void insertionSort(T arr[], int n)
{
    T i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

template <typename T>
T binarySearch(int a[], T item,
    T low, T high)
{
    if (high <= low)
        return (item > a[low]) ?
        (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == a[mid])
        return mid + 1;

    if (item > a[mid])
        return binarySearch(a, item,
            mid + 1, high);
    return binarySearch(a, item, low,
        mid - 1);
}

template <typename T>
void modifiedinsertionSort(T a[], int n)
{
    int i, loc, j, k, selected;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];

        // find location where selected should be inserted
        loc = binarySearch(a, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = selected;
    }
}

// A utility function to print an array
// of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

// Driver code
int main()
{
    int arr[] = { 12, 11, 13, 5, 6 };
    int size_arr = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, size_arr);
    std::cout << "Insertion sorted array: ";
    printArray(arr, size_arr);


    int a[]
        = { 37, 23, 0, 17, 12, 72, 31, 46, 100, 88, 54 };
    int size_a = sizeof(a) / sizeof(a[0]), i;

    modifiedinsertionSort(a, size_a);

    std::cout << "Modified insertion sorted array: \n";
    printArray(a, size_a);
    return 0;
}