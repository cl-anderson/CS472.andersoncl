// assn08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// sources: https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/,with, https://www.geeksforgeeks.org/sudoku-backtracking-7/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Graph.hpp"

struct node { int num; int row; int col; int box; };
void printBoard(int(&arr)[9][9]);
void printNodeBoard(node(&arr)[9][9]);
bool checkRow(int(&arr)[9][9], int num, int row);
bool checkCol(int(&arr)[9][9], int num, int col);
bool checkBox(int(&arr)[9][9], int num, int row, int col);
std::pair<int, int> findEmpty(int(&arr)[9][9]);
bool solver(int(&arr)[9][9]);
AdjacencyListGraph<int> makeGraph(node(&arr)[9][9]);

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

    node board[9][9];
    node x;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            x.num = stoi(charboard[i][j]);
            x.row = i;
            x.col = j;
            // identifying boxes
            // top row
            if (i < 3 && j < 3) { x.box = 1; }
            if (i < 3 && 2 < j < 6) { x.box = 2; }
            if (i < 3 && 5 < j < 9) { x.box = 3; }
            // middle row
            if (2 < i < 6 && j < 3) { x.box = 4; }
            if (2 < i < 6 && 2 < j < 6) { x.box = 5; }
            if (2 < i < 6 && 5 < j < 9) { x.box = 6; }
            // bottom row
            if (6 < i < 9 && j < 3) { x.box = 7; }
            if (6 < i < 9 && 2 < j < 6) { x.box = 8; }
            if (6 < i < 9 && 5 < j < 9) { x.box = 9; }
            board[i][j] = x;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

        }
    }


    std::cout << "Printing the unsolved sudoku board...\n\n";
    printNodeBoard(board);

    /*if (solver(board) == true)
    {
        std::cout << "Printing solved sudoku board...\n\n";
        printNodeBoard(board);
    }
    else { std::cout << "Failed to solve board.\n"; }*/

    /*char myChar2;
    std::string charboard2[9][9];
    std::fstream puzzleFile2("puzzle.txt");

    rowcount = 1;
    count = 1;
    while (puzzleFile2 >> std::skipws >> myChar2)
    {
        if (rowcount % 9 == 0)
        {
            rowcount++;
        }
        charboard2[rowcount - 1][count - 1] = myChar2;
        count++;
    }

    int board2[9][9];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board2[i][j] = stoi(charboard2[i][j]);
        }
    }

    std::cout << "Printing the unsolved sudoku board 2...\n\n";
    printBoard(board2);

    if (solver(board2) == true)
    {
        std::cout << "Printing solved sudoku board 2...\n\n";
        printBoard(board2);
    }
    else { std::cout << "Failed to solve board 2.\n"; }*/
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

void printNodeBoard(node(&arr)[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << arr[i][j].num << " ";
        }
        std::cout << std::endl;
    }
}

AdjacencyListGraph<int> makeGraph(int(&arr)[9][9])
{
    int row = -1;
    int col = -1;
    AdjacencyListGraph<int> newgraph;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            for (auto k : arr[i]) { newgraph.addEdge(arr[i][j], arr[i][k]); }
            for (int l = 0; l < 9; l++) { newgraph.addEdge(arr[i][j], arr[l][j]); }
        }
    }
    return newgraph;
}
bool checkRow(int(&arr)[9][9], int num, int row)
{
    for (int col = 0; col < 9; col++)
    {
        if (arr[row][col] == num) { return true; }
    }
    return false;
}

bool checknodeRow(AdjacencyListGraph<int> graph, node n)
{
    for (auto x : n.neighbors)
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

bool checknodeCol(AdjacencyListGraph<int> graph, int num, int col)
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