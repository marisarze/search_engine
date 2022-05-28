//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_CONVERTER_H
#define SEARCH_PROJECT_CONVERTER_H

#include <vector>
#include <iostream>
#include <fstream>
#include "SearchServer.h"

class ConverterJSON {
private:
    std::string config_path, requests_path, answers_path;
    std::string read_open_file(std::ifstream &file);
    std::vector <std::vector<RelativeIndex>> to_relative_index(std::vector <std::vector<std::pair<int, float>>> input);

public:
    ConverterJSON();
    ConverterJSON(std::string in_config_path);
    ConverterJSON(std::string in_config_path,
                  std::string in_requests_path);
    ConverterJSON(std::string in_config_path,
                  std::string in_requests_path,
                  std::string in_answers_path);
    void set_config_path(std::string in_config_path);
    std::string get_config_path();

    void set_requests_path(std::string in_requests_path);
    std::string get_requests_path();

    void set_answers_path(std::string in_answers_path);
    std::string get_answers_path();

    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
    void ShowConfigInfo();
    void ValidateConfigFile();
};

#endif //SEARCH_PROJECT_CONVERTER_H


