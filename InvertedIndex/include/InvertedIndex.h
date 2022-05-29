//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_INVERTEDINDEX_H
#define SEARCH_PROJECT_INVERTEDINDEX_H

#include <vector>
#include <iostream>
#include <map>
#include <mutex>

struct Entry {
    size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};


class InvertedIndex {
public:
    InvertedIndex() = default;
    std::vector<Entry> get_word_count(const std::string &word);
    void update_document_base(std::vector<std::string> input_docs);
private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freq_dictionary;
    void handle_doc(std::string sentence, size_t id);
};
#endif //SEARCH_PROJECT_INVERTEDINDEX_H


