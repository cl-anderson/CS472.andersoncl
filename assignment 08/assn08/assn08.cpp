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

struct node { int num = 0; int box = 0; std::vector<node> neighbors; };
void printBoard(int(&arr)[9][9]);
void printGraph(node(&arr)[9][9]);
void makeGraph(node(&arr)[9][9]);
bool checkRow(int(&arr)[9][9], int num, int row);
bool checkCol(int(&arr)[9][9], int num, int col);
bool checkBox(int(&arr)[9][9], int num, int row, int col);
std::pair<int, int> findEmpty(int(&arr)[9][9]);
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
    std::cout << "test";
    node board[9][9];
    node x;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            x.num = stoi(charboard[i][j]);
            // identifying boxes
            // top row
            if (i < 3 && j < 3) { x.box = 1; }
            else if (i < 3 && 2 < j < 6) { x.box = 2; }
            else if (i < 3 && 5 < j < 9) { x.box = 3; }
            // middle row
            else if (2 < i < 6 && j < 3) { x.box = 4; }
            else if (2 < i < 6 && 2 < j < 6) { x.box = 5; }
            else if (2 < i < 6 && 5 < j < 9) { x.box = 6; }
            // bottom row
            else if (6 < i < 9 && j < 3) { x.box = 7; }
            else if (6 < i < 9 && 2 < j < 6) { x.box = 8; }
            else if (6 < i < 9 && 5 < j < 9) { x.box = 9; }
            board[i][j] = x;
        }
    }
    std::cout << "\nsecond test";
    makeGraph(board);
    std::cout << "Printing the unsolved sudoku board...\n\n";
    printGraph(board);

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

void printGraph(node(&arr)[9][9])
{
    std::cout << "\nmade it into printgraph";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << arr[i][j].num << " ";
        }
        std::cout << std::endl;
    }
}

void makeGraph(node(&arr)[9][9])
{
    std::vector<std::pair<int, int>> row1; // to avoid iterating through the entire array for every single node, we'll save each node to the appropriate list. and use these to add to neighbors
    std::vector<std::pair<int, int>> row2;
    std::vector<std::pair<int, int>> row3;
    std::vector<std::pair<int, int>> row4;
    std::vector<std::pair<int, int>> row5;
    std::vector<std::pair<int, int>> row6;
    std::vector<std::pair<int, int>> row7;
    std::vector<std::pair<int, int>> row8;
    std::vector<std::pair<int, int>> row9;

    std::vector<std::pair<int, int>> col1;
    std::vector<std::pair<int, int>> col2;
    std::vector<std::pair<int, int>> col3;
    std::vector<std::pair<int, int>> col4;
    std::vector<std::pair<int, int>> col5;
    std::vector<std::pair<int, int>> col6;
    std::vector<std::pair<int, int>> col7;
    std::vector<std::pair<int, int>> col8;
    std::vector<std::pair<int, int>> col9;

    std::vector<std::pair<int, int>> box1; 
    std::vector<std::pair<int, int>> box2;
    std::vector<std::pair<int, int>> box3;
    std::vector<std::pair<int, int>> box4;
    std::vector<std::pair<int, int>> box5;
    std::vector<std::pair<int, int>> box6;
    std::vector<std::pair<int, int>> box7;
    std::vector<std::pair<int, int>> box8;
    std::vector<std::pair<int, int>> box9;
    std::pair<int, int> location;
    std::pair<int, int> location2;
    std::cout << "\nmade it into makegraph";
    std::cout << "\nmaking row col connections...";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            location.first = i;
            location.second = j;
            for (int k = 0; k < 9; k++) // add every node in node arr[i][j]'s row to its neighbors
            { 
                location2.first = i; 
                location2.second = k; 
                if (i == 0) { row1.push_back(location2); }
                else if (i == 1) { row1.push_back(location2); }
                else if (i == 2) { row2.push_back(location2); }
                else if (i == 3) { row3.push_back(location2); }
                else if (i == 4) { row4.push_back(location2); }
                else if (i == 5) { row5.push_back(location2); }
                else if (i == 6) { row6.push_back(location2); }
                else if (i == 7) { row7.push_back(location2); }
                else if (i == 8) { row8.push_back(location2); }
            }
            for (int l = 0; l < 9; l++) // add every node in node arr[i][j]'s col to its neighbors
            {
                location2.first = l;
                location2.second = j;
                if (i == 0) { row1.push_back(location2); }
                else if (i == 1) { col1.push_back(location2); }
                else if (i == 2) { col2.push_back(location2); }
                else if (i == 3) { col3.push_back(location2); }
                else if (i == 4) { col4.push_back(location2); }
                else if (i == 5) { col5.push_back(location2); }
                else if (i == 6) { col6.push_back(location2); }
                else if (i == 7) { col7.push_back(location2); }
                else if (i == 8) { col8.push_back(location2); }
            }
    
            if (arr[i][j].box == 1) {box1.push_back(location);} // adding nodes to appropriate boxes
            else if (arr[i][j].box == 2) { box2.push_back(location); }
            else if (arr[i][j].box == 3) { box3.push_back(location); }
            else if (arr[i][j].box == 4) { box4.push_back(location); }
            else if (arr[i][j].box == 5) { box5.push_back(location); }
            else if (arr[i][j].box == 6) { box6.push_back(location); }
            else if (arr[i][j].box == 7) { box7.push_back(location); }
            else if (arr[i][j].box == 8) { box8.push_back(location); } 
            else if (arr[i][j].box == 9) { box9.push_back(location); }
        }
    }
    std::cout << "\nmaking box connections...";
    for (int i = 0; i < 9; i++)
    {
        std::cout << "row " << i << std::endl;
        for (int j = 0; j < 9; j++)
        {
            if (arr[i][j].box == 1)
            {
                for (auto m : box1) { arr[i][j].neighbors.push_back(arr[m.first][m.second]); }
            }
            else if (arr[i][j].box == 2)
            {
                for (auto n : box2) { arr[i][j].neighbors.push_back(arr[n.first][n.second]); }
            }
            else if (arr[i][j].box == 3)
            {
                for (auto o : box3) { arr[i][j].neighbors.push_back(arr[o.first][o.second]); }
            }
            else if (arr[i][j].box == 4)
            {
                for (auto p : box4) { arr[i][j].neighbors.push_back(arr[p.first][p.second]); }
            }
            else if (arr[i][j].box == 5)
            {
                for (auto q : box5) { arr[i][j].neighbors.push_back(arr[q.first][q.second]); }
            }
            else if (arr[i][j].box == 6)
            {
                for (auto r : box6) { arr[i][j].neighbors.push_back(arr[r.first][r.second]); }
            }
            else if (arr[i][j].box == 7)
            {
                for (auto s : box7) { arr[i][j].neighbors.push_back(arr[s.first][s.second]); }
            }
            else if (arr[i][j].box == 8)
            {
                for (auto t : box8) { arr[i][j].neighbors.push_back(arr[t.first][t.second]); }
            }
            else if (arr[i][j].box == 9)
            {
                for (auto u : box9) { arr[i][j].neighbors.push_back(arr[u.first][u.second]); }
            }
        }
    }
    std::cout << "\nall connections complete";
}
bool checkRow(int(&arr)[9][9], int num, int row)
{
    for (int col = 0; col < 9; col++)
    {
        if (arr[row][col] == num) { return true; }
    }
    return false;
}

//bool checknodeRow(AdjacencyListGraph<int> graph, node n)
//{
//    for (auto x : n.neighbors)
//    {
//        if (arr[row][col] == num) { return true; }
//    }
//    return false;
//}

bool checkCol(int(&arr)[9][9], int num, int col)
{
    for (int row = 0; row < 9; row++)
    {
        if (arr[row][col] == num) { return true; }
    }
    return false;
}

//bool checknodeCol(AdjacencyListGraph<int> graph, int num, int col)
//{
//    for (int row = 0; row < 9; row++)
//    {
//        if (arr[row][col] == num) { return true; }
//    }
//    return false;
//}

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