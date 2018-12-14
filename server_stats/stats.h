#pragma once

#include "http_request.h"

#include <string_view>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Stats
{
public:
    Stats();
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int> &GetMethodStats() const;
    const map<string_view, int> &GetUriStats() const;
private:
    map<string_view, int> methodStats_;
    map<string_view, int> uriStats_;
    static void addStat(string_view item, map<string_view, int> &stats, const set<string_view> &knownItems, const string &unknownItem);
    static const vector<string> methodNames_;
    static const set<string_view> methods_;
    static const vector<string> uriNames_;
    static const set<string_view> uris_ ;
    static const string unknownMethod_;
    static const string unknownUri_;
};

HttpRequest ParseRequest(string_view line);
