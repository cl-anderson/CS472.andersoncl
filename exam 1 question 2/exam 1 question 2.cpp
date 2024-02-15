// exam 1 question 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>

template <typename T>
double euclideanDist(std::pair<T, T> pair)
{
    double d = 0;
    d = ((pair.first)^2 + (pair.second)^2);
    d = sqrt(d);
    return d;
}

template <typename T>
double hammingDist(std::pair<T, T>)
{

}

template <typename T>
double closestPair(double *func, std::list<std::pair<T, T>> pairs)
{
    double dist = 0;
    double dlist = [];
    for (int i = 0; i < pairs.size(); i++)
    {
        dist = func(pairs[i]);
        dlist[i] = dist;
    }
    int minDist = dlist[0];
    for (int x = 0; x < dlist.size(); x++)
    {
        if (dlist[x] < minDist) { minDist = dlist[x]; }
    }
    return minDist;
}

int main()
{
    std::pair<int, int> paira(1, 78);
    std::pair<int, int> pairb(13, 457);
    std::pair<int, int> pairc(892, 23);
    std::pair<int, int> paird(1982, 16);
    std::pair<int, int> paire(1, 8);

    std::list<std::pair<int, int>> intPairs;
    intPairs.push_back(paira);
    intPairs.push_back(pairb);
    intPairs.push_back(pairc);
    intPairs.push_back(paird);
    intPairs.push_back(paire);

    std::pair<int, int> testPair(0, 0);
    closestPair(double (*euclideanDist)(testPair), intPairs);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
