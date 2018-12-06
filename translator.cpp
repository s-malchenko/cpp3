#include "test_runner.h"
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class Translator
{
public:
    void Add(string_view source, string_view target)
    {
        const string &sourceRef = *words_.insert(string(source)).first;
        const string &targetRef = *words_.insert(string(target)).first;
        forwardMap_[sourceRef] = targetRef;
        backwardMap_[targetRef] = sourceRef;
    }

    string_view TranslateForward(string_view source) const
    {
        auto it = words_.find(string(source));

        if (it != words_.end())
        {
            try
            {
                return forwardMap_.at(*it);
            }
            catch (...) {}
        }

        return emptyString_;
    }
    string_view TranslateBackward(string_view target) const
    {
        auto it = words_.find(string(target));

        if (it != words_.end())
        {
            try
            {
                return backwardMap_.at(*it);
            }
            catch (...) {}
        }

        return emptyString_;
    }

private:
    set<string> words_;
    map<string_view, string_view> forwardMap_;
    map<string_view, string_view> backwardMap_;
    const string emptyString_;
};


void TestSimple()
{
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
