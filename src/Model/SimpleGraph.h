#pragma once

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include "Node.h"
#include "Edge.h"


using AdjacencyListEntry = std::pair<NodeId, EdgeId>;
using AdjacencyList = std::map<NodeId, std::vector<AdjacencyListEntry>>;

template <class T>
class SimpleGraph {
    public:
        std::vector<Node<T>> nodeList;
        std::vector<Edge<T>> edgeList;
        AdjacencyList adjacencyList;
        void AddNode(Node<T> node);
        void RemoveNode(NodeId id);
        void AddEdge(Edge<T> edge);
        void RemoveEdge(Edge<T> edge);

        NodeId nodeCounter;
        EdgeId edgeCounter;
    private:

};