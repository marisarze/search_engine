//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_CONVERTER_H
#define SEARCH_PROJECT_CONVERTER_H

#include <vector>
#include <iostream>

class ConverterJSON {
private:
    std::string folder = "";
    std::string readFile(std::string path);

public:
    ConverterJSON() = default;
    ConverterJSON(std::string inFolder="");
    std::vector<std::string> GetTextDocuments();
    int GetResponsesLimit();
    std::vector<std::string> GetRequests();
    void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
};

#endif //SEARCH_PROJECT_CONVERTER_H


