#include "DrawingPane.h"

DrawingPane::DrawingPane(wxFrame* parent, wxWindowID id) 
    : wxWindow(parent, id) {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_LEFT_DOWN, &DrawingPane::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &DrawingPane::OnMouseLeftUp, this);
        Bind(wxEVT_LEFT_DCLICK, &DrawingPane::OnDoubleClick, this);
        Bind(wxEVT_MOTION, &DrawingPane::OnMouseLeftDrag, this);
        Bind(wxEVT_PAINT, &DrawingPane::OnPaint, this);
}

void DrawingPane::OnMouseLeftDown(wxMouseEvent& event) {
    graphView.dragOrigin = event.GetPosition();
    if (!event.ShiftDown()) {
        for (auto node : graphView.graph.nodeList) {
            graphView.selectedNodes[node.GetId()] = false;
        }
    }
    for (auto node : graphView.graph.nodeList) {
        if (abs(event.GetPosition().x - graphView.nodePositions[node.GetId()].x) < 20
            && abs(event.GetPosition().y - graphView.nodePositions[node.GetId()].y) < 20) 
        {
                graphView.selectedNodes[node.GetId()] = true;
            if (event.ControlDown()) {
                graphView.newEdgeNode1Id = node.GetId();
                std::cout << graphView.newEdgeNode1Id.value() << "\n";
            }
        }
    }
    Refresh();
}

void DrawingPane::OnMouseLeftUp(wxMouseEvent& event) {
    for (auto node : graphView.graph.nodeList) {
        if (abs(event.GetPosition().x - graphView.nodePositions[node.GetId()].x) < 20
            && abs(event.GetPosition().y - graphView.nodePositions[node.GetId()].y) < 20
            && event.ControlDown())
        {
            graphView.newEdgeNode2Id = node.GetId();
            std::cout << graphView.newEdgeNode2Id.value() << "\n";
        }
    }
    if (graphView.newEdgeNode1Id.has_value() && graphView.newEdgeNode2Id.has_value()) {
        graphView.AddEdge(graphView.newEdgeNode1Id.value(), graphView.newEdgeNode2Id.value());
    }
    graphView.newEdgeNode1Id = std::nullopt;
    graphView.newEdgeNode2Id = std::nullopt;
    Refresh();
}

void DrawingPane::OnMouseLeftDrag(wxMouseEvent& event) {
    // MouseDown event sets drag origin point
    auto translation = event.GetPosition() - graphView.dragOrigin;
    // Reset drag origin at event iteration so the translation amount doesn't keep incrementing
    graphView.dragOrigin = event.GetPosition();
    for (auto& node : graphView.graph.nodeList) {
        if (graphView.selectedNodes[node.GetId()] && event.Dragging()) {
            if (!event.ControlDown()) {
                graphView.nodePositions[node.GetId()] += translation;
                
            }    
        }
    }
    Refresh();
}

void DrawingPane::OnDoubleClick(wxMouseEvent& event) {
    auto nodePosIter = find_if(graphView.nodePositions.begin(), graphView.nodePositions.end(),
                                [&](auto& entry) {
                                    return abs(entry.second.x - event.GetPosition().x) < 20
                                            && abs(entry.second.y - event.GetPosition().y) < 20;
                                }
                        );
    if (nodePosIter != graphView.nodePositions.end()) {
        graphView.RemoveNode(nodePosIter->first);
    }
    else {
        graphView.AddNode(event.GetPosition());
    }
    Refresh();
}

void DrawingPane::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc) {
        graphView.Draw(gc);
        delete gc;
    }
}
