// exam 2 question 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// sources: https://cplusplus.com/forum/general/5705/
// worst case complexity O(N * M). This Oompa-Loompa cleanup is no joke. For an ideal complexity, the silly Oompa-Loompa should drop all his coins in a single row or column.
#include <iostream>
#include <vector>

const int N = 10;
const int M = 10;
int COINCOUNT = 0;
std::vector<std::pair<int, int>> PATH;
struct node
{
    int num = -1;
    bool visited = false;
};


template <typename T>
void findPath(T arr, int i, int j)
{
    std::pair<int, int> location;

    if ((i+1) < N && arr[i + 1][j].num == 1 && !arr[i + 1][j].visited)
    {
        arr[i + 1][j].visited = true;
        COINCOUNT++;
        location.first = (i + 1);
        location.second = j;
        PATH.push_back(location);
        findPath(arr, (i + 1), j);
    }
    else if ((j+1) < M && arr[i][j+1].num == 1 && !arr[i][j+1].visited)
    {
        arr[i][j+1].visited = true;
        COINCOUNT++;
        location.first = i;
        location.second = (j+1);
        PATH.push_back(location);
        findPath(arr, i, (j+1));
    }
    else 
    {
        if ((i + 1) < N)
        {
            arr[i + 1][j].visited = true;
            findPath(arr, (i + 1), j);
        }
        else if ((j + 1) < M)
        {
            arr[i][j + 1].visited = true;
            findPath(arr, i, (j + 1));
        }
    }
}

int main()
{
    node warehouseFloor[N][M];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int r = rand();
            if (r % 2 == 0) { warehouseFloor[i][j].num = 0; }
            else { warehouseFloor[i][j].num = 1; }
        }
    }

    findPath(warehouseFloor, 0, 0);
    std::cout << "Number of coins recovered: " << COINCOUNT << std::endl;
    std::cout << "Path taken:\n";
    for (auto i : PATH)
    {
        std::cout << "(" << i.first << ", " << i.second << ")\n";
    }



    return 0;
}
