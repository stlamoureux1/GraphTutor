#pragma once
#include "Node.h"

using EdgeId = unsigned int;

template <class T>
class Edge {
    public:
        Edge(EdgeId id, Node<T> node1, Node<T> node2);
        EdgeId GetId();
        std::pair<NodeId, NodeId> GetNodeIds();
    private:
        EdgeId m_id;
        NodeId m_node1Id;
        NodeId m_node2Id;
};

template <class T>
Edge<T>::Edge(EdgeId id, Node<T> node1, Node<T> node2)
    : m_id(id), m_node1Id(node1.GetId()), m_node2Id(node2.GetId()) {}

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