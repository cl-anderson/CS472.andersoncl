// assn07.01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <vector>

void moveCoin(std::vector<int>& coins, int pos1, int pos2);
void printVec(std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl << std::endl;
}

void makePairs(std::vector<int>& coins)
{
    for (int i; i < coins.size(); i++)
    {
        if (i == 0 || coins[i - 1] != 1)
        {

        }
    }
}
int main()
{
    int rowLength = 10;
    std::vector<int> coins;

    for (int i = 0; i < rowLength; i++)
    {
        coins.push_back(1);
    }

    printVec(coins);

    moveCoin(coins, 0, 3);

    printVec(coins);

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