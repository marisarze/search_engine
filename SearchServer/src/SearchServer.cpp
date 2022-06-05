#include <vector>
#include <sstream>
#include <thread>
#include <algorithm>
#include <stdexcept>
#include "SearchServer.h"
#include "InvertedIndex.h"


SearchServer::SearchServer(InvertedIndex& idx): index(idx){};


std::vector <std::string> SearchServer::get_unique_words(std::string input){
    std::vector <std::string> unique;
    std::string word;
    std::stringstream ss(input);
    while (ss >> word){
        if (std::find(unique.begin(), unique.end(), word)==unique.end()){
            unique.push_back(word);
        }
    }
    return unique;
};


std::vector <std::vector<RelativeIndex>> SearchServer::search(const std::vector <std::string>& queries_input, int top_limit){
    if (top_limit<0){
        std::string error_message = "Error. Top limit must be positive or zero, current value top_limit = " + std::to_string(top_limit);
        throw std::invalid_argument(error_message);
    }
    std::vector <std::vector<RelativeIndex>> result;
    for (int i=0;i<queries_input.size();i++){
        std::vector <Entry> abs_relevance = {};
        auto unique = get_unique_words(queries_input[i]);
        for (auto &word: unique){
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            auto word_count = index.get_word_count(word);
            for (int j=0;j<word_count.size();j++){
                bool found = false;
                for (int k=0;k<abs_relevance.size();k++){
                    if (abs_relevance[k].doc_id==word_count[j].doc_id){
                        found = true;
                        abs_relevance[k].count += word_count[j].count;
                        break;
                    }
                }
                if (found==false) abs_relevance.push_back(word_count[j]);
            }
        }
        int temp_top_limit = abs_relevance.size();
        if (top_limit>0){
            temp_top_limit=std::min((int)abs_relevance.size(),top_limit);
        }

        if (abs_relevance.size()>1){
            for (int j = 0; j < temp_top_limit; j++) {
                for (int k = 0; k < abs_relevance.size() - j - 1; k++) {
                    if (abs_relevance[k].count >= abs_relevance[k + 1].count) {
                        auto temp = abs_relevance[k];
                        abs_relevance[k] = abs_relevance[k + 1];
                        abs_relevance[k + 1] = temp;
                    }
                }
            }
        }
        std::vector <RelativeIndex> relative_query_relevance = {};
        std::vector <Entry> top_abs_relevance = {};

        for (int j=0;j<temp_top_limit;j++){
            top_abs_relevance.push_back(abs_relevance[abs_relevance.size()-1-j]);
        }

        if (top_abs_relevance.size()>0){
            int max_abs_relevance = top_abs_relevance[0].count;
            for (int j=0;j<top_abs_relevance.size();j++){
                RelativeIndex temp_pair;
                temp_pair.doc_id = top_abs_relevance[j].doc_id;
                temp_pair.rank = (float)top_abs_relevance[j].count / (float)max_abs_relevance;
                relative_query_relevance.push_back(temp_pair);
            }
        }
        result.push_back(relative_query_relevance);
    }
    return result;
}