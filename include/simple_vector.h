#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector
{
public:
    SimpleVector()
    {
        begin_ = nullptr;
        end_ = nullptr;
        capacity_ = 0;
    }

    explicit SimpleVector(size_t size)
    {
        begin_ = new T[size];
        end_ = begin_ + size;
        capacity_ = size;
    }

    SimpleVector(const SimpleVector<T> &other)
    : begin_(new T[other.capacity_]),
    end_(begin_ + other.Size()),
    capacity_(other.capacity_)
    {
        std::copy(other.begin(), other.end(), begin());
    }

    ~SimpleVector()
    {
        delete[] begin_;
    }

    void operator=(const SimpleVector<T> &other)
    {
        delete[] begin_;
        begin_ = new T[other.capacity_];
        end_ = begin_ + other.Size();
        capacity_ = other.capacity_;
        std::copy(other.begin(), other.end(), begin());
    }

    T &operator[](size_t index)
    {
        return *(begin_ + index);
    }

    const T &operator[](size_t index) const
    {
        return *(begin_ + index);
    }

    T *begin() { return begin_; }
    T *end() { return end_; }
    const T *begin() const { return begin_; }
    const T *end() const { return end_; }

    size_t Size() const
    {
        return end_ - begin_;
    }

    size_t Capacity() const
    {
        return capacity_;
    }

    void PushBack(const T &value)
    {
        if (capacity_ == 0)
        {
            capacity_ = 1;
            begin_ = new T[1];
            end_ = begin_ ;
        }
        else if (capacity_ - Size() < 1)
        {
            capacity_ <<= 1;
            T *newBegin = new T[capacity_];
            std::copy(begin_, end_, newBegin);
            delete[] begin_;
            end_ = newBegin + Size();
            begin_ = newBegin;
        }

        *(end_++) = value;
    }

private:
    // Добавьте поля для хранения данных вектора
    T *begin_;
    T *end_;
    size_t capacity_;
};
