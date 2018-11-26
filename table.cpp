#include "test_runner.h"
#include <utility>

using namespace std;

// Реализуйте здесь шаблонный класс Table
template <typename T>
class Table
{
public:
    Table(size_t rows, size_t cols)
    {
        resize(rows, cols);
    }

    pair<size_t, size_t> Size() const
    {
        return make_pair(_table.size(), _table[0].size());
    }

    void Resize(size_t rows, size_t cols)
    {
        resize(rows, cols);
    }

    vector<T>& operator[](size_t i)
    {
        return _table[i];
    }

    const vector<T>& operator[](size_t i) const
    {
        return _table[i];
    }

private:
    vector<vector<T>> _table;
    void resize(size_t rows, size_t cols)
    {
        _table.resize(rows);
        for (auto &r : _table)
        {
            r.resize(cols);
        }
    }
};

void TestTable()
{
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
