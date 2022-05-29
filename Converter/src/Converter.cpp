#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <string>
#include <stdexcept>
#include "Converter.h"
#include "SearchServer.h"

using json = nlohmann::json;

ConverterJSON::ConverterJSON(){};


ConverterJSON::ConverterJSON(std::string in_config_path):
        config_path(in_config_path){};


ConverterJSON::ConverterJSON(std::string in_config_path, std::string in_requests_path):
        config_path(in_config_path),requests_path(in_requests_path){};


ConverterJSON::ConverterJSON(std::string in_config_path, std::string in_requests_path, std::string in_answers_path):
    config_path(in_config_path),requests_path(in_requests_path),answers_path(in_answers_path){};


void ConverterJSON::set_config_path(std::string in_config_path){
    config_path = in_config_path;
};


std::string ConverterJSON::get_config_path(){
    return config_path;
};

void ConverterJSON::set_requests_path(std::string in_requests_path){
    requests_path = in_requests_path;
};


std::string ConverterJSON::get_requests_path(){
    return requests_path;
};


void ConverterJSON::set_answers_path(std::string in_answers_path){
    answers_path = in_answers_path;
};


std::string ConverterJSON::get_answers_path(){
    return answers_path;
};


std::string ConverterJSON::read_open_file(std::ifstream &file){
    file.seekg(0, std::ios::beg);
    std::string raw;
    while(true){
        char temp = file.get();
        if (file.eof()) break;
        raw += temp;
    }
    return raw;
};


void ConverterJSON::validate_config_file(std::string valid_project_version){
    std::ifstream config_file(config_path);
    json parsedJSON;
    if (!config_file.is_open()){
        std::string error_message = "Config file with path " + config_path + " is missing.";
        throw std::runtime_error(error_message);
    } else {
        parsedJSON = json::parse(config_file);
        config_file.close();
    }
    if(parsedJSON.count("config")==0){
        throw std::runtime_error("Config file is empty.");
    }
    if(parsedJSON["config"].count("version")==0){
        throw std::runtime_error("Config file should contain version.");
    }
    if(parsedJSON["config"]["version"]!=valid_project_version){
        throw std::runtime_error("Config file has incorrect version.");
    }
}


void ConverterJSON::show_config_info(){
    std::ifstream config_file(config_path);
    json parsedJSON = json::parse(config_file);
    config_file.close();
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


std::vector <std::string> ConverterJSON::get_text_documents(){
    std::ifstream config_file(config_path);
    json parsedJSON = json::parse(config_file);
    config_file.close();
    auto docsJSON = parsedJSON["files"];
    std::vector <std::string> target;
    for (auto it = docsJSON.begin();it!=docsJSON.end(); it++){
        std::string docDirectory = it.value();
        std::ifstream doc_file(docDirectory);
        if (!doc_file){
            std::cerr << "Resource file is missing: " + docDirectory << std::endl;
            continue;
        }
        std::string content = read_open_file(doc_file);
        target.push_back(content);
    }
    return target;
}


int ConverterJSON::get_responses_limit(){
    std::ifstream config_file(config_path);
    json parsedJSON = json::parse(config_file);
    config_file.close();
    return parsedJSON["config"]["max_responses"];
}


std::vector <std::string> ConverterJSON::get_requests(){
    std::ifstream requests_file(requests_path);
    json parsedJSON = json::parse(requests_file);
    requests_file.close();
    auto requestsJSON = parsedJSON["requests"];
    std::vector <std::string> target;
    for (auto it = requestsJSON.begin();it!=requestsJSON.end(); it++){
        target.push_back(it.value());
    }
    return target;
};


void ConverterJSON::put_answers(std::vector <std::vector<RelativeIndex>> answers){
    json answersJSON = {{"answers", {}}};
    for (int request_id=0;request_id<answers.size();request_id++) {
        std::string prefix;
        if (request_id <99 && request_id>8)
            prefix = "request0";
        else if (request_id<=8)
            prefix = "request00";
        else
            prefix = "request00";
        std::string request_key = prefix + std::to_string(request_id + 1);
        json answerEntry = {};
        if (answers[request_id].size() == 0)
            answerEntry["result"] = "false";
        else if (answers[request_id].size() == 1) {
            answerEntry["result"] = "true";
            answerEntry["docid"] = answers[request_id][0].doc_id;
            answerEntry["rank"] = answers[request_id][0].rank;
        } else {
            answerEntry["result"]="true";
            answerEntry["relevance"] = json::array();
            for (int i=0;i<answers[request_id].size();i++){
                json pair = {};
                pair["docid"] = answers[request_id][i].doc_id;
                pair["rank"] = answers[request_id][i].rank;
                answerEntry["relevance"].insert(answerEntry["relevance"].end(), pair);
            }
        }
        answersJSON["answers"][request_key] = answerEntry;
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


void ConverterJSON::put_answers(std::vector <std::vector<std::pair<int, float>>> answers){
    put_answers(to_relative_index(answers));
};