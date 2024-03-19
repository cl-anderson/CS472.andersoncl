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

void swapTiles(char** arr, int a1, int a2, int b1, int b2)
{
    char a;
    char b;
    a = arr[a1][a2];
    b = arr[b1][b2];
    arr[a1][a2] = b;
    arr[b1][b2] = a;
}

void arrangeTiles(char** arr)
{
    int col = COL;
    int goodColumns = 0;
    while (goodColumns < COL)
    {
        for (int j = 0; j <= 3; j++)
        {
            if (arr[0][j] == arr[1][j] || arr[0][j] == arr[2][j])
            {
                if (j == 0)
                {
                    swapTiles(arr, 0, j, 0, (col - 1));
                }
                else { swapTiles(arr, 0, j, 0, (j - 1)); }
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
                    swapTiles(arr, 1, j, 1, (col - 1));
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
                    swapTiles(arr, 2, j, 2, (col - 1));
                }
                else { swapTiles(arr, 2, j, 2, (j - 1)); }
            }
            goodColumns++;
        }
    }
}

int main()
{
    srand(time(NULL));

    char counter[3][COL];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            int r = (rand() % 3);
            if (r == 0) { counter[i][j] = 'R'; }
            else if (r == 1) { counter[i][j] = 'W'; }
            else if (r == 2) { counter[i][j] = 'B'; }
        }
    }

    std::cout << "Counter BEFORE arranging tiles:\n";
    printCounter(counter);

    arrangeTiles(counter);

    std::cout << "Counter AFTER arranging tiles:\n";
    printCounter(counter);
    return 0;
}