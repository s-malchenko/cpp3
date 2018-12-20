#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    static const unsigned num = 3;

    if (range_end - range_begin < num)
    {
        return;
    }

    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

    RandomIt middle1 = elements.begin() + (elements.size() / num);
    RandomIt middle2 = middle1 + (elements.size() / num);
    MergeSort(elements.begin(), middle1);
    MergeSort(middle1, middle2);
    MergeSort(middle2, elements.end());
    vector<typename RandomIt::value_type> tmp;
    merge(make_move_iterator(elements.begin()),
        make_move_iterator(middle1),
        make_move_iterator(middle1),
        make_move_iterator(middle2),
        back_inserter(tmp));
    merge(
        make_move_iterator(tmp.begin()),
        make_move_iterator(tmp.end()),
        make_move_iterator(middle2),
        make_move_iterator(elements.end()),
        range_begin);
}

void TestIntVector()
{
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
