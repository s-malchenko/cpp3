// #include "profile.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

using namespace std;

class ReadingManager
{
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
          page_ratings_(MAX_PAGE_COUNT_ + 1, 0),
          page_users_(MAX_PAGE_COUNT_ + 1, 0),
          user_count_(0) {}

    void Read(int user_id, int page_count)
    {
        int prevPages = user_page_counts_[user_id];
        int newPages = user_page_counts_[user_id] = page_count;
        PageRating(prevPages, newPages);
    }

    double Cheer(int user_id) const
    {
        return page_ratings_[user_page_counts_[user_id]];
    }

private:
    static const int MAX_USER_COUNT_ = 100000;
    static const int MAX_PAGE_COUNT_ = 1000;

    vector<int> user_page_counts_;
    vector<double> page_ratings_;
    vector<int> page_users_;
    int user_count_;

    void PageRating(int oldPage, int newPage)
    {
        if (oldPage)
        {
            --page_users_[oldPage];
        }
        else
        {
            ++user_count_;
        }
        
        ++page_users_[newPage];

        if (user_count_ == 1)
        {
            page_ratings_[newPage] = 1;
            return;
        }

        int users = 0;

        for (int i = 1; i < page_ratings_.size(); ++i)
        {
            users += page_users_[i - 1];
            page_ratings_[i] = users * 1.0 / (user_count_ - 1);
        }
    }
};


int main()
{
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // LOG_DURATION("ebook");
    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ")
        {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER")
        {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}