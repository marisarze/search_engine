#include <iostream>
#include "SearchServer.h"
#include "InvertedIndex.h"
#include "Converter.h"

#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(name, "Tom", "name");
DEFINE_int32(age, 18, "age");

int main(int argc, char** argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::cout << "your name is : " << FLAGS_name
              << ", your age is: " << FLAGS_name << std::endl;
    gflags::ShutDownCommandLineFlags();
    return 0;
}

