#pragma once
#include "Node.h"
#include "nlohmann/json.hpp"


using EdgeId = unsigned int;
using json = nlohmann::json;

template <class T>
class Edge {
    public:
        Edge(EdgeId id, Node<T> node1, Node<T> node2);
        Edge(json j);
        EdgeId GetId();
        std::pair<NodeId, NodeId> GetNodeIds();
        json ToJSON();
    private:
        EdgeId m_id;
        NodeId m_node1Id;
        NodeId m_node2Id;
};

template <class T>
Edge<T>::Edge(EdgeId id, Node<T> node1, Node<T> node2)
    : m_id(id), m_node1Id(node1.GetId()), m_node2Id(node2.GetId()) {}

template <class T>
Edge<T>::Edge(json j) : m_id(j["id"]), m_node1Id(j["node1_id"]), m_node2Id(j["node2_id"]) {}

template <class T>
EdgeId Edge<T>::GetId() {
    return m_id;
}

template <class T>
std::pair<NodeId, NodeId> Edge<T>::GetNodeIds() {
    return { m_node1Id, m_node2Id };
}

template <class T>
bool operator==(Edge<T> edge1, Edge<T> edge2) {
    return edge1.GetId() == edge2.GetId()
            && edge2.GetNodeIds() == edge2.GetNodeIds();
}

template <class T>
json Edge<T>::ToJSON() {
    json j;
    j["id"] = GetId();
    j["node1_id"] = m_node1Id;
    j["node2_id"] = m_node2Id; 
    return j;
}