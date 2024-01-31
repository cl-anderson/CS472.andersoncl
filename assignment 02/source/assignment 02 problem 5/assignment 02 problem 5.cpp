// assignment 02 problem 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
// author: cl-anderson
// purpose: measurement of sort()
// sources: https://en.cppreference.com/w/cpp/algorithm/sort, https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time, 
//          https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <chrono>

std::vector<double> GenerateRandomDataSet(std::vector<double>, int);
double calcAverage(std::vector<double> timeVec);

int main()
{
    
    std::vector<double> time5vec;
    std::vector<double> first5vec;
    for (int count = 0; count < 200; count++)
    {
        first5vec = GenerateRandomDataSet(first5vec, 5);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first5vec.begin(), first5vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time5vec.push_back(x);
    }
    double vec5average = calcAverage(time5vec);
    
    std::vector<double> time10vec;
    std::vector<double> first10vec;
    for (int count = 0; count < 200; count++)
    {
        first10vec = GenerateRandomDataSet(first10vec, 10);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first10vec.begin(), first10vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time10vec.push_back(x);
    }
    double vec10average = calcAverage(time10vec);

    std::vector<double> time50vec;
    std::vector<double> first50vec;
    for (int count = 0; count < 200; count++)
    {
        first50vec = GenerateRandomDataSet(first50vec, 50);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first50vec.begin(), first50vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time50vec.push_back(x);
    }
    double vec50average = calcAverage(time50vec);

    std::vector<double> time100vec;
    std::vector<double> first100vec;
    for (int count = 0; count < 200; count++)
    {
        first100vec = GenerateRandomDataSet(first100vec, 100);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first100vec.begin(), first100vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time100vec.push_back(x);
    }
    double vec100average = calcAverage(time100vec);

    std::vector<double> time500vec;
    std::vector<double> first500vec;
    for (int count = 0; count < 200; count++)
    {
        first500vec = GenerateRandomDataSet(first100vec, 500);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first500vec.begin(), first500vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time500vec.push_back(x);
    }
    double vec500average = calcAverage(time500vec);

    std::vector<double> time1000vec;
    std::vector<double> first1000vec;
    for (int count = 0; count < 200; count++)
    {
        first1000vec = GenerateRandomDataSet(first1000vec, 1000);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first1000vec.begin(), first1000vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time1000vec.push_back(x);
    }
    double vec1000average = calcAverage(time1000vec);

    std::vector<double> time5000vec;
    std::vector<double> first5000vec;
    for (int count = 0; count < 200; count++)
    {
        first5000vec = GenerateRandomDataSet(first5000vec, 5000);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first5000vec.begin(), first5000vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time5000vec.push_back(x);
    }
    double vec5000average = calcAverage(time5000vec);

    std::vector<double> time10000vec;
    std::vector<double> first10000vec;
    for (int count = 0; count < 200; count++)
    {
        first10000vec = GenerateRandomDataSet(first10000vec, 10000);

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        std::sort(first10000vec.begin(), first10000vec.end());
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        auto x = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        time10000vec.push_back(x);
    }
    double vec10000average = calcAverage(time10000vec);

    std::cout << "Average time to sort vector length 5: " << vec5average << std::endl;
    std::cout << "Average time to sort vector length 10: " << vec10average << std::endl;
    std::cout << "Average time to sort vector length 50: " << vec50average << std::endl;
    std::cout << "Average time to sort vector length 100: " << vec100average << std::endl;
    std::cout << "Average time to sort vector length 500: " << vec500average << std::endl;
    std::cout << "Average time to sort vector length 1000: " << vec1000average << std::endl;
    std::cout << "Average time to sort vector length 5000: " << vec5000average << std::endl;
    std::cout << "Average time to sort vector length 10000: " << vec10000average << std::endl;
    return 0;
}

std::vector<double> GenerateRandomDataSet(std::vector<double> dataSet, int size)
{
    std::random_device randev;
    std::mt19937 mersenne_engine{ randev() };
    std::uniform_int_distribution<int> dist{ 1, 10000 };

    for (int i = 0; i < size; i++)
    {
        int x = 0;
        x = dist(mersenne_engine);
        dataSet.push_back(x);
    }

    return dataSet;
}

double calcAverage(std::vector<double> timeVec)
{
    double avgTime = 0;
    for (auto i = 0; i < timeVec.size(); i++)
    {
        avgTime += timeVec[i];
    }
    avgTime = (avgTime / timeVec.size());
    return avgTime;
}