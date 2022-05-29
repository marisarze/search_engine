#include <vector>
#include "SearchServer.h"
#include "gtest/gtest.h"
#include "InvertedIndex.h"

TEST(TestCaseSearchServerSimple, TestSimple) {
const std::vector<std::string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "Americano Cappuccino"
};

const std::vector<std::string> request = {"milk water", "sugar"};
const std::vector<std::vector<RelativeIndex>> expected = {
        {
                {2, 1},
                {0, 0.7},
                {1, 0.3}
        },
        {
        }
};

InvertedIndex idx;
idx.update_document_base(docs);

SearchServer srv(idx);

std::vector<std::vector<RelativeIndex>> result = srv.search(request);

ASSERT_EQ(result, expected);
}

class TestCaseSearchServer: public::testing::Test {
protected:
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };

    InvertedIndex idx;
    SearchServer srv = SearchServer(idx);
    void SetUp() override {
        idx.update_document_base(docs);
    }
};

TEST_F(TestCaseSearchServer, TestTop5) {

    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, (float)4/(float)6},
                    {1, (float)4/(float)6},
                    {2, (float)4/(float)6}
            }
    };

    std::vector<std::vector<RelativeIndex>> result = srv.search(request, 5);

    ASSERT_EQ(result, expected);
}


TEST_F(TestCaseSearchServer, TestRepeatedWordsDontMatter) {

    const std::vector<std::string> request_one = {"moscow is the capital of russia"};
    const std::vector<std::string> request_two = {"moscow moscow is the capital of russia"};

    std::vector<std::vector<RelativeIndex>> result_one = srv.search(request_one);
    std::vector<std::vector<RelativeIndex>> result_two = srv.search(request_two);
    ASSERT_EQ(result_one, result_two);
}