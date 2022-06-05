#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <map>
#include "InvertedIndex.h"


std::mutex mtx;


void InvertedIndex::handle_doc(std::string sentence, size_t id){
    std::stringstream ss(sentence);
    std::string word;
    while (ss >> word){
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (freq_dictionary.count(word)==0){
            Entry newEntry = {id, 1};
            mtx.lock();
            freq_dictionary[word].push_back(newEntry);
            mtx.unlock();
        } else {
            bool entry_found = false;
            for (auto &entry: freq_dictionary[word]){
                if (entry.doc_id == id){
                    mtx.lock();
                    entry.count++;
                    mtx.unlock();
                    entry_found = true;
                    break;
                }
            }
            if (!entry_found){
                Entry newEntry = {id, 1};
                mtx.lock();
                freq_dictionary[word].push_back(newEntry);
                mtx.unlock();
            }
        }
    }
};


void InvertedIndex::sort_freq_dictionary(){
    for (auto &elem: freq_dictionary){
        auto& value = elem.second;
        for (int i = 0; i < value.size(); i++) {
            for (int j = 0; j < value.size() - i - 1; j++) {
                if (value[j].doc_id >= value[j + 1].doc_id) {
                    auto temp = value[j];
                    value[j] = value[j + 1];
                    value[j + 1] = temp;
                }
            }
        }
    }
}


void InvertedIndex::update_document_base(std::vector <std::string> input_docs){
    std::vector <std::thread> threads;
    for (int i=0;i<input_docs.size(); i++){
        threads.push_back(std::thread(&InvertedIndex::handle_doc, this, input_docs[i], i));
    }
    for (int i=0;i<threads.size(); i++){
        threads[i].join();
    }
    sort_freq_dictionary();
    docs = input_docs;
};


std::vector <Entry> InvertedIndex::get_word_count(const std::string& word){
    std::string for_lowercase = word;
    std::transform(for_lowercase.begin(), for_lowercase.end(), for_lowercase.begin(), ::tolower);
    if (freq_dictionary.count(for_lowercase)==0){
        std::vector <Entry> result = {};
        return result;
    } else {
        return freq_dictionary[for_lowercase];
    }
};
