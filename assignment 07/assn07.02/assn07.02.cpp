// assn07.02.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// sources: https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/,with, https://www.geeksforgeeks.org/sudoku-backtracking-7/

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>

void printBoard(int (&arr)[9][9]);
bool checkRow(int(&arr)[9][9], int num, int row);
bool checkCol(int(&arr)[9][9], int num, int col);
bool checkBox(int(&arr)[9][9], int num, int row, int col);
std::pair<int,int> findEmpty(int(&arr)[9][9]);
bool solver(int(&arr)[9][9]);
int main()
{
    char myChar;
    std::string charboard[9][9];
    std::fstream puzzleFile("puzzle.txt");

    int rowcount = 1;
    int count = 1;
    while (puzzleFile >> std::skipws >> myChar)
    {
        if (rowcount % 9 == 0) 
        { 
            rowcount++;
        }
        charboard[rowcount - 1][count - 1] = myChar;
        count++;
    }

    int board[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = stoi(charboard[i][j]);
        }
    }

    std::cout << "Printing the unsolved sudoku board...\n\n";
    printBoard(board);

    if (solver(board) == true)
    {
        std::cout << "Printing solved sudoku board...\n\n";
        printBoard(board);
    } 
    else { std::cout << "Failed to solve board.\n"; }

    return 0;
}

void printBoard(int(&arr)[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool checkRow(int(&arr)[9][9], int num, int row)
{
    for (int col = 0; col < 9; col++)
    {
        if (arr[row][col] == num) { return true; }
    }
    return false;
}

bool checkCol(int(&arr)[9][9], int num, int col)
{
    for (int row = 0; row < 9; row++)
    {
        if (arr[row][col] == num) { return true; }
    }
    return false;
}

bool checkBox(int(&arr)[9][9], int num, int rowstart, int colstart)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (arr[row + rowstart][col + colstart] == num) { return true; }

    return false;
}

bool checkNum(int(&arr)[9][9], int num, int row, int col)
{
    return (!checkRow(arr, num, row) && !checkCol(arr, num, col) && !checkBox(arr, num, row - row % 3, col - col % 3) && arr[row][col] == 0);
}

std::pair<int, int> findEmpty(int(&arr)[9][9])
{
    std::pair<int, int> location;
    location.first = -1;
    location.second = -1;
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (arr[row][col] == 0)
            {
                location.first = row;
                location.second = col;
            }
        } 
    }
    return location;
}
bool solver(int(&arr)[9][9])
{
    int row = 0;
    int col = 0;
    std::pair<int, int> emptypair;
    emptypair.first = -1;
    emptypair.second = -1;
    bool solved = false;

    std::pair<int, int> emptySpot = findEmpty(arr);

    /*for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {*/
            if (findEmpty(arr) == emptypair) { return true; }
            else
            {
                std::cout << "Found empty location: " << emptySpot.first << " " << emptySpot.second << std::endl;

                for (int num = 1; num < 10; num++)
                {
                    if (checkNum(arr, num, emptySpot.first, emptySpot.second))
                    {
                        arr[emptySpot.first][emptySpot.second] = num;
                        if (solver(arr))
                            return true;

                        arr[emptySpot.first][emptySpot.second] = 0;
                    }
                }
            }
     /*   }
    }*/
    return solved;
}