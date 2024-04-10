// assn07.01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <vector>

void moveCoin(std::vector<int>& coins, int pos1, int pos2);
void printVec(std::vector<int>& vec);

void makePairs(std::vector<int>& coins);

int main()
{
    int rowLength = 10;
    std::vector<int> coins;

    for (int i = 0; i < rowLength; i++)
    {
        coins.push_back(1);
    }

    printVec(coins);
    makePairs(coins);
    printVec(coins);

    int rowLength2 = 22;
    std::vector<int> coins2;
    for (int i = 0; i < rowLength2; i++)
    {
        coins2.push_back(1);
    }
    printVec(coins2);
    makePairs(coins2);
    printVec(coins2);

    return 0;
}

void moveCoin(std::vector<int>& coins, int pos1, int pos2)
{
    if (coins[pos1] != 0)
    {
        if (coins[pos2] != 2)
        {
            coins[pos1]--;
            coins[pos2]++;
        }
    }
}
void printVec(std::vector<int>& vec)
{
    std::cout << "Printing row of " << vec.size() << " coins...\n";
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void makePairs(std::vector<int>& coins)
{
    std::cout << "Making coin pairs...\n";
    for (int i = 0; i < (coins.size() - 1); i++)
    {
        if (coins[i] == 1) { moveCoin(coins, i, i + 1); }
    }
}