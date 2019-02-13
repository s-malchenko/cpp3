#pragma once

#include "synchronized.h"
#include <istream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <future>
using namespace std;

class InvertedIndex
{
public:
    void Add(const string &document);
    const vector<size_t> &Lookup(const string &word) const;

    const string &GetDocument(size_t id) const
    {
        return docs[id];
    }

private:
    map<string, vector<size_t>> index;
    vector<string> docs;
};

class SearchServer
{
public:
    SearchServer() = default;
    explicit SearchServer(istream &document_input);
    void UpdateDocumentBase(istream &document_input);
    void AddQueriesStream(istream &query_input, ostream &search_results_output);

private:
    static void updateTask(istream &document_input, Synchronized<InvertedIndex> &index);
    static void searchTask(istream &query_input, ostream &search_results_output, Synchronized<InvertedIndex> &index);
    Synchronized<InvertedIndex> index;
    vector<future<void>> futures;
};
