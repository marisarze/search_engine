#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <string>
#include "Converter.h"


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

void ConverterJSON::CheckConfigValidity(){
    std::ifstream config_file;
    config_file.open(folder+"/config.json");
    if (!config_file){
        throw "Config file is missing";
    }
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    if(parsedJSON.count("config")==0){
        throw "Config file is empty";
    }
    config_file.close();
}

ConverterJSON::ConverterJSON(std::string inFolder): folder(inFolder){};

void ConverterJSON::ShowConfigInfo(){
    std::ifstream config_file;
    config_file.open(folder+"/config.json");
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    auto config_part = parsedJSON["config"];
    std::string info = "";
    if (config_part.count("name")){
        info += "search engine name: " + config_part["name"] + '\n';
    }
    if (config_part.count("version")){
        info += "search engine version: " + config_part["version"] + '\n';
    }
    std::cout << info;
};

std::vector <std::string> ConverterJSON::GetTextDocuments(){
    std::ifstream file;
    file.open(folder+"/config.json");
    if (!file){
        throw "Config file is missing";
    }
    std::string raw = read_open_file(file);
    auto parsedJSON = json::parse(raw);
    auto docsJSON = parsedJSON["files"];
    std::vector <std::string> target;
    for (auto it = docsJSON.begin();it!=docsJSON.end(); it++){
        std::string docDirectory = it.value();
        std::ifstream doc_file(docDirectory);
        if (!doc_file){
            std::cerr << "Resource file is missing: " + docDirectory << std::endl;
        }
        std::string raw = read_open_file(doc_file);
        target.push_back(raw);
    }
    return target;
}

int ConverterJSON::GetResponsesLimit(){
    std::ifstream config_file;
    config_file.open(folder+"/config.json");
    std::string raw = read_open_file(config_file);
    auto parsedJSON = json::parse(raw);
    return parsedJSON["config"]["max_responses"];
}

std::vector <std::string> ConverterJSON::GetRequests(){
    std::ifstream request_file;
    request_file.open(folder+"/config.json");
    std::string raw = read_open_file(request_file);
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