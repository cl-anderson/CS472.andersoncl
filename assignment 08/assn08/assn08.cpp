// assn08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// sources: https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/,with, https://www.geeksforgeeks.org/sudoku-backtracking-7/,
//          https://github.com/walkerje/C-Turtle, https://www.geeksforgeeks.org/draw-color-filled-shapes-in-turtle-python/,
//          https://community.wolfram.com/groups/-/m/t/2983903
// A NOTE: i couldn't get the svae display function to work, sorry! but you can look at the display 
// and screenshot it if needed (the save display error message gives you time to screenshot)
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <utility>
#include <vector>
#include "Graph.hpp"
#include "CImg.h"
#include "CTurtle.hpp"

#define cimg_use_png
#define _cimg_sge_ext1 "png"
#define _cimg_sge_ext2 "png"

struct node { int num = 0; int box = 0; std::vector<std::pair<int,int>> rowNeighbors; std::vector<std::pair<int, int>> columnNeighbors; std::vector<std::pair<int, int>> boxNeighbors; };
void printGraph(node(&arr)[9][9]);
void saveGraph(node(&arr)[9][9]);
void drawGraph(node(&arr)[9][9]);
void makeGraph(node(&arr)[9][9]);
bool checkRow(node(&arr)[9][9], int num, std::pair<int, int> location);
bool checkCol(node(&arr)[9][9], int num, std::pair<int, int> location);
bool checkBox(node(&arr)[9][9], int num, std::pair<int, int> location);
bool checkNum(node(&arr)[9][9], int num, std::pair<int, int> location);
std::pair<int, int> findEmpty(node(&arr)[9][9]);
bool solver(node(&arr)[9][9]);

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
            // identifying boxes
            // top row
            if (i < 3)
            {
                if (j < 3) { x.box = 1; }
                else if (j > 2 && j <= 5) { x.box = 2; }
                else if (j >= 6 && j < 9) { x.box = 3; }
            }
            // middle row
            else if (i > 2 && i < 6)
            {
                if (j < 3) { x.box = 4; }
                else if (j > 2 && j < 6) { x.box = 5; }
                else if (j >= 6 && j < 9) { x.box = 6; }
            }
            // bottom row
            else if (i >= 6)
            {
                if (j < 3) { x.box = 7; }
                else if (j > 2 && j < 6) { x.box = 8; }
                else if (j >= 6 && j < 9) { x.box = 9; }
            }
            board[i][j] = x;
        }
    }
    makeGraph(board);
    std::cout << "\nPrinting the unsolved sudoku board...\n\n";
    printGraph(board);

    if (solver(board) == true)
    {
        std::cout << "Printing solved sudoku board...\n\n";
        printGraph(board);
        saveGraph(board);
        std::cout << "Saved solved sudoku board to new text file.\n\n";
    }
    else { std::cout << "Failed to solve board.\n"; }

    drawGraph(board);
    
    return 0;
}

void printGraph(node(&arr)[9][9])
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

void saveGraph(node(&arr)[9][9])
{
    std::ofstream puzzleFile("solvedpuzzle.txt");
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            puzzleFile << arr[i][j].num << " ";
        }
        puzzleFile << std::endl;
    }
    puzzleFile.close();
}

void drawGraph(node(&arr)[9][9])
{
    namespace ct = cturtle;
    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);
    turtle.speed(ct::TS_FASTEST);
    for (int i = 0; i < 9; i++)
    {
        turtle.penup();
        turtle.goTo(-10, ((i-5) * -40));
        for (int j = 0; j < 9; j++)
        {
            if (arr[i][j].num == 1) { turtle.fillcolor({ "tomato" }); }
            else if (arr[i][j].num == 2) { turtle.fillcolor({ "orange" }); }
            else if (arr[i][j].num == 3) { turtle.fillcolor({ "yellow" }); }
            else if (arr[i][j].num == 4) { turtle.fillcolor({ "lawn green" }); }
            else if (arr[i][j].num == 5) { turtle.fillcolor({ "light sea green" }); }
            else if (arr[i][j].num == 6) { turtle.fillcolor({ "light blue" }); }
            else if (arr[i][j].num == 7) { turtle.fillcolor({ "blue" }); }
            else if (arr[i][j].num == 8) { turtle.fillcolor({ "purple" }); }
            else if (arr[i][j].num == 9) { turtle.fillcolor({ "pink" }); }
            turtle.pendown();
            turtle.begin_fill();
            for (int i = 0; i < 5; i++)
            {
                turtle.forward(40);
                turtle.right(90);
            }
            turtle.end_fill();
            turtle.penup();
            turtle.left(90);
        }
        turtle.penup();
    }
    scr.save("9 colored sudoku.png");
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
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            location.first = i;
            location.second = j;
            if (i == 0) { row1.push_back(location2); }
            else if (i == 1) { row2.push_back(location); }
            else if (i == 2) { row3.push_back(location); }
            else if (i == 3) { row4.push_back(location); }
            else if (i == 4) { row5.push_back(location); }
            else if (i == 5) { row6.push_back(location); }
            else if (i == 6) { row7.push_back(location); }
            else if (i == 7) { row8.push_back(location); }
            else if (i == 8) { row9.push_back(location); }

            if (i == 0) { col1.push_back(location2); }
            else if (i == 1) { col2.push_back(location); }
            else if (i == 2) { col3.push_back(location); }
            else if (i == 3) { col4.push_back(location); }
            else if (i == 4) { col5.push_back(location); }
            else if (i == 5) { col6.push_back(location); }
            else if (i == 6) { col7.push_back(location); }
            else if (i == 7) { col8.push_back(location); }
            else if (i == 8) { col9.push_back(location); }
    
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
    std::cout << "\nmaking connections...\n";
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            if (arr[i][j].box == 1)
            {
                for (auto position : box1) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 2)
            {
                for (auto position : box2) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 3)
            {
                for (auto position : box3) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 4)
            {
                for (auto position : box4) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 5)
            {
                for (auto position : box5) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 6)
            {
                for (auto position : box6) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 7)
            {
                for (auto position : box7) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 8)
            {
                for (auto position : box8) { arr[i][j].boxNeighbors.push_back(position); }
            }
            else if (arr[i][j].box == 9)
            {
                for (auto position : box9) { arr[i][j].boxNeighbors.push_back(position); }
            }

            if (i == 0)
            {
                for (auto position : row1) { arr[i][j].rowNeighbors.push_back(position); }
                for (auto position1 : col1) { arr[i][j].columnNeighbors.push_back(position1); }
            }
            else if (i == 1)
            {
                for (auto position2 : row2) { arr[i][j].rowNeighbors.push_back(position2); }
                for (auto position3 : col2) { arr[i][j].columnNeighbors.push_back(position3); }
            }
            else if (i == 2)
            {
                for (auto position4 : row3) { arr[i][j].rowNeighbors.push_back(position4); }
                for (auto position5 : col3) { arr[i][j].columnNeighbors.push_back(position5); }
            }
            else if (i == 3)
            {
                for (auto position6 : row4) { arr[i][j].rowNeighbors.push_back(position6); }
                for (auto position7 : col4) { arr[i][j].columnNeighbors.push_back(position7); }
            }
            else if (i == 4)
            {
                for (auto position8 : row5) { arr[i][j].rowNeighbors.push_back(position8); }
                for (auto position9 : col5) { arr[i][j].columnNeighbors.push_back(position9); }
            }
            else if (i == 5)
            {
                for (auto position10 : row6) { arr[i][j].rowNeighbors.push_back(position10); }
                for (auto position11 : col6) { arr[i][j].columnNeighbors.push_back(position11); }
            }
            else if (i == 6)
            {
                for (auto position12 : row7) { arr[i][j].rowNeighbors.push_back(position12); }
                for (auto position13 : col7) { arr[i][j].columnNeighbors.push_back(position13); }
            }
            else if (i == 7)
            {
                for (auto position14 : row8) { arr[i][j].rowNeighbors.push_back(position14); }
                for (auto position15 : col8) { arr[i][j].columnNeighbors.push_back(position15); }
            }
            else if (i == 8)
            {
                for (auto position16 : row9) { arr[i][j].rowNeighbors.push_back(position16); }
                for (auto position17 : col9) { arr[i][j].columnNeighbors.push_back(position17); }
            }
        }
    }
    std::cout << "\nall connections complete";
}

bool checkRow(node(&arr)[9][9], int testnum, std::pair<int, int> location)
{
    for (auto x : arr[location.first][location.second].rowNeighbors)
    {
        if (testnum == arr[x.first][x.second].num) { return true; }
    }
    return false;
}
bool checkCol(node(&arr)[9][9], int testnum, std::pair<int, int> location)
{
    for (auto x : arr[location.first][location.second].columnNeighbors)
    {
        if (testnum == arr[x.first][x.second].num) { return true; }
    }
    return false;
}
bool checkBox(node(&arr)[9][9], int testnum, std::pair<int, int> location)
{
    for (auto x : arr[location.first][location.second].boxNeighbors)
    {
        if (testnum == arr[x.first][x.second].num) { return true; }
    }
    return false;
}

bool checkNum(node(&arr)[9][9], int testnum, std::pair<int,int> location)
{
    if (checkRow(arr, testnum, location) == false && checkCol(arr, testnum, location) == false && checkBox(arr, testnum, location) == false) { return true; }
    else { return false; }
}

std::pair<int, int> findEmpty(node(&arr)[9][9])
{
    std::pair<int, int> location;
    location.first = -1;
    location.second = -1;
    for (int row = 0; row <= 8; row++)
    {
        for (int col = 0; col <= 8; col++)
        {
            if (arr[row][col].num == 0)
            {
                location.first = row;
                location.second = col;
                return location;
            }
        }
    }
}
bool solver(node(&arr)[9][9])
{
    int row = 0;
    int col = 0;
    std::pair<int, int> emptypair;
    emptypair.first = -1;
    emptypair.second = -1;
    bool solved = false;

    std::pair<int, int> emptySpot = findEmpty(arr);

    if (emptySpot == emptypair) { return true; }
    else
    {
        //std::cout << "Found empty location: " << emptySpot.first << " " << emptySpot.second << std::endl;

        for (int num = 1; num < 10; num++)
        {
            if (checkNum(arr, num, emptySpot))
            {
                arr[emptySpot.first][emptySpot.second].num = num;
                if (solver(arr))
                    return true;
                else { arr[emptySpot.first][emptySpot.second].num = 0; }
                
            }
        }
    }
    return solved;
}