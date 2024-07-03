#pragma once

using NodeId = unsigned int;

template <class T>
class Node {
    public:
        Node(NodeId id, T data);
        NodeId GetId();
        T GetData();
        void SetData(T data);
    private:
        NodeId m_id;
        T m_data;
};

template <class T>
Node<T>::Node(NodeId id, T data) : m_id(id), m_data(data) {}

template <class T>
NodeId Node<T>::GetId() { return m_id; }

template <class T>
T Node<T>::GetData() { return m_data; }

template <class T>
void Node<T>::SetData(T data) {
    m_data = data;
    // TBD: Add input validation
}

template <class T>
bool operator==(Node<T> node1, Node<T> node2) {
    return node1.GetId() == node2.GetId() && node1.GetData() == node2.GetData();
}