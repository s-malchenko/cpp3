#include "test_runner.h"
#include <vector>

template <typename T>
class Deque
{
public:
    Deque() {}

    size_t Size() const
    {
        return _front.size() + _back.size();
    }

    bool Empty()
    {
        return _front.empty() && _back.empty();
    }

    void PushFront(const T &value)
    {
        _front.push_back(value);
    }

    void PushBack(const T &value)
    {
        _back.push_back(value);
    }

    const T& Front() const
    {
        if (!_front.empty())
        {
            return _front._back();
        }
        else if (!_back.empty())
        {
            return _back[0];
        }
        else
        {
            return _front.begin();
        }
    }

    T& Front()
    {
        if (!_front.empty())
        {
            return _front._back();
        }
        else if (!_back.empty())
        {
            return _back[0];
        }
        else
        {
            return _front.begin();
        }
    }


private:
    vector<T> _front;
    vector<T> _back;
};

void TestTable()
{
    Deque<int> d;
    ASSERT_EQUAL(d.Size(), 0);
    d.PushBack(2);
    ASSERT_EQUAL(d.Size(), 1);
    d.PushFront(1);
    ASSERT_EQUAL(d.Size(), 2);
    ASSERT_EQUAL(d.Front(), 1);
    ASSERT_EQUAL(d.Back(), 2);
    const Deque<int> cd;
    ASSERT_EQUAL(cd.Size(), 0);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}