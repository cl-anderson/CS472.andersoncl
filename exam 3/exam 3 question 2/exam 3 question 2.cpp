// exam 3 question 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// this is an exponential algorithm and not linear because the input size isn't actually the integer itself,
// but rather the number of bits it takes to store it. when we represent a number in binary, 
// the number of bits is generally equal to the ceiling of the logarithm base 2 of the integer. bits = ceil(log2(integer)). 
// sources: https://www.quora.com/How-do-you-find-the-number-of-bits-in-an-integer

#include <iostream>
#include <string>
#include <vector>

bool testPrimality(int testnum);
int main()
{
    int testNum = 0;
    std::cout << "Enter a number to be tested for primality: ";
    std::cin >> testNum;

    std::cout << "\nA 1 denotes primality.\n";
    std::cout << testNum << " primality: " << testPrimality(testNum);
    return 0;
}

bool testPrimality(int testnum)
{
    for (int x = 2; x < (testnum / 2); x++)
    {
        if (testnum % x == 0) { return false; }
    }
    return true;
}