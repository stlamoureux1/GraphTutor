#include "SimpleGraph.h"

template <class T>
void SimpleGraph<T>::AddNode(Node<T> node) {
    // Check if there is already a node using this node's id.
    auto nodeIter = find_if( nodeList.begin(), 
                             nodeList.end(), 
                             [&](Node<T> otherNode){ return otherNode.GetId() == node.GetId(); }
                            );
    // If not, add it to node list.
    if (nodeIter == nodeList.end()) {
        nodeList.push_back(node);
    }

    // Update adjacency list
    adjacencyList[node.GetId()] = {};

}

template <class T>
void SimpleGraph<T>::RemoveNode(Node<T> node) {
    // Remove this node from nodeList
    auto nodeIter = find_if(nodeList.begin(),
                            nodeList.end(),
                            [&](Node<T> otherNode) { 
                                return otherNode.GetId() == node.GetId();
                            }    
                        );
    if (nodeIter != nodeList.end()) {
        nodeList.erase(nodeIter);
    }

    // Remove from edgeList all edges containing this node
    auto edgeIter = remove_if(edgeList.begin(),
                                edgeList.end(),
                                [&](Edge<T>& otherEdge) {
                                    return otherEdge.GetNodeIds().first == node.GetId()
                                            || otherEdge.GetNodeIds().second == node.GetId();
                                }
                            );
    edgeList.erase(edgeIter, edgeList.end());

    // Update adjacency list
    auto idIter = adjacencyList.find(node.GetId());
    if (idIter != adjacencyList.end()) {
        adjacencyList.erase(idIter);
    }
    for (auto& [key, val] : adjacencyList) {
        auto entryIter = remove_if(val.begin(),
                                    val.end(),
                                    [&](auto& entry) { 
                                        return entry.first == node.GetId(); 
                                    }
                                );
        val.erase(entryIter, val.end());
        
    }
}

template <class T>
void SimpleGraph<T>::AddEdge(Edge<T> edge) {
    auto edgeIter = find_if(edgeList.begin(),
                            edgeList.end(),
                            [&](Edge<T>& otherEdge) {
                                return otherEdge.GetId() == edge.GetId();
                            }
                        );
    if (edgeIter == edgeList.end()) {
        edgeList.push_back(edge);
    
        adjacencyList[edge.GetNodeIds().first].push_back(
                std::make_pair<NodeId, EdgeId>(edge.GetNodeIds().second, edge.GetId())
            );
        adjacencyList[edge.GetNodeIds().second].push_back(
                std::make_pair<NodeId, EdgeId>(edge.GetNodeIds().first, edge.GetId())
            );
    }
}

template <class T>
void SimpleGraph<T>::RemoveEdge(Edge<T> edge) {
    // Remove edge from edgeList
    auto edgeIter = find_if(edgeList.begin(), 
                        edgeList.end(), 
                        [&](Edge<T>& otherEdge) {
                            return otherEdge.GetId() == edge.GetId();
                        }
                        );
    if (edgeIter != edgeList.end()) {
        edgeList.erase(edgeIter);
    }

    // Update adjacencyList
    for (auto& vec : adjacencyList) {
        for (auto iter = vec.begin(); iter != vec.end(); iter++) {
            if (iter->second == edge.GetId()) {
                vec.erase(iter);
            }
        }
    }
}