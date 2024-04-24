// exam 3 question 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

std::vector<int> keySort(std::vector<int> vec);
int main()
{
    std::vector<int> unsortedList;
    int intIn = 0;
    for (int x = 0; x < 9; x++)
    {
        std::cout << "Enter an integer for the list: ";
        std::cin >> intIn;
        unsortedList.push_back(intIn);
    }

    std::cout << "\nPrinting unsorted list...\n";
    for (auto x : unsortedList)
    {
        std::cout << x << std::endl;
    }
    
    std::vector<int> sortedList;
    sortedList = keySort(unsortedList);

    return 0;
}

std::vector<int> keySort(std::vector<int> vec)
{
    std::vector<int> list0, list1, list2, list3, list4, list5, list6, list7, list8, list9;
    int saveNum = -1;
    int digit = 0;
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < int(log10(x) + 1); y++)
        {
            saveNum = vec[x];
            digit = saveNum[y];
            std::cout << digit << ".";
        }
        std::cout << "\n";
    }
    return vec;
}