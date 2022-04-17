#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include "SearchServer.h"
#include "InvertedIndex.h

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer (InvertedIndex& idx): index(idx){};

    std::vector <std::vector<RelativeIndex>> search(const std::vector <std::string>& queries_input){
        std::vector <std::vector<RelativeIndex>> result;
        std::stringstream ss(sentence);
        std::string word;
        for (int i=0;i<queries_input.size();i++){
            std::vector <std::pair <size_t, size_t>> absolute_query_relevance;
            while (ss >> word){
                auto word_count = index.GetWordCount(word);
                for (int j=0;j<word_count.size();j++){
                    bool found = false;
                    for (int k=0;k<absolute_query_relevance.size();k++){
                        if (absolute_query_relevance[k].first==word_count[j].doc_id){
                            found = true;
                            absolute_query_relevance[k].second += word_count[j].count;
                            break;
                        }
                    }
                    if (found==false) absolute_query_relevance.push_back(word_count[j]);
                }
            }
            int max_abs_relevance = 0;
            for (auto &elem: absolute_query_relevance){
                if (elem.second>max_abs_relevance) max_abs_relevance = elem.second;
            }
            std::vector <RelativeIndex> relative_query_relevance;
            for (int j=0;j<absolute_query_relevance.size();j++){
                RelativeIndex temp_pair;
                temp_pair.doc_id = absolute_query_relevance[j].first;
                temp_pair.rank = absolute_query_relevance[j].second / max_abs_relevance
                relative_query_relevance.push_back(temp_pair);
            }
            result.push_back(relative_query_relevance);
        }
        return result;
    }

private:
    InvertedIndex index;
};