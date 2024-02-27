// assn 04.02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <random>

std::string generateString(std::string str, int length)
{
    int gen = 0;
    for (int i = 0; i < length; i++)
    {
        gen = rand() % 3;
        if (gen == 0)
        {
            str.append("r");
        }
        else if (gen == 1)
        {
            str.append("w");
        }
        else if (gen == 2)
        {
            str.append("b");
        }
    }
    return str;
}

std::string sortCandy(std::string str)
{
    std::string check = "";
    std::string newstring;
    int reds = 0, whites = 0, blues = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'r') 
        { 
            check = "red";
            reds++;
        }
        else if (str[i] == 'w') 
        { 
            check = "white";
            whites++;
        }
        else if (str[i] == 'b') 
        { 
            check = "blue";
            blues++;
        }
    }
    for (int i = 0; i < reds; i++)
    {
        newstring.push_back('r');
    }
    for (int i = 0; i < whites; i++)
    {
        newstring.push_back('w');
    }
    for (int i = 0; i < blues; i++)
    {
        newstring.push_back('b');
    }
    return newstring;
}

int main()
{
    srand(time(NULL));
    std::string basestring = "";
    basestring = generateString(basestring, 10);
    std::cout << basestring;

    basestring = sortCandy(basestring);
    std::cout << std::endl << basestring;

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
