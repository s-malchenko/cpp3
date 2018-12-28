#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <list>

using namespace std;

template <typename T>
class PriorityCollection
{
public:
    using Entry = pair<T, int>;
    using Id = typename list<pair<T, int>>::const_iterator;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object)
    {
        return addElement(object);
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin)
    {
        for (auto it = range_begin; it != range_end; ++it)
        {
            ids_begin = addElement(*it);
            ++ids_begin;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        for (auto i = data.begin(); i != data.end(); ++i)
        {
            if (i == id)
            {
                return true;
            }
        }

        return false;
    }

    // Получить объект по идентификатору
    const T &Get(Id id) const
    {
        return id->first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        ++(convertId(id)->second);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const
    {
        auto id = getMaxId();
        return {id->first, id->second};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        auto id = convertId(getMaxId());
        pair<T, int> element = {move(id->first), id->second};
        data.erase(id);
        return element;
    }

private:
    // Приватные поля и методы
    list<Entry> data;

    Id addElement(T &element)
    {
        data.push_back({move(element), 0});
        return --data.end();
    }

    Id getMaxId() const
    {
        Id result = data.begin();
        int maxPriority = data.front().second;

        for (auto it = data.begin(); it != data.end(); ++it)
        {
            if (it->second >= maxPriority)
            {
                maxPriority = it->second;
                result = it;
            }
        }

        return result;
    }

    typename list<pair<T, int>>::iterator convertId(const Id id)
    {
        return data.erase(id, id);
    }
};


class StringNonCopyable : public string
{
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i)
    {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

void TestConst()
{
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    const auto &constStrings = strings;
    constStrings.GetMax();
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    RUN_TEST(tr, TestConst);
    return 0;
}
