#include <iostream>
#include <chrono>
#include "arrayinitializer.h"

int main()
{
    size_t arraySize = 0;

    std::cout << "Enter the size of the array: " << std::flush;
    std::cin >> arraySize;

    size_t threadNumbers = 0;

    std::cout << "Enter the number of threads: " << std::flush;
    std::cin >> threadNumbers;

    const size_t quotient = arraySize / threadNumbers;
    const size_t remainder = arraySize % threadNumbers;

    std::vector<size_t> array;
    array.resize(arraySize, 0);

    std::vector<std::thread> threads;
    threads.reserve(threadNumbers);

    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < threadNumbers; ++i)
        threads.push_back(std::thread(&ArrayInitializer::execute<size_t>, std::ref(array), i,
                                      quotient, remainder, threadNumbers));

    for (size_t i = 0; i < threadNumbers; ++i)
        if (threads.at(i).joinable())
            threads.at(i).join();

    auto end = std::chrono::steady_clock::now();

    for (const auto &it : array) {
        std::cout << '[' << it  << "] " << std::flush;
    }

    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "\nThe time: " << elapsed_ms.count() << std::endl;

    return 0;
}
