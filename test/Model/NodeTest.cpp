#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "Model/Node.h"


TEST(NodeTest, test1) {
    Node<int> node1(325, 18);
    node1.SetData(40);
    ASSERT_EQ(node1.GetData(), 40);
}

TEST(NodeTest, test2) {
    Node<std::string> node1(0, "zero");
    node1.SetData("one");
    ASSERT_EQ(node1.GetData(), "one");    
}

TEST(NodeTest, test3) {
    std::vector<int> vec2{4, 5, 6};
    Node<std::vector<int>> node1(0, {1, 2, 3});
    node1.SetData({4, 5, 6});
    ASSERT_EQ(node1.GetData(), vec2);
}

TEST(NodeTest, test4) {
    std::vector<int> vec1{1, 2, 3};
    std::vector<int> vec2{1, 2, 3};
    Node<std::vector<int>*> node1(0, &vec1);
    ASSERT_NE(node1.GetData(), &vec2);
}