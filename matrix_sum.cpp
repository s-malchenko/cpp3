#include "test_runner.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <future>

using namespace std;

int64_t accumulateVectors(vector<vector<int>>::const_iterator begin, vector<vector<int>>::const_iterator end)
{
    int64_t result = 0;

    for (auto it = begin; it != end; ++it)
    {
        result += accumulate(it->begin(), it->end(), 0);
    }

    return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix)
{
    // Реализуйте эту функцию
    static const int CORE_NUM = 4;
    size_t partSize = matrix.size() / CORE_NUM;
    vector<future<int64_t>> futures;

    for (int i = 0; i < CORE_NUM - 1; ++i)
    {
        futures.push_back(async([&matrix, partSize, i] { return accumulateVectors(matrix.begin() + i * partSize, matrix.begin() + (i + 1) * partSize); }));
    }

    futures.push_back(async([&matrix, partSize] {return accumulateVectors(matrix.begin() + (CORE_NUM - 1) * partSize, matrix.end()); }));

    int64_t result = 0;

    for (auto &i : futures)
    {
        result += i.get();
    }

    return result;
}

void TestCalculateMatrixSum()
{
    const vector<vector<int>> matrix =
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
