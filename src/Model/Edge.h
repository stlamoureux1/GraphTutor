#pragma once
#include "Node.h"
#include "nlohmann/json.hpp"


using EdgeId = unsigned int;
using ordered_json = nlohmann::ordered_json;

template <class T>
class Edge {
    public:
        Edge() = default;
        Edge(EdgeId id, Node<T> node1, Node<T> node2);
        EdgeId GetId() const;
        std::pair<NodeId, NodeId> GetNodeIds() const;

        template <typename BasicJson>
        friend void to_json(BasicJson& j, const Edge<T>& edge) {
            j["edge"]["id"] = edge.GetId();
            j["edge"]["node1Id"] = edge.GetNodeIds().first;
            j["edge"]["node2Id"] = edge.GetNodeIds().second;
        };

        template <typename BasicJson>
        friend void from_json(const BasicJson& j, Edge<T>& edge) {
            j.at("edge").at("id").get_to(edge.m_id);
            j.at("edge").at("node1Id").get_to(edge.m_node1Id);
            j.at("edge").at("node2Id").get_to(edge.m_node2Id);
        };
    private:
        EdgeId m_id;
        NodeId m_node1Id;
        NodeId m_node2Id;
};

template <class T>
Edge<T>::Edge(EdgeId id, Node<T> node1, Node<T> node2)
    : m_id(id), m_node1Id(node1.GetId()), m_node2Id(node2.GetId()) {}

template <class T>
EdgeId Edge<T>::GetId() const {
    return m_id;
}

template <class T>
std::pair<NodeId, NodeId> Edge<T>::GetNodeIds() const {
    return { m_node1Id, m_node2Id };
}

template <class T>
bool operator==(Edge<T> edge1, Edge<T> edge2) {
    return edge1.GetId() == edge2.GetId()
            && edge2.GetNodeIds() == edge2.GetNodeIds();
}

