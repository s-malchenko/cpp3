#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
void setGroup(String &s, vector<set<Char<String>>> &dict, vector<Group<String>> &groups)
{
    vector<bool> result(dict.size(), true);

    for (const auto &c : s)
    {
        for (size_t i = 0; i < dict.size(); ++i)
        {
            bool factor = dict[i].count(c);
            result[i] = result[i] && factor;
        }

        if (find(result.begin(), result.end(), true) == result.end())
        {
            dict.push_back(set<Char<String>>(s.begin(), s.end()));
            groups.push_back({move(s)});
            return;
        }
    }
}

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings)
{
    // Напишите реализацию функции,
    // использовав не более 1 копирования каждого символа
    vector<set<Char<String>>> groupSymbols;
    vector<Group<String>> groups;

    for (auto &s : strings)
    {
        setGroup(s, groupSymbols, groups);
    }

    return groups;
}


void TestGroupingABC()
{
    vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
    ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal()
{
    vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
    ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
    ASSERT_EQUAL(groups[2], vector<string>({"port"}));
    ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}
