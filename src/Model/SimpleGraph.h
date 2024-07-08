#pragma once

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "Node.h"
#include "Edge.h"


using AdjacencyListEntry = std::pair<NodeId, EdgeId>;
using AdjacencyList = std::map<NodeId, std::vector<AdjacencyListEntry>>;
using json = nlohmann::json;

template <class T>
class SimpleGraph {
    public:
        SimpleGraph() = default;
        std::vector<Node<T>> nodeList;
        std::vector<Edge<T>> edgeList;
        AdjacencyList adjacencyList;
        void AddNode(Node<T> node);
        void RemoveNode(NodeId id);
        void AddEdge(Edge<T> edge);
        void RemoveEdge(Edge<T> edge);

        template <typename BasicJson>
        friend void to_json(BasicJson& j, const SimpleGraph<T>& graph) {
            j["nodeList"] = graph.nodeList;
            j["edgeList"] = graph.edgeList;
        };

        template <typename BasicJson>
        friend void from_json(const BasicJson& j, SimpleGraph<T>& graph) {
            j.at("nodeList").get_to(graph.nodeList);
            j.at("edgeList").get_to(graph.edgeList);
        };

        NodeId nodeCounter;
        EdgeId edgeCounter;
    private:

};