// assn07.02.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// sources: https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/

#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>

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

}
int main()
{
    char myChar;
    std::string myStr;
    std::string charboard[9][9];
    int board[9][9];
    std::fstream puzzleFile("puzzle.txt");

    int rowcount = 1;
    int count = 1;
    while (puzzleFile >> std::skipws >> myChar)
    {
        if (rowcount % 9 == 0) 
        { 
            //std::cout << std::endl;
            rowcount++;
        }
        //std::cout << myChar << " ";
        charboard[rowcount - 1][count - 1] = myChar;
        count++;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = stoi(charboard[i][j]);
        }
    }

    std::cout << "printing from the sudoku board: \n\n";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}