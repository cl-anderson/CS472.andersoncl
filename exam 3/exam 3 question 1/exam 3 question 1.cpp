// exam 3 question 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

std::vector<int> keySort(std::vector<int> vec);
int NUMSIZE = 3;
int main()
{
    std::cout << "Enter the max number of digits for your integers:  ";
    std::cin >> NUMSIZE;
    std::vector<int> unsortedList;
    int intIn = 0;
    for (int x = 0; x < 4; x++)
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
    std::cout << "Length of number: " << std::to_string(unsortedList[0]).length();
    
    std::vector<int> sortedList;
    sortedList = keySort(unsortedList);

    std::cout << "\nPrinting sorted list...\n";
    for (auto x : sortedList)
    {
        std::cout << x << std::endl;
    }

    return 0;
}

std::vector<int> keySort(std::vector<int> vec)
{
    std::vector<int> list0, list1, list2, list3, list4, list5, list6, list7, list8, list9;
    std::vector<std::vector<int>> megaList{ list0, list1, list2, list3, 
        list4, list5, list6, list7, list8, list9 };
    for (int x = 0; x < vec.size(); x++)
    {
        megaList[0].push_back(vec[x]);
    }
   
    std::string numString;
    int digit = 0;
    for (int w = 1; w <= NUMSIZE; w++)
    {
        for (int subList = 0; subList < megaList.size(); subList++)
        {
            for (int num = 0; num < megaList[subList].size(); num++)
            {
                int number = megaList[subList][num];
                std::cout << "\nnumber: " << number;
                numString = std::to_string(number);
                std::cout << "\nnumString: " << numString << "\n";
                if (numString.length() > w)
                {
                    std::cout << "digitchar: " << numString[numString.length() - w] << "\n";
                    char digitchar = numString[numString.length() - w];
                    digit = digitchar - '0';
                    std::cout << "digit: " << digit << "\n";
                    megaList[digit].push_back(number);
                    //megaList[subList][num] = -1;
                    megaList[subList].erase(std::remove(megaList[subList].begin(), megaList[subList].end(), number), megaList[subList].end());
                }
            }
        }
    }
    std::vector<int> sortedVec;
    for (int x = 0; x < megaList.size(); x++)
    {
        for (int y = 0; y < megaList[x].size(); y++)
        {
         sortedVec.push_back(megaList[x][y]); 
        }
    }
    
    return sortedVec;
}