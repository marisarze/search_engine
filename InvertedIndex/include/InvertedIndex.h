//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_INVERTEDINDEX_H
#define SEARCH_PROJECT_INVERTEDINDEX_H

#include <vector>
#include <iostream>
#include <map>
#include <mutex>


/**
 * The class responsible for representing the entries in the index
 */
struct Entry {
    // document index
    size_t doc_id;

    // word frequency
    size_t count;

    // Helper method for use in tests comparing received and expected
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};


/**
 * The class responsible for handling the entries in the index
 */
class InvertedIndex {
public:
    // Constructor
    InvertedIndex() = default;

    /**
     * Method for getting the number of words found inside a specific resource file
     * @param word desired value
     * @return vector of entries, specified as a pair of resource sequence number and word count
     */
    std::vector<Entry> get_word_count(const std::string &word);

    /**
     * Method for creating stored index entries
     * @param input_docs original sentences
     */
    void update_document_base(std::vector<std::string> input_docs);
private:

    // Class member containing original sentences
    std::vector<std::string> docs;

    //frequency dictionary
    std::map<std::string, std::vector<Entry>> freq_dictionary;

    /**
     * Auxiliary method to handle single sentence
     * and to update frequency_dictionary
     * @param sentence processed text
     * @param id index of document that contains the processed text
     */
    void handle_doc(std::string sentence, size_t id);

    /**
     * Method sorting the frequency dictionary for purposes of unambiguity
     */
     void sort_freq_dictionary();
};
#endif //SEARCH_PROJECT_INVERTEDINDEX_H


