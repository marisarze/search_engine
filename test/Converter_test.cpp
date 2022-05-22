//
// Created by marisarze on 4/18/2022.
//
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "gtest/gtest.h"
#include "Converter.h"

using json = nlohmann::json;

class TestCaseConverter: public::testing::Test {
protected:
    int n = 888;
    std::string config_path = "config.json";
    json config_json = json::object({
        {"config", {{"name", "FastestSearchEngine"},
                    {"version", "0.9999"},
                    {"max_responses", 567}}},
        {"files", json::array()}
    });


    void SetUp() override {
        std::filesystem::create_directory("./awesome_resources");
        for (int i=0;i<n;i++){
            std::string name = "awesome_resources/inner_file"+std::to_string(i)+".txt";
            std::fstream file(name, std::ios_base::out);
            if (file.is_open()){
                file << "Five little ducks went out one day\n"
                        "Over the hill and far away..."<<std::endl;
                file << "Order number is "+std::to_string(i);
                file.close();
                config_json["files"].insert(config_json["files"].end(), name);
            } else {
                file.close();
                throw std::runtime_error("Can't create fixture resource file: " + name);
            }
        };

        std::fstream config_file(config_path, std::ios_base::out);
        if (config_file.is_open()){
            config_file << config_json.dump(4);
            config_file.close();
        } else {
            throw std::runtime_error("Can't create fixture config file: ./config.json");
        }
    }

    void TearDown() override {
        if (!std::filesystem::remove_all("./awesome_resources")){
            throw std::runtime_error("Error deleting fixture folder \"awesome_resources\"");
        };
    }
};


TEST_F(TestCaseConverter, TestShowConfigInfo){
    std::string requests_path = "./requests.json";
    std::string answers_path = "./answers.json";
    auto converter = ConverterJSON(config_path, requests_path, answers_path);
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());
    converter.ShowConfigInfo();
    std::string result = buffer.str();
    std::cout.rdbuf(sbuf);
    std::string expected = "search engine name: FastestSearchEngine\n"
            "search engine version: 0.9999\n";
    ASSERT_EQ(result, expected);
};


TEST_F(TestCaseConverter, TestGetResponsesLimit){
    std::string requests_path = "./requests.json";
    std::string answers_path = "./answers.json";
    auto converter = ConverterJSON(config_path, requests_path, answers_path);
    int result = converter.GetResponsesLimit();
    int expected = 567;
    ASSERT_EQ(result, expected);
};


TEST(TestCaseConverterSimple, TestGetRequests){
    std::fstream requests_file("./request.json", std::ios_base::out);
    auto requests_json = json::array();
    requests_json.insert(requests_json.end(), "They came for him one winter's night");
    requests_json.insert(requests_json.end(), "Arrested, he was bound");
    requests_json.insert(requests_json.end(), "They said there\'d been a robbery");
    requests_json.insert(requests_json.end(), "His pistol had been found");
    if (requests_file.is_open()){
        requests_file << requests_json.dump(4);
        requests_file.close();
    } else {
        requests_file.close();
        throw std::runtime_error("Can't create fixture requests file: ./requests.json");
    }
}


