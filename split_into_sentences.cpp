#include "test_runner.h"

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    Sentence<Token> currentSentence;
    vector<Sentence<Token>> result;
    bool sentenceFinished = false;

    for (auto it = tokens.begin(); it != tokens.end(); ++it)
    {
        if (it->IsEndSentencePunctuation())
        {
            sentenceFinished = true;
        }
        else if (sentenceFinished)
        {
            result.push_back(move(currentSentence));
            sentenceFinished = false;
        }

        currentSentence.push_back(move(*it));
    }

    result.push_back(move(currentSentence));
    return result;
}


struct TestToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken &other) const
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>(
    {
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
    );

    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>(
    {
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
    );

    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>(
    {
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
    );
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestSplitting);
    return 0;
}
