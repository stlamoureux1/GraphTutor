#pragma once

#include <map>
#include <set>
#include <wx/wx.h>
#include <nlohmann/json.hpp>
#include "NodeView.h"
#include "EdgeView.h"
#include "Model/SimpleGraph.h"


template <typename BasicJson>
void to_json(BasicJson& j, const wxPoint& point) {
    j["point"]["x"] = point.x;
    j["point"]["y"] = point.y;
}

template <typename BasicJson>
void from_json(const BasicJson& j, wxPoint& point) {
    j.at("point").at("x").get_to(point.x);
    j.at("point").at("y").get_to(point.y);
}

class SimpleGraphView {
    public:
        SimpleGraphView() = default;
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

        template <typename BasicJson>
        friend void to_json(const BasicJson& j, std::map<NodeId, wxPoint>& nodePositions) {
            for (auto [i, val] : nodePositions) {
                json i_json = i;
                json val_json = val;
                j[i_json] = val_json;
            }
        }

        template <typename BasicJson>
        friend void from_json(BasicJson& j, const std::map<NodeId, wxPoint>& m) {

        }

        template <typename BasicJson>
        friend void to_json(BasicJson& j, const SimpleGraphView& graphView) {
            j["nodePositions"] = graphView.nodePositions;
            j["graph"] = graphView.graph;
        };

        template <typename BasicJson>
        friend void from_json(const BasicJson& j, SimpleGraphView& graphView) {
            j.at("nodePositions").get_to(graphView.nodePositions);
            j.at("graph").get_to(graphView.graph);
        };
    private:

};
