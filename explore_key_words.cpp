#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
#include <functional>
#include <iostream>
#include <sstream>
#include <list>
using namespace std;

struct Stats
{
    map<string, int> word_frequences;

    void operator += (const Stats &other)
    {
        for (auto i : other.word_frequences)
        {
            word_frequences[i.first] += i.second;
        }
    }
};

Stats ExploreLine(const set<string> &key_words, const string &line)
{
    Stats result;
    size_t pos = 0;

    while (true)
    {
        auto pos2 = line.find(' ', pos);
        auto word = line.substr(pos, pos2 - pos);

        if (key_words.count(word))
        {
            ++result.word_frequences[word];
        }

        if (pos2 == string::npos)
        {
            break;
        }
        else
        {
            pos = pos2 + 1;
        }
    }

    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input)
{
    Stats result;

    for (string line; getline(input, line); )
    {
        result += ExploreLine(key_words, line);
    }

    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
    Stats result;
    vector<future<Stats>> v;
    list<stringstream> streams;
    const size_t threadLines = 100000;

    while (input)
    {
        stringstream ss;
        size_t i = threadLines;

        for (string line; getline(input, line) && i; --i)
        {
            ss << move(line) << "\n";
        }

        streams.push_back(move(ss));
        v.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(streams.back())));
    }

    for (auto &i : v)
    {
        result += i.get();
    }

    return result;
}

void TestBasic()
{
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    const int repeatNum = 100000;
    for (int i = 0; i < repeatNum; ++i)
    {
        ss << "this new yangle service really rocks\n";
        ss << "It sucks when yangle isn't available\n";
        ss << "10 reasons why yangle is the best IT company\n";
        ss << "yangle rocks others suck\n";
        ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    }

    {
        LOG_DURATION("Making stats");
        const auto stats = ExploreKeyWords(key_words, ss);
        const map<string, int> expected =
        {
            {"yangle", 6 * repeatNum},
            {"rocks", 2 * repeatNum},
            {"sucks", 1 * repeatNum}
        };
        ASSERT_EQUAL(stats.word_frequences, expected);
    }
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
