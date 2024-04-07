// assn07.02.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// sources: https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>

void printBoard(int(&arr)[9][9]);
bool checkRow(int(&arr)[9][9], int num, int row);
bool checkCol(int(&arr)[9][9], int num, int col);
bool checkBox(int(&arr)[9][9], int num, int row, int col);
bool findEmpty(int(&arr)[9][9], int& row, int& col);
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

    std::cout << "printing the sudoku board: \n\n";
    printBoard(board);

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
    bool numFree = true;
    for (int i = 0; i < 9; i++)
    {
        if (arr[row][i] == num) { return false; }
    }
    return true;
}

bool checkCol(int(&arr)[9][9], int num, int col)
{
    bool numFree = true;
    for (int i = 0; i < 9; i++)
    {
        if (arr[i][col] == num) { return false; }
    }
    return true;
}

bool checkBox(int(&arr)[9][9], int num, int row, int col)
{
    if (row < 3 && col < 3)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (row < 3 && 2 < col < 6)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (row < 3 && 5 < col < 9)
    {
        if (arr[row][col] = num) { return false; }
    }

    if (2 < row < 6 && col < 3)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (2 < row < 6 && 2 < col < 6)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (2 < row < 6 && 5 < col < 9)
    {
        if (arr[row][col] = num) { return false; }
    }

    if (5 < row < 8 && col < 3)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (5 < row < 8 && 2 < col < 6)
    {
        if (arr[row][col] = num) { return false; }
    }
    if (5 < row < 8 && 5 < col < 9)
    {
        if (arr[row][col] = num) { return false; }
    }
    return true;
}

bool checkNum(int(&arr)[9][9], int num, int row, int col)
{
    if (checkRow(arr, num, row) == true && checkCol(arr, num, col) == true && checkBox(arr, num, row, col) == true)
    {
        return true;
    }
}

bool findEmpty(int(&arr)[9][9], int& row, int& col)
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (arr[row][col] == 0) { return true; }
        } 
    }
    return false;
}
bool solver(int(&arr)[9][9])
{
    int row, col;

    if (!findEmpty(arr, row, col)) { return true; }
}