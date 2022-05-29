#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "Converter.h"

#include <iostream>
#include "CLI/CLI.hpp"

int main(int argc, char** argv) {
    try {
        CLI::App app{"App description"};

        std::string config_path = "./config.json";
        app.add_option("--config,-c", config_path, "Configuration file path");

        std::string request_path = "./requests.json";
        app.add_option("--request,-r", request_path, "Path for request file");

        std::string output_path = "./answers.json";
        app.add_option("--output,-o", output_path, "Output path for query response file");


        CLI11_PARSE(app, argc, argv);


        ConverterJSON converter(config_path, request_path, output_path);
        converter.ValidateConfigFile();
        converter.ShowConfigInfo();
        InvertedIndex index;
        index.UpdateDocumentBase(converter.GetTextDocuments());
        SearchServer server(index);
        auto answers = server.search(converter.GetRequests(), converter.GetResponsesLimit());
        converter.putAnswers(answers);
        return 0;
    }
    catch (const std::exception& e){
        std::cerr << e.what();
        return 1;
    }

}
