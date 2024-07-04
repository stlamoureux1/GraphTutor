#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Model/SimpleGraphImpl.h"

using ::testing::Pair;

TEST(SimpleGraphTest, test1) {
    SimpleGraph<int> graph;
    Node<int> node1(0, 0);
    Node<int> node2(1, 1);
    Edge<int> edge1(0, node1, node2);
    graph.AddEdge(edge1);
    ASSERT_THAT(graph.adjacencyList[node1.GetId()][0], Pair(node2.GetId(), edge1.GetId()));
}

TEST(SimpleGraphTest, test2) {
    SimpleGraph<std::string> graph;
    Node<std::string> node1(0, "a");
    Node<std::string> node2(1, "b");
    Node<std::string> node3(2, "c");
    Node<std::string> node4(3, "d");
    Edge<std::string> edge1(1, node1, node2);
    Edge<std::string> edge2(2, node1, node3);
    Edge<std::string> edge3(3, node3, node4);
    Edge<std::string> edge4(4, node2, node3);
    graph.AddEdge(edge1);
    graph.AddEdge(edge2);
    graph.AddEdge(edge3);
    graph.AddEdge(edge4);
    graph.RemoveNode(node1);
    auto it = std::find_if(graph.edgeList.begin(), graph.edgeList.end(), 
                [&](auto& edge){
                    return edge.GetNodeIds().first == node1.GetId() || edge.GetNodeIds().second == node1.GetId();
                });
    ASSERT_EQ(it, graph.edgeList.end());
}