#include "Gistogramma.h"
#include <gtest\gtest.h>
#include <iostream>
#include <sstream>
using namespace std;

TEST(testcase1, test1) {
    string str = "ball 1 table green 34 34 money 3,8 66 1 1 1 green 34 34 money 3,8 66";
    istringstream ist(str);
    Gistogramma gist_flow(ist);
    vector<string> values = { "ball", "1", "table", "green", "34", "34", "money", "3,8", "66", "1", "1", "1", "green", "34", "34", "money", "3,8", "66" };
    Gistogramma gist_vector(values);
    Gistogramma gist_flow_copy(gist_flow);
    ASSERT_TRUE(gist_flow == gist_flow_copy);
    ASSERT_TRUE(gist_flow == gist_vector);
}

TEST(testcase2, test2) {
    string str = "ball 1 table green 34 34 money 3,8 66 1 1 1 green 34 34 money 3,8 66";
    istringstream ist(str);
    Gistogramma gist_flow(ist);
    vector<string> values = { "ball", "1", "table", "green", "34", "34", "money", "3,8", "66", "1", "1", "1", "green", "34", "34", "money", "3,8", "66", "ball", "1", "table", "green", "34", "34", "money", "3,8", "66", "1", "1", "1", "green", "34", "34", "money", "3,8", "66" };
    Gistogramma gist_vector(values);
    gist_flow = gist_flow + gist_flow;
    ASSERT_TRUE(gist_flow == gist_vector);
}

TEST(testcase3, test3) {
    string str = "ball 1 table green 34 34 money 3,8 66 1 1 1 green 34 34 money 3,8 66";
    istringstream ist(str);
    Gistogramma gist_flow(ist);
    vector<string> values = { "ball", "1", "table", "green", "34", "34", "money", "3,8", "66", "1", "1", "1", "green", "34", "34", "money", "3,8", "66", "ball", "1", "table", "green", "34", "34", "money", "3,8", "66", "1", "1", "1", "green", "34", "34", "money", "3,8", "66" };
    Gistogramma gist_vector(values);
    gist_vector = gist_vector - gist_flow;
    ASSERT_TRUE(gist_flow == gist_vector);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
