// #include "profile.h"
#include <set>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class RouteManager
{
public:
    void AddRoute(int start, int finish)
    {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const
    {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1)
        {
            return result;
        }

        const set<int> &dests = reachable_lists_.at(start);
        auto range = dests.equal_range(finish);

        if (range.first != range.second)
        {
            return 0;
        }
        else if (range.first != dests.end())
        {
            result = min(result, abs(*range.first - finish));

            if (range.first != dests.begin())
            {
                result = min(result, abs(*(--range.first) - finish));
            }
        }
        else
        {
            return min(result, abs(*(--range.first) - finish));
        }

        return result;
    }
private:
    map<int, set<int>> reachable_lists_;
};


int main()
{
    cin.tie(nullptr);
    // LOG_DURATION("Expresses");
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD")
        {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO")
        {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}
