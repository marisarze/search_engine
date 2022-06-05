//
// Created by marisarze on 4/7/2022.
//

#ifndef SEARCH_PROJECT_CONVERTER_H
#define SEARCH_PROJECT_CONVERTER_H

#include <vector>
#include <iostream>
#include <fstream>
#include "SearchServer.h"

/**
 * Class responsible for reading and writing json objects to/from files
 */
class ConverterJSON {
private:
    // configuration file path
    std::string config_path;

    // requests file path
    std::string requests_path;

    // answers file path
    std::string answers_path;

    /**
     * method for reading text files
     * @param file object for reading
     * @return file contents
     */
    std::string read_open_file(std::ifstream &file);

    /**
     * method-converter of a  std::pair<int, float>
     * response vector into the <RelativeIndex> format
     * @param input answer vector required for conversion
     * @return answer vector of <RelativeIndex>
     */
    std::vector <std::vector<RelativeIndex>> to_relative_index(std::vector <std::vector<std::pair<int, float>>> input);

public:
    // ConverterJSON class constructor
    ConverterJSON();

    /**
     *ConverterJSON class constructor
     * @param in_config_path value for setting config_path
     */
    ConverterJSON(std::string in_config_path);

    /**
     *ConverterJSON class constructor
     * @param in_config_path value for setting config_path
     * @param in_requests_path value for setting requests_path
     */
    ConverterJSON(std::string in_config_path,
                  std::string in_requests_path);

    /**
     *ConverterJSON class constructors setting
     * @param in_config_path value for setting config_path
     * @param in_requests_path value for setting requests_path
     * @param in_answers_path value for setting answers_path
     */
    ConverterJSON(std::string in_config_path,
                  std::string in_requests_path,
                  std::string in_answers_path);

    /**
     * config_path value setter
     * @param in_config_path value for setting config_path
     */
    void set_config_path(std::string in_config_path);

    /**
     * config_path value getter
     * @return config_path value
    */
    std::string get_config_path();

    /**
     * requests_path value setter
     * @param in_config_path value for setting requests_path
    */
    void set_requests_path(std::string in_requests_path);

    /**
     * requests_path value getter
     * @return requests_path value
    */
    std::string get_requests_path();

    /**
     * answers_path value setter
     * @param in_config_path value for setting answers_path
    */
    void set_answers_path(std::string in_answers_path);

    /**
     * answers_path value getter
     * @return answers_path value
    */
    std::string get_answers_path();

    /**
     * Method for getting the contents of indexed files
     * specified in the configuration file
     * @return file content vector
     */
    std::vector<std::string> get_text_documents();

    /**
     * Method for getting the value of the maximum
     * number of responses for each request
     * specified in the configuration file
     * @return answer limit
     */
    int get_responses_limit();

    /**
     * Method for getting requests from request file
     * @return vector of text requests
     */
    std::vector<std::string> get_requests();

    /**
     * Method for writing answers to a file
     * @param vector of answers in format <RelativeIndex>
     */
    void put_answers(std::vector<std::vector<RelativeIndex>> answers);

    /**
     * Method for writing answers to a file
     * @param vector of answers in format std::pair<int, float>
     */
    void put_answers(std::vector<std::vector<std::pair<int, float>>> answers);

    /**
     * Method for showing information from config file:
     * config name, engine version
     */
    void show_config_info();

    /**
     * Method Method for checking the correctness of
     * the contents of the configuration file. Throws an error
     * if the fields "version", "config" are missing.
     * The value of the "version" field must match the version of the program.
     */
    void validate_config_file(std::string valid_project_version);
};


#endif //SEARCH_PROJECT_CONVERTER_H


