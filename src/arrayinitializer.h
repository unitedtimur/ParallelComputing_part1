#ifndef ARRAYINITIALIZER_H
#define ARRAYINITIALIZER_H

#include <vector>
#include <thread>
#include <random>

class ArrayInitializer final
{
public:
    template<typename T>
    static void execute(std::vector<T> &array, const size_t threadNumber,
                        const size_t &quotient, const size_t &remainder,
                        const size_t &threadNumbers);

private:
    explicit ArrayInitializer() = default;
    ~ArrayInitializer() = default;

    ArrayInitializer(const ArrayInitializer&) = default;
    ArrayInitializer& operator=(const ArrayInitializer&) = default;
};

template<typename T>
void ArrayInitializer::execute(std::vector<T> &array, const size_t threadNumber,
                               const size_t &quotient, const size_t &remainder,
                               const size_t &threadNumbers)
{
    std::default_random_engine dre(std::time(nullptr));
    std::uniform_int_distribution<> uid(1, 100);

    for (size_t i = threadNumber * quotient; i < quotient * (threadNumber + 1); ++i)
        array[i] = uid(dre);

    const auto index = quotient * threadNumbers + threadNumber;

    if ((index < array.size()) && remainder)
        array[index] = uid(dre);
}

#endif // ARRAYINITIALIZER_H
