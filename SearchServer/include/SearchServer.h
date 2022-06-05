//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_SEARCHSERVER_H
#define SEARCH_PROJECT_SEARCHSERVER_H

#include <vector>
#include <iostream>
#include "InvertedIndex.h"


/**
 * The class responsible for representing the entries of requests
 */
struct RelativeIndex{
    // document index
    size_t doc_id;

    // relative frequency
    float rank;

    // Helper method for use in tests comparing received and expected
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

/**
 * The class responsible for handling the requests
 */
class SearchServer {
public:

    /**
     * Request handler constructor
     * @param idx an indexing input class containing a frequency dictionary
     */
    SearchServer(InvertedIndex& idx);

    /**
     * Request Processing Method
     * @param queries_input query vector
     * @param top_limit maximum number of responses per request
     * @return relevancy response vector for each query
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input, int top_limit=0);
private:

    /**
     * Auxiliary method for getting unique words from a string
     * @param input considered string
     * @return sequence of unique words
     */
    std::vector <std::string> get_unique_words(std::string input);

    // database containing the frequency dictionary
    InvertedIndex &index;
};

#endif //SEARCH_PROJECT_SEARCHSERVER_H


