#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string &line)
{
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream &document_input)
{
    indexReady = false;
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input)
{
    if (indexReady)
    {
        futures.push_back(async(updateTask, ref(document_input), ref(index)));
    }
    else
    {
        updateTask(document_input, index);
        indexReady = true;
    }
}

void SearchServer::updateTask(istream &document_input, Synchronized<InvertedIndex> &index)
{
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); )
    {
        new_index.Add(move(current_document));
    }

    index.GetAccess().ref_to_value = move(new_index);
}

void SearchServer::AddQueriesStream(istream &query_input, ostream &search_results_output)
{
    futures.push_back(async(searchTask, ref(query_input), ref(search_results_output), ref(index)));
}

void SearchServer::searchTask(istream &query_input, ostream &search_results_output, Synchronized<InvertedIndex> &index)
{
    vector<pair<size_t, size_t>> search_results;

    for (string current_query; getline(query_input, current_query); )
    {
        search_results.assign(50000, {0, 0});
        const auto words = SplitIntoWords(current_query);

        for (const auto &word : words)
        {
            vector<size_t> lookupResult;

            {
                lookupResult = index.GetAccess().ref_to_value.Lookup(word);
            }

            for (const size_t docid : lookupResult)
            {
                if (docid + 1 > search_results.size())
                {
                    search_results.resize(docid + 1);
                }

                search_results[docid].first = docid;
                search_results[docid].second++;
            }
        }

        partial_sort(begin(search_results), begin(search_results) + 5, end(search_results), [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs)
        {
            int64_t lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            int64_t rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        }
                    );

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5))
        {
            if (docid || hitcount)
            {
                search_results_output << " {" << "docid: " << docid << ", " << "hitcount: " << hitcount << '}';
            }
        }

        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string &document)
{
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    for (const auto &word : SplitIntoWords(document))
    {
        index[word].push_back(docid);
    }
}

const vector<size_t> &InvertedIndex::Lookup(const string &word) const
{
    static const vector<size_t> v;
    if (auto it = index.find(word); it != index.end())
    {
        return it->second;
    }
    else
    {
        return v;
    }
}
