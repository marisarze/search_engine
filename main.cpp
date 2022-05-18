#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "Converter.h"

#include <iostream>
#include "CLI/CLI.hpp"

int main(int argc, char** argv) {
    CLI::App app{"App description"};

    std::string config_file = "./config.txt";
    app.add_option("--config,-c", config_file, "Configuration file path");

    std::string output_file = "./answers.txt";
    app.add_option("--output,-o", output_file, "Output path for query response file");


    CLI11_PARSE(app, argc, argv);

    ConverterJSON converter(config_file);
    converter.ValidateConfigFile();
    converter.ShowConfigInfo();
    InvertedIndex index;
    index.UpdateDocumentBase(converter.GetTextDocuments());
    return 0;
}
