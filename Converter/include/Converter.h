//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_CONVERTER_H
#define SEARCH_PROJECT_CONVERTER_H

#include <vector>
#include <iostream>
#include <fstream>

class ConverterJSON {
private:
    std::string config_path, requests_path, answers_path;
    std::string read_open_file(std::ifstream &file);

public:
    ConverterJSON(std::string in_config_path, std::string in_requests_path, std::string in_answers_path);
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
    void ShowConfigInfo();
    void ValidateConfigFile();
};

#endif //SEARCH_PROJECT_CONVERTER_H


