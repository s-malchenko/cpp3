#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <set>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection
{
public:
    using Entry = pair<int, size_t>;
    using Id = size_t;

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
            *ids_begin = addElement(*it);
            ++ids_begin;
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const
    {
        if (id >= data.size())
        {
            return false;
        }

        return (iteratorById(id) != priorities.end());
    }

    // Получить объект по идентификатору
    const T &Get(Id id) const
    {
        return data[id].first;
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id)
    {
        set<Entry>::iterator it = iteratorById(id);
        auto entry = *it;
        priorities.erase(it);
        ++entry.first;
        iteratorById(id, priorities.insert(entry).first);
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T &, int> GetMax() const
    {
        auto id = getMaxId();
        return {data[id].first, iteratorById(id)->first};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax()
    {
        auto id = getMaxId();
        pair<T, int> element = {move(data[id].first), iteratorById(id)->first};
        priorities.erase(iteratorById(id));
        iteratorById(id, priorities.end());
        return element;
    }

private:
    // Приватные поля и методы
    set<Entry> priorities;
    vector<pair<T, set<Entry>::iterator>> data;

    Id addElement(T &element)
    {
        data.push_back({move(element), priorities.end()});
        auto index = data.size() - 1;
        data[index].second = priorities.insert({0, index}).first;
        return index;
    }

    Id getMaxId() const
    {
        return (--priorities.end())->second;
    }

    set<Entry>::iterator iteratorById(Id id)
    {
        return data[id].second;
    }

    set<Entry>::const_iterator iteratorById(Id id) const
    {
        return data[id].second;
    }

    void iteratorById(Id id, set<Entry>::iterator it)
    {
        data[id].second = it;
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
