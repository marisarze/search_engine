//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_SEARCHSERVER_H
#define SEARCH_PROJECT_SEARCHSERVER_H

#include <vector>
#include <iostream>
#include "InvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class SearchServer {
public:
    SearchServer(InvertedIndex& idx);
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input, int top_limit=0);
private:
    std::vector <std::string> get_unique_words(std::string input);
    InvertedIndex &index;
};

#endif //SEARCH_PROJECT_SEARCHSERVER_H


