// exam 1 question 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// purpose: closest pair implementation, with euclidean and hamming distance functions
// //
// sources: https://blog.hubspot.com/website/call-a-function-in-c, CS472 lecture materials

#include <iostream>
#include <vector>
#include <functional>

template <typename T>
double euclideanDist(std::pair<T, T> pair)
{
    double d = 0;
    d = ((pair.first)^2 + (pair.second)^2);
    d = sqrt(d);
    return d;
}

template <typename T>
double hammingDist(std::pair<T, T> pair)
{
    std::string a, b;
    a = pair.first;
    b = pair.second;
    double dist = 0;
    for (int x = 0; x < a.length(); x++)
    {
        if (a[x] != b[x]) { dist++; }
    }
    return dist;
}

template <typename T>
double closestPair(double (*func)(std::pair<T, T>), std::vector<std::pair<T, T>> pairs)
{
    double dist = 0;
    double y = 0;
    std::vector<double> dlist;
    for (int i = 0; i < pairs.size(); i++)
    {
        dist = func(pairs[i]);
        dlist.push_back(dist);
    }
    double minDist = dlist[0];
    for (int x = 0; x < dlist.size(); x++)
    {
        y = dlist[x];
        if (y < minDist) { minDist = y; }
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

    std::vector<std::pair<int, int>> intPairs;
    intPairs.push_back(paira);
    intPairs.push_back(pairb);
    intPairs.push_back(pairc);
    intPairs.push_back(paird);
    intPairs.push_back(paire);

    std::cout << "Distance of the closest int pair: " << closestPair(euclideanDist, intPairs);

    std::pair<std::string, std::string> spaira("ambystoma", "plethodon");
    std::pair<std::string, std::string> spairb("dogtired", "hogwired");
    std::pair<std::string, std::string> spairc("weeping", "wailing");
    std::pair<std::string, std::string> spaird("john f", "john l");
    std::pair<std::string, std::string> spaire("scouting", "scraping");

    std::vector<std::pair<std::string, std::string>> stringPairs;
    stringPairs.push_back(spaira);
    stringPairs.push_back(spairb);
    stringPairs.push_back(spairc);
    stringPairs.push_back(spaird);
    stringPairs.push_back(spaire);

    std::cout << "\nDistance of the closest string pair: " << closestPair(hammingDist, stringPairs);
    return 0;
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
