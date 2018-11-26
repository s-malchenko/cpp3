// #include "test_runner.h"
#include <vector>

using namespace std;

template <typename T>
class Deque
{
public:
    Deque() {}

    size_t Size() const
    {
        return _front.size() + _back.size();
    }

    bool Empty() const
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

    const T &Front() const
    {
        if (!_front.empty())
        {
            return _front.back();
        }
        else
        {
            return _back[0];
        }
    }

    T &Front()
    {
        if (!_front.empty())
        {
            return _front.back();
        }
        else
        {
            return _back[0];
        }
    }

    const T &Back() const
    {
        if (!_back.empty())
        {
            return _back.back();
        }
        else
        {
            return _front[0];
        }
    }

    T &Back()
    {
        if (!_back.empty())
        {
            return _back.back();
        }
        else
        {
            return _front[0];
        }
    }

    const T &At(size_t i) const
    {
        if (i < _front.size())
        {
            return _front.at(_front.size() - i - 1);
        }
        else
        {
            return _back.at(i - _front.size());
        }
    }

    T &At(size_t i)
    {
        if (i < _front.size())
        {
            return _front.at(_front.size() - i - 1);
        }
        else
        {
            return _back.at(i - _front.size());
        }
    }

    const T &operator[](size_t i) const
    {
        if (i < _front.size())
        {
            return _front[_front.size() - i - 1];
        }
        else
        {
            return _back[i - _front.size()];
        }
    }

    T &operator[](size_t i)
    {
        if (i < _front.size())
        {
            return _front[_front.size() - i - 1];
        }
        else
        {
            return _back[i - _front.size()];
        }
    }

private:
    vector<T> _front;
    vector<T> _back;
};

// void TestTable()
// {
//     Deque<int> d;
//     ASSERT_EQUAL(d.Size(), 0);
//     d.PushBack(2);
//     ASSERT_EQUAL(d.Size(), 1);
//     d.PushFront(1);
//     ASSERT_EQUAL(d.Size(), 2);
//     ASSERT_EQUAL(d.Front(), 1);
//     ASSERT_EQUAL(d.Back(), 2);
//     const Deque<int> cd;
//     ASSERT_EQUAL(cd.Size(), 0);

//     ASSERT_EQUAL(d.At(0), 1);
//     ASSERT_EQUAL(d.At(1), 2);
//     ASSERT_EQUAL(d[0], 1);
//     ASSERT_EQUAL(d[1], 2);
    
//     try
//     {
//         d.At(3);
//         ASSERT(false);
//     }
//     catch (out_of_range &e)
//     {

//     }
//     catch (...)
//     {
//         ASSERT(false);
//     }
// }

// int main()
// {
//     TestRunner tr;
//     RUN_TEST(tr, TestTable);
//     return 0;
// }