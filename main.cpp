#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "Converter.h"
int main() {
    auto ii = InvertedIndex();
    auto ss = SearchServer(ii);
    auto conv = ConverterJSON("");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
