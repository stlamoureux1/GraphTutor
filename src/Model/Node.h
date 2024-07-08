#pragma once

#include <nlohmann/json.hpp>

using NodeId = unsigned int;

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

template <class T>
class Node {
    public:
        Node() = default;
        Node(NodeId id, T data);
        NodeId GetId() const;
        T GetData() const;
        void SetData(T data);

        template <typename BasicJson>
        friend void to_json(BasicJson& j, const Node<T>& node) {
            j["node"]["id"] = node.GetId();
            j["node"]["data"] = node.GetData();  
        };

        template <typename BasicJson>
        friend void from_json(const BasicJson& j, Node<T>& node) {
            j.at("node").at("id").get_to(node.m_id);
            j.at("node").at("data").get_to(node.m_data);
        };
    private:
        NodeId m_id;
        T m_data;
};

template <class T>
Node<T>::Node(NodeId id, T data) : m_id(id), m_data(data) {}

template <class T>
NodeId Node<T>::GetId() const { 
    return m_id; 
}

template <class T>
T Node<T>::GetData() const { 
    return m_data; 
}

template <class T>
void Node<T>::SetData(T data) {
    this->m_data = data;
    // TBD: Add input validation
}

template <class T>
bool operator==(Node<T> node1, Node<T> node2) {
    return node1.GetId() == node2.GetId() && node1.GetData() == node2.GetData();
}

/*
template <typename BasicJson, class T>
void to_json(BasicJson& j, const Node<T>& node) {
    j["node"]["id"] = node.GetId();
    j["node"]["data"] = node.GetData(); 
}

template <typename BasicJson, class T>
void from_json(const ordered_json& j, Node<T>& node) {
    // NodeId id = j.at("node").at("id");
    // T data = j.at("node").at("data");
    // Node<T> newNode(id, data);
    // node = newNode;
    j.at("node").at("id").get_to(node.m_id);
    j.at("node").at("data").get_to(node.m_data);
}
*/



/*
template <class T>
struct nlohmann::adl_serializer<Node<T>> {
    static Node<T> from_json(const ordered_json& j) {
        return {j.at("node").at("id"), j.at("node").at("data")};
    }

    static void to_json(ordered_json& j, Node<T> node) {
        j["node"]["id"] = node.GetId();
        j["node"]["data"] = node.GetData();
    }
};
*/