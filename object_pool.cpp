#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool
{
public:
    T *Allocate()
    {
        T *object = allocateObject();

        if (object == nullptr)
        {
            object = new T;
            allocated.insert(object);
        }
        
        return object;
    }

    T *TryAllocate()
    {
        return allocateObject();
    }

    void Deallocate(T *object)
    {
        if (allocated.count(object))
        {
            allocated.erase(object);
            deallocated.push(object);
        }
        else
        {
            throw invalid_argument("object not allocated");
        }
    }

    ~ObjectPool()
    {
        for (auto i : allocated)
        {
            delete i;
        }

        while (!deallocated.empty())
        {
            delete deallocated.front();
            deallocated.pop();
        }
    }

private:
    set<T *> allocated;
    queue<T *> deallocated;

    T *allocateObject()
    {
        T *object = nullptr;

        if (!deallocated.empty())
        {
            object = deallocated.front();
            deallocated.pop();
            allocated.insert(object);
        }

        return object;
    }
};

void TestObjectPool()
{
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
