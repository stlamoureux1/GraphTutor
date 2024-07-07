#include <wx/wx.h>
#include "Model/SimpleGraphImpl.h"
#include "SimpleGraphView.h"


void SimpleGraphView::Draw(wxGraphicsContext* gc) {
    for (Edge edge : graph.edgeList) {
        wxPoint endpoint1 = nodePositions[edge.GetNodeIds().first];
        wxPoint endpoint2 = nodePositions[edge.GetNodeIds().second];
        EdgeView edgeView(endpoint1, endpoint2);
        edgeView.Draw(gc);
    }
    for (Node node : graph.nodeList) {
        NodeView nodeView(nodePositions[node.GetId()], 20.0);
        nodeView.isSelected = selectedNodes[node.GetId()];
        nodeView.Draw(gc);
    }
}

void SimpleGraphView::AddNode(wxPoint pos) {
    NodeId id = ++graph.nodeCounter;
    Node newNode(id, 0);
    graph.AddNode(newNode);
    nodePositions[id] = pos;
}

void SimpleGraphView::RemoveNode(NodeId id) {
    // auto nodeIter = find_if(graph.nodeList.begin(), graph.nodeList.end(), [&](auto& node) { return node.GetId() == id; });
    graph.RemoveNode(id);
    nodePositions.erase(id);
    selectedNodes.erase(id);
}

void SimpleGraphView::MoveNode(NodeId id, wxPoint pos) {
    nodePositions[id] = pos;
}

void SimpleGraphView::AddEdge(NodeId id1, NodeId id2) {
    auto node1Iter = find_if(graph.nodeList.begin(), graph.nodeList.end(), 
                                [&](auto node) { return node.GetId() == id1; });
    auto node2Iter = find_if(graph.nodeList.begin(), graph.nodeList.end(),
                                [&](auto node) { return node.GetId() == id2; });
    if (node1Iter != graph.nodeList.end() && node2Iter != graph.nodeList.end()) {
        Edge newEdge(++graph.edgeCounter, *node1Iter, *node2Iter);
        graph.AddEdge(newEdge);
    }   
}