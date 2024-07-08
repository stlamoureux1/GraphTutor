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
    json j = edge1.ToJSON();
    ASSERT_EQ(j["id"], 0);
    ASSERT_EQ(j["node1_id"], 0);
    ASSERT_EQ(j["node2_id"], 1);
}

TEST(EdgeTest, IOtest2) {
    json j;
    j["id"] = 0;
    j["node1_id"] = 0;
    j["node2_id"] = 1;
    Edge<int> edge(j);
    ASSERT_EQ(edge.GetId(), 0);
    ASSERT_THAT(edge.GetNodeIds(), Pair(0, 1));
}