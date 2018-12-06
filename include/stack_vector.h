#pragma once

#include <stdexcept>
#include <array>
using namespace std;

template <typename T, size_t N>
class StackVector
{
public:
    explicit StackVector(size_t a_size = 0)
    {
        if (a_size > N)
        {
            throw invalid_argument("invalid size");
        }

        end_ = values_.begin() + a_size;
    }

    T &operator[](size_t index)
    {
        return values_[index];
    }

    const T &operator[](size_t index) const
    {
        return values_[index];
    }

    typename array<T, N>::iterator begin()
    {
        return values_.begin();
    }

    typename array<T, N>::iterator end()
    {
        return end_;
    }

    typename array<T, N>::const_iterator begin() const
    {
        return values_.begin();
    }

    typename array<T, N>::const_iterator end() const
    {
        return end_;
    }

    size_t Size() const
    {
        return end_ - values_.begin();
    }
    size_t Capacity() const
    {
        return N;
    }

    void PushBack(const T &value)
    {
        if (end_ != values_.end())
        {
            *end_++ = value;
        }
        else
        {
            throw overflow_error("overflow");
        }
    }

    T PopBack()
    {
        if (end_ != values_.begin())
        {
            return *(--end_);

        }
        else
        {
            throw underflow_error("underflow");
        }
    }

private:
    typename array<T, N>::iterator end_;
    array<T, N> values_;
};

