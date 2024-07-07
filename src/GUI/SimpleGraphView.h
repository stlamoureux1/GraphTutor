#pragma once

#include <map>
#include <set>
#include <wx/wx.h>
#include "NodeView.h"
#include "EdgeView.h"
#include "Model/SimpleGraph.h"

class SimpleGraphView {
    public:
        // SimpleGraphView();
        void Draw(wxGraphicsContext* gc);
        void AddNode(wxPoint pos);
        void RemoveNode(NodeId id);
        void MoveNode(NodeId id, wxPoint pos);
        void AddEdge(NodeId id1, NodeId id2);
        SimpleGraph<int> graph;
        std::map<NodeId, wxPoint> nodePositions;
        std::map<NodeId, bool> selectedNodes; 
        wxPoint dragOrigin;
        std::optional<NodeId> newEdgeNode1Id;
        std::optional<NodeId> newEdgeNode2Id;
    private:

};
