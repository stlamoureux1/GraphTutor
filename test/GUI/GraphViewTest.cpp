#include <gmock/gmock.h>
#include <fstream>
#include "GUI/SimpleGraphView.h"

using ::testing::ElementsAre;
using ::testing::Pair;

TEST(GraphViewTest, IOtest1) {
    // Output test -- no assertions
    std::ofstream outFile("graph.json");
    SimpleGraphView graphView;
    SimpleGraph<int> graph;
    Node<int> node0(0, 0);
    Node<int> node1(1, 1);
    Node<int> node2(2, 2);
    Edge<int> edge0(0, node0, node1);
    Edge<int> edge1(1, node1, node2);
    graph.nodeList = {node0, node1, node2};
    graph.edgeList = {edge0, edge1};
    graphView.graph = graph;
    graphView.nodePositions = {{0, wxPoint(100, 100)}, {1, wxPoint(200, 200)}, {2, wxPoint(300, 300)}};
    json j = graphView;
    if (!outFile) {
        std::cout << "no file\n";
        return; 
    }
    outFile << std::setw(4) << j;
}

TEST(GraphViewTest, IOtest2) {
    std::ifstream inFile("graph.json");
    json j;
    inFile >> j;
    SimpleGraphView graphView = j;
    Node<int> node0(0, 0);
    Node<int> node1(1, 1);
    Node<int> node2(2, 2);
    Edge<int> edge0(0, node0, node1);
    Edge<int> edge1(1, node1, node2);
    ASSERT_THAT(graphView.graph.nodeList, ElementsAre(node0, node1, node2));
    ASSERT_THAT(graphView.graph.edgeList, ElementsAre(edge0, edge1));
    ASSERT_THAT(graphView.nodePositions, ElementsAre(Pair(0, wxPoint(100, 100)), Pair(1, wxPoint(200, 200)), Pair(2, wxPoint(300, 300))));
}
