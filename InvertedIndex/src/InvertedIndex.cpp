#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <map>

struct Entry {
    size_t doc_id, count;

    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
private:
    std::map <std::string, std::vector <Entry>> freq_dictionary;
    std::vector <std::string> docs;

    std::mutex mtx;
    void handle_doc(std::string sentence, size_t id){
        std::stringstream ss(sentence);
        std::string word;
        while (ss >> word){
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
    }

public:
    InvertedIndex(){};

    void UpdateDocumentBase(std::vector <std::string> input_docs){
        std::vector <std::thread> threads;
        for (int i=0;i<input_docs.size(); i++){
            std::thread t(&InvertedIndex::handle_doc, this, input_docs[i], i);
            threads.push_back(t);
        }
        for (int i=0;i<threads.size(); i++){
            threads[i].join();
        }
    }

    std::vector <Entry> GetWordCount (const std::string& word){
        if (freq_dictionary.count(word)==0){
            std::vector <Entry> result;
            return result;
        } else {
            return freq_dictionary[word];
        }
    };

};