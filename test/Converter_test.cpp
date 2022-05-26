//
// Created by marisarze on 4/18/2022.
//
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "gtest/gtest.h"
#include "Converter.h"
#include "InvertedIndex.h"

using json = nlohmann::json;

class TestCaseConverter: public::testing::Test {
protected:
    int n = 17;
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
                        "Over the hill and far away...\n";
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

TEST_F(TestCaseConverter, TestGetTextDocuments){
    std::string requests_path = "./requests.json";
    std::string answers_path = "./answers.json";
    auto converter = ConverterJSON(config_path);
    std::vector <std::string> result = converter.GetTextDocuments();
    ASSERT_EQ(result.size(), 17);
    ASSERT_EQ(result[16], "Five little ducks went out one day\n"
                           "Over the hill and far away...\n"
                           "Order number is 16");
};


TEST(TestCaseConverterSimple, TestGetRequests){
    std::string config_path = "./config.json";
    std::string requests_path = "./requests.json";
    std::string answers_path = "./answers.json";
    std::fstream requests_file(requests_path, std::ios_base::out);
    auto requests_json = json::object({{"requests", json::array()}});
    std::vector <std::string> expected = {"They came for him one winter's night",
                                        "Arrested, he was bound",
                                        "They said there\'d been a robbery",
                                        "His pistol had been found"};
    for (auto &elem : expected){
        requests_json["requests"].insert(requests_json["requests"].end(), elem);
    }

    if (requests_file.is_open()){
        requests_file << requests_json.dump(4);
        requests_file.close();
    } else {
        requests_file.close();
        throw std::runtime_error("Can't create fixture requests file: ./requests.json");
    }
    auto converter = ConverterJSON(config_path, requests_path, answers_path);
    auto result = converter.GetRequests();
    if (!std::filesystem::remove_all("./requests.json")){
        throw std::runtime_error("Error deleting fixture folder \"requests.json\"");
    }
    ASSERT_EQ(result, expected);
}


TEST(TestCaseConverterSimple, TestPutAnswersPairs){
    std::vector <std::vector <std::pair <int, float>>> input({{
        std::pair <int, float>({2,0.989}),
        std::pair <int, float>({1,0.897}),
        std::pair <int, float>({0,0.750}),
        std::pair <int, float>({3,0.670}),
        std::pair <int, float>({4,0.561})},{
        std::pair <int, float>({10,0.769})
    },{}});

    nlohmann::basic_json <
            std::map,
            std::vector,
            std::string,
            bool,
            std::int64_t,
            std::uint64_t,
            float,
            std::allocator,
            nlohmann::adl_serializer,
            std::vector<std::uint8_t>>
        expected({{
        "answers", {
            {"request001",{
                {"result", "true"},
                {"relevance", json::array({
                      {{"docid", 2}, {"rank", (json::number_float_t)0.989}},
                      {{"docid", 1}, {"rank", (json::number_float_t)0.897}},
                      {{"docid", 0}, {"rank", (json::number_float_t)0.750}},
                      {{"docid", 3}, {"rank", (json::number_float_t)0.670}},
                      {{"docid", 4}, {"rank", (json::number_float_t)0.561}}
                      })
                }}
            },
            {"request002",{
                {"result", "true"},
                {"docid", 10},
                {"rank", (json::number_float_t)0.769}}
            },
            {"request003",{
                {"result", "false"}
            }}
            }
        }});

    std::string config_path = "./config.json";
    std::string requests_path = "./requests.json";
    std::string answers_path = "./answers.json";
    ConverterJSON converter(config_path, requests_path, answers_path);
    converter.putAnswers(input);
    std::fstream answers_file(answers_path, std::ios_base::in);
    nlohmann::basic_json <
            std::map,
            std::vector,
            std::string,
            bool,
            std::int64_t,
            std::uint64_t,
            float,
            std::allocator,
            nlohmann::adl_serializer,
            std::vector<std::uint8_t>> result;
    if (answers_file.is_open()){
        result = json::parse(answers_file);
        answers_file.close();
    } else {
        answers_file.close();
        throw std::runtime_error("Can't open answers file: ./answers.json");
    }
    if (!std::filesystem::remove_all("./answers.json")){
        throw std::runtime_error("Error deleting \"answers.json\"");
    }
    ASSERT_EQ(expected, result);
}





