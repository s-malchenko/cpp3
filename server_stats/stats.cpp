#include "stats.h"

const vector<string> Stats::methodNames_ = {"GET", "POST", "PUT", "DELETE"};
const set<string_view> Stats:: methods_(methodNames_.begin(), methodNames_.end());
const vector<string> Stats::uriNames_ = {"/", "/order", "/product", "/basket", "/help"};
const set<string_view> Stats::uris_(uriNames_.begin(), uriNames_.end());
const string Stats::unknownMethod_("UNKNOWN");
const string Stats::unknownUri_("unknown");

Stats::Stats()
{
    for (auto i : methods_)
    {
        methodStats_[i] = 0;
    }
    methodStats_[unknownMethod_] = 0;

    for (auto i : uris_)
    {
        uriStats_[i] = 0;
    }
    uriStats_[unknownUri_] = 0;
}

void Stats::AddMethod(string_view method)
{
    addStat(method, methodStats_, methods_, unknownMethod_);
}

void Stats::AddUri(string_view uri)
{
    addStat(uri, uriStats_, uris_, unknownUri_);
}
const map<string_view, int> &Stats::GetMethodStats() const
{
    return methodStats_;
}

const map<string_view, int> &Stats::GetUriStats() const
{
    return uriStats_;
}

void Stats::addStat(string_view item, map<string_view, int> &stats, const set<string_view> &knownItems, const string &unknownItem)
{
    auto pos = knownItems.find({item});

    if (pos != knownItems.end())
    {
        ++stats[*pos];
    }
    else
    {
        ++stats[unknownItem];
    }
}

HttpRequest ParseRequest(string_view line)
{
    static const int PARTS = 3;
    vector<string_view> splitted(PARTS);
    size_t pos = 0, i = 0;

    while (i != PARTS)
    {
        size_t space = line.find(' ', pos);
        splitted[i] = line.substr(pos, space - pos);

        if (space == line.npos)
        {
            break;
        }
        else 
        {
            pos = space + 1;

            if (splitted[i].size())
            {
                ++i;
            }
        }
    }

    return {splitted[0], splitted[1], splitted[2]};
}
