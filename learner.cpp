#include "profile.h"
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner
{
private:
    set<string> dict;

public:
    int Learn(const vector<string> &words)
    {
        int prevSize = dict.size();
        for (const auto &word : words)
        {
            dict.insert(word);
        }
        return dict.size() - prevSize;
    }

    vector<string> KnownWords()
    {
        return {dict.begin(), dict.end()};
    }
};

int main()
{
    Learner guy;

    {
        LOG_DURATION("Learning");
        for (int i = 10000; i > 0; --i)
        {
            guy.Learn({"word" + to_string(i), "Word" + to_string(i)});
        }
    }

    {
        LOG_DURATION("KnownWords");
        auto w = guy.KnownWords();
    }
    return 0;
}
