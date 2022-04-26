#include <vector>
#include <sstream>
#include <thread>
#include <mutex>
#include "SearchServer.h"
#include "InvertedIndex.h"


SearchServer::SearchServer(InvertedIndex& idx): index(idx){};

std::vector <std::vector<RelativeIndex>> SearchServer::search(const std::vector <std::string>& queries_input){
    std::vector <std::vector<RelativeIndex>> result;
    std::string word;
    for (int i=0;i<queries_input.size();i++){
        std::vector <Entry> absolute_query_relevance;
        std::stringstream ss(queries_input[i]);
        while (ss >> word){
            auto word_count = index.GetWordCount(word);
            for (int j=0;j<word_count.size();j++){
                bool found = false;
                for (int k=0;k<absolute_query_relevance.size();k++){
                    if (absolute_query_relevance[k].doc_id==word_count[j].doc_id){
                        found = true;
                        absolute_query_relevance[k].count += word_count[j].count;
                        break;
                    }
                }
                if (found==false) absolute_query_relevance.push_back(word_count[j]);
            }
        }
        int max_abs_relevance = 0;
        for (auto &elem: absolute_query_relevance){
            if (elem.count>max_abs_relevance) max_abs_relevance = elem.count;
        }
        std::vector <RelativeIndex> relative_query_relevance;
        for (int j=0;j<absolute_query_relevance.size();j++){
            RelativeIndex temp_pair;
            temp_pair.doc_id = absolute_query_relevance[j].doc_id;
            temp_pair.rank = absolute_query_relevance[j].count / max_abs_relevance;
            relative_query_relevance.push_back(temp_pair);
        }
        result.push_back(relative_query_relevance);
    }
    return result;
}