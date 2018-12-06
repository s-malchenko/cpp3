#include <iostream>
#include <list>
#include <vector>
#include <iterator>

using namespace std;

static const int ATHLETES_NUM = 100000;

int main ()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    size_t q;
    cin >> q;

    list<int> rank;
    vector<list<int>::iterator> refs(ATHLETES_NUM, rank.end());

    for (int i = 0; i < q; ++i)
    {
        size_t num, prev;
        cin >> num >> prev;
        refs[num] = rank.insert(refs[prev], num);
    }

    for (auto a : rank)
    {
        cout << a << " ";
    }

    return 0;
}
