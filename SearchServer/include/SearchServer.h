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
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx);
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input, int top_limit=0);
private:
    std::vector <std::string> GetUniqueWords(std::string input);
    InvertedIndex index;
};

#endif //SEARCH_PROJECT_SEARCHSERVER_H


