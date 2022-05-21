#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <string>
#include <stdexcept>
#include "Converter.h"
#include "SearchServer.h"

using json = nlohmann::json;

std::string ConverterJSON::read_open_file(std::ifstream &file){
    std::string raw;
    while(true){
        std::string temp;
        file >> temp;
        raw += temp;
        if (file.eof()) break;
        raw += ' ';
    }
    return raw;
};

void ConverterJSON::ValidateConfigFile(){
    std::ifstream config_file;
    config_file.open(config_path);
    if (!config_file){
        std::string error_message = "Config file with path " + config_path + " is missing";
        throw std::runtime_error(error_message);
    }
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    if(parsedJSON.count("config")==0){
        throw std::runtime_error("Config file is empty");
    }
    config_file.close();
}

ConverterJSON::ConverterJSON(std::string in_config_path, std::string in_requests_path, std::string in_answers_path):
    config_path(in_config_path),requests_path(in_requests_path),answers_path(in_answers_path){};

void ConverterJSON::ShowConfigInfo(){
    std::ifstream config_file;
    config_file.open(config_path);
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    auto config_part = parsedJSON["config"];
    std::string info = "";
    if (config_part.count("name")){
        info = info + "search engine name: " + config_part["name"].get<std::string>() + '\n';
    }
    if (config_part.count("version")){
        info = info + "search engine version: " + config_part["version"].get<std::string>() + '\n';
    }
    std::cout << info;
};

std::vector <std::string> ConverterJSON::GetTextDocuments(){
    std::ifstream file;
    file.open(config_path);
    std::string raw = read_open_file(file);
    auto parsedJSON = json::parse(raw);
    auto docsJSON = parsedJSON["files"];
    std::vector <std::string> target;
    for (auto it = docsJSON.begin();it!=docsJSON.end(); it++){
        std::string docDirectory = it.value();
        std::ifstream doc_file(docDirectory);
        if (!doc_file){
            std::cerr << "Resource file is missing: " + docDirectory << std::endl;
            continue;
        }
        std::string raw = read_open_file(doc_file);
        target.push_back(raw);
    }
    return target;
}

int ConverterJSON::GetResponsesLimit(){
    std::ifstream config_file;
    config_file.open(config_path);
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    return parsedJSON["config"]["max_responses"];
}

std::vector <std::string> ConverterJSON::GetRequests(){
    std::ifstream request_file;
    request_file.open(requests_path);
    std::string raw = read_open_file(request_file);
    auto parsedJSON = json::parse(raw);
    auto requestsJSON = parsedJSON["requests"];
    std::vector <std::string> target;
    for (auto it = requestsJSON.begin();it!=requestsJSON.end(); it++){
        target.push_back(it.value());
    }
    return target;
};

void ConverterJSON::putAnswers(std::vector <std::vector<RelativeIndex>> answers){
    json answersJSON = {{"answers", {}}};
    for (int request_id=0;request_id<answers.size();request_id++){
        std::string request_key = "request" + std::to_string(request_id+1);
        json answerEntry = {};
        if (answers[request_id].size()==0)
            answerEntry["result"]="false";
        else {
            answerEntry["result"]="true";
            answerEntry["relevance"] = json::array();
            for (int i=0;i<answers[request_id].size();i++){
                json pair = {};
                pair["docid"] = answers[request_id][i].doc_id;
                pair["rank"] = answers[request_id][i].rank;
                answerEntry["relevance"].insert(answerEntry["relevance"].end(), pair);
            }
        }
        answersJSON[request_key] = answerEntry;
    }
    std::ofstream file(answers_path);
    file << answersJSON.dump(4);
    file.close();
}

std::vector <std::vector<RelativeIndex>> ConverterJSON::to_relative_index(std::vector <std::vector<std::pair<int, float>>> input){
    std::vector <std::vector<RelativeIndex>> result;
    for (int i=0;i<input.size();i++){
        std::vector<RelativeIndex> relevances;
        for (int j=0;j<input[i].size();j++){
            RelativeIndex item;
            item.doc_id = input[i][j].first;
            item.rank = input[i][j].second;
            relevances.push_back(item);
        }
        result.push_back(relevances);
    };
    return result;
}

void ConverterJSON::putAnswers(std::vector <std::vector<std::pair<int, float>>> answers){
    putAnswers(to_relative_index(answers));
};