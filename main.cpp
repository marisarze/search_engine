#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "Converter.h"

#include <iostream>
#include "CLI/CLI.hpp"
#include "cmake_var_parsing_in.h"

int main(int argc, char** argv) {
    try {
        CLI::App app{"App description"};

        std::string config_path = "./config.json";
        app.add_option("--config,-c", config_path, "Configuration file path");

        std::string request_path = "./requests.json";
        app.add_option("--request,-r", request_path, "Path for request file");

        std::string output_path = "./answers.json";
        app.add_option("--output,-o", output_path, "Output path for query response file");
        bool version_flag=false;
        app.add_flag("--version,-v", version_flag, "Show a version of the application");
        CLI11_PARSE(app, argc, argv);
        if (version_flag){
            std::cout << "The app version: " << PROJECT_VER << std::endl;
        } else {
            ConverterJSON converter(config_path, request_path, output_path);
            converter.validate_config_file(PROJECT_VER);
            converter.show_config_info();
            InvertedIndex index;
            index.update_document_base(converter.get_text_documents());
            SearchServer server(index);
            auto answers = server.search(converter.get_requests(), converter.get_responses_limit());
            converter.put_answers(answers);
            return 0;
        }
    }
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what();
        return 1;
    }

}
