#include <iostream>
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

    for (size_t i = 0; i < threadNumbers; ++i) {
        threads.push_back(std::thread(&ArrayInitializer::execute<size_t>, std::ref(array), i,
                                      quotient, remainder, threadNumbers));

        if (threads.at(i).joinable())
            threads.at(i).join();
    }

    for (const auto &it : array) {
        std::cout << '[' << it  << "] " << std::flush;
    }

    std::cout << std::endl;

    return 0;
}
