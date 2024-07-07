#include <wx/wx.h>
#include "Model/SimpleGraphImpl.h"
#include "SimpleGraphView.h"


void SimpleGraphView::Draw(wxGraphicsContext* gc) {
    for (Node node : graph.nodeList) {
        NodeView nodeView(nodePositions[node.GetId()], 20.0);
        nodeView.isSelected = selectedNodes[node.GetId()];
        nodeView.Draw(gc);
    }
    for (Edge edge : graph.edgeList) {
        wxPoint endpoint1 = nodePositions[edge.GetNodeIds().first];
        wxPoint endpoint2 = nodePositions[edge.GetNodeIds().second];
        EdgeView edgeView(endpoint1, endpoint2);
        edgeView.Draw(gc);
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