#include <vector>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <string>
#include "Converter.h"

using json = nlohmann::json;

std::string ConverterJSON::readFile(std::string path){
    std::ifstream file;
    file.open(path);
    if (!file){
        std::cout << "No config file" << std::endl;
        // raise no file error or can't open file error
    } else {
        std::string raw;
        while(true){
            std::string temp;
            file >> temp;
            raw += temp;
            if (file.eof()) break;
            raw += ' ';
        }
        file.close();
        return raw;
    };
};

ConverterJSON::ConverterJSON(std::string inFolder /*=""*/): folder(inFolder){};

std::vector <std::string> ConverterJSON::GetTextDocuments(){
    std::string raw = readFile(folder+"/config.json");
    auto parsedJSON = json::parse(raw);
    auto docsJSON = parsedJSON["files"];
    std::vector <std::string> target;
    for (auto it = docsJSON.begin();it!=docsJSON.end(); it++){
        std::string docDirectory = it.value();
        std::string raw = readFile(docDirectory);
        target.push_back(raw);
    }
    return target;
}


int ConverterJSON::GetResponsesLimit(){
    std::string raw = readFile(folder+"/config.json");
    auto parsedJSON = json::parse(raw);
    return parsedJSON["config"]["max_responses"];
}


std::vector <std::string> ConverterJSON::GetRequests(){
    std::string raw = readFile(folder+"/requests.json");
    auto parsedJSON = json::parse(raw);
    auto requestsJSON = parsedJSON["requests"];
    std::vector <std::string> target;
    for (auto it = requestsJSON.begin();it!=requestsJSON.end(); it++){
        target.push_back(it.value());
    }
    return target;
};

void ConverterJSON::putAnswers(std::vector <std::vector<std::pair<int, float>>> answers){
    json answersJSON = {{"answers", {}}};
    for (int request_id=0;request_id<answers.size();request_id++){
        std::string request_key = "request" + std::to_string(request_id+1);
        json answerEntry = {};
        if (answers[request_id].size()==0)
            answerEntry["result"]="false";
        else {
            answerEntry["result"]="true";
            answerEntry["relevance"] = json::array();
            for (int doc_id=0;doc_id<answers[request_id].size();doc_id++){
                json pair = {};
                pair["docid"] = answers[request_id][doc_id].first;
                pair["rank"] = answers[request_id][doc_id].second;
                answerEntry["relevance"].insert(answerEntry["relevance"].end(), pair);
            }
        }
        answersJSON[request_key] = answerEntry;
    }
    std::ofstream file(folder+"/answers.json");
    file << answersJSON.dump(4);
    file.close();
}