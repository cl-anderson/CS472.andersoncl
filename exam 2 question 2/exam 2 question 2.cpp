// exam 2 question 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// sources: https://stackoverflow.com/questions/17663186/initializing-a-two-dimensional-stdvector,
//          https://forums.codeguru.com/showthread.php?531243-Passing-a-sub-range-of-a-vector-by-reference,
//          https://stackoverflow.com/questions/5891811/generate-random-number-between-1-and-3-in-c

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
const int COL = 5;

template <typename T>
void printCounter(T arr)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
void swapTiles(T* vec, int a1, int a2, int b1, int b2)
{
    char a;
    char b;
    a = vec[a1][a2];
    b = vec[b1][b2];
    vec[a1][a2] = b;
    vec[b1][b2] = a;
}

template <typename T>
void arrangeTiles(T* arr)
{
 
    int goodColumns = 0;
    for (int j = 0; j <= 3; j++)
    {
        if (arr[0][j] == arr[1][j] || arr[0][j] == arr[2][j])
        {
            if (j == 0)
            {
                std::iter_swap(arr.begin(), 0, j, 0, (COL - 1));
            }
            else { swapTiles(arr, 0, j, 0, (j-1)); }
        }
        else
        { 
            goodColumns++;
        }
    }

    for (int j = 0; j <= 3; j++)
    {
        if (arr[1][j] == arr[2][j] || arr[1][j] == arr[0][j])
        {
            if (j == 0)
            {
                swapTiles(arr, 1, j, 1, (COL - 1));
            }
            else { swapTiles(arr, 1, j, 1, (j - 1)); }
        }
        else 
        { 
            goodColumns++;
        }
    }

    for (int j = 0; j <= 3; j++)
    {
        if (arr[2][j] == arr[1][j] || arr[2][j] == arr[0][j])
        {
            if (j == 0)
            {
                swapTiles(arr, 2, j, 2, (COL - 1));
            }
            else { swapTiles(arr, 2, j, 2, (j - 1)); }
        }
        goodColumns++;
    }
}
int main()
{
    srand(time(NULL));

    std::vector<std::vector<char>> counter;
    for (int i = 0; i < 3; i++)
    {
        std::vector<char> row;
        for (int j = 0; j < COL; j++)
        {
            int r = (rand() % 3);
            if (r == 0) { row.push_back('R'); }
            else if (r == 1) { row.push_back('W'); }
            else if (r == 2) { row.push_back('B'); }
        }
        counter.push_back(row);
    }

    std::cout << "Counter BEFORE arranging tiles:\n";
    printCounter(counter);

    std::vector<std::vector<char>>* ptr = &counter;
    arrangeTiles(ptr);

    std::cout << "Counter AFTER arranging tiles:\n";
    printCounter(counter);
    return 0;
}