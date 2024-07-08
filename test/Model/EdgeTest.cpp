#include <gmock/gmock.h>
#include "Model/Edge.h"

using ::testing::Pair;

TEST(EdgeTest, test1) {
    Node<int> node1(0, 0);
    Node<int> node2(1, 1);
    Edge<int> edge(0, node1, node2);
    ASSERT_THAT(edge.GetNodeIds(), Pair(node1.GetId(), node2.GetId()));
}

TEST(EdgeTest, test2) {
    Node<int> node1(0, 0);
    Node<int> node2(1, 1);
    Edge<int> edge1(0, node1, node2);
    Edge<int> edge2(0, node1, node2);
    ASSERT_EQ(edge1, edge2);
}


TEST(EdgeTest, IOtest1) {
    Node<int> node1(0, 0);
    Node<int> node2(1, 1);
    Edge<int> edge1(0, node1, node2);
    ordered_json j = edge1;
    ASSERT_EQ(j["edge"]["id"], 0);
    ASSERT_EQ(j["edge"]["node1Id"], 0);
    ASSERT_EQ(j["edge"]["node2Id"], 1);
}

TEST(EdgeTest, IOtest2) {
    ordered_json j;
    j["edge"]["id"] = 0;
    j["edge"]["node1Id"] = 0;
    j["edge"]["node2Id"] = 1;
    auto edge = j.template get<Edge<int>>(); 
    ASSERT_EQ(edge.GetId(), 0);
    ASSERT_THAT(edge.GetNodeIds(), Pair(0, 1));
}
