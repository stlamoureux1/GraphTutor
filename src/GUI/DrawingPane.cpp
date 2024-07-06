#include "DrawingPane.h"

DrawingPane::DrawingPane(wxFrame* parent, wxWindowID id) 
    : wxWindow(parent, id), newEdgeStart(std::nullopt), newEdgeEnd(std::nullopt) 
    {
        SetBackgroundStyle(wxBG_STYLE_PAINT);
        Bind(wxEVT_LEFT_DOWN, &DrawingPane::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &DrawingPane::OnMouseLeftUp, this);
        Bind(wxEVT_LEFT_DCLICK, &DrawingPane::OnDoubleClick, this);
        Bind(wxEVT_MOTION, &DrawingPane::OnMouseLeftDrag, this);
        Bind(wxEVT_PAINT, &DrawingPane::OnPaint, this);
    } 

void DrawingPane::OnMouseLeftDown(wxMouseEvent& event) {
    for (auto& node : nodeList) {
        if (node.Contains(event.GetPosition())) {
            node.isSelected = true;
            if (event.ControlDown()) {
                // On control-click, start creating new edge
                newEdgeStart = std::make_optional(node);
                // std::cout << "new edge start set\n";
            }
            else {
                dragOrigin = node.GetCenter();
            }
        }
        else {
            // Allow multi-selection on shift-click.
            // If shift is not pressed, deselect all other nodes.
            if (!event.ShiftDown()) {
                node.isSelected = false;
            }
        }
    }
    Refresh();
}

void DrawingPane::OnMouseLeftUp(wxMouseEvent& event) {
    for (auto& node : nodeList) {
        if (node.Contains(event.GetPosition()) && event.ControlDown()) {
            newEdgeEnd = std::make_optional(node);
            if (newEdgeStart.has_value() && newEdgeEnd.has_value()) {
                EdgeView newEdge(newEdgeStart.value(), newEdgeEnd.value());
                edgeList.push_back(newEdge);
            }
        }
    }
    Refresh();
}

void DrawingPane::OnMouseLeftDrag(wxMouseEvent& event) {
    // MouseDown event sets drag origin point
    auto translation = event.GetPosition() - dragOrigin;
    // Reset drag origin at event iteration so the translation amount doesn't keep incrementing
    dragOrigin = event.GetPosition();
    for (auto& node : nodeList) {
        if (node.isSelected && event.Dragging()) {
            if (!event.ControlDown()) {
                node.SetCenter(node.GetCenter() + translation);
            }
            // TBD Draw a dashed temporary edge when user drags from inside of node
            /*
            else {
                wxPaintDC dc(this);
                wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
                if (gc) {
                    wxPen pen = wxPen(*wxWHITE_PEN);
                    pen.SetStyle(wxPENSTYLE_LONG_DASH);
                    gc->SetPen(pen);
                    wxGraphicsPath path = gc->CreatePath();
                    path.MoveToPoint(newEdgeStart);
                    path.AddLineToPoint(event.GetPosition());
                    gc->StrokePath(path);
                    delete gc;
                }
            }
            */
        }
    }
    Refresh();
}

void DrawingPane::OnDoubleClick(wxMouseEvent& event) {
    // Check if an edge is under the cursor
    auto edgeIter = find_if(edgeList.begin(),
                            edgeList.end(),
                            [&](auto edgeView){ return edgeView.Contains(event.GetPosition()); }
                            );
    // If one is remove it
    if (edgeIter != edgeList.end()) {
        edgeList.erase(edgeIter);
    } 
    // Check if a node is under the cursor
    auto nodeIter = find_if(nodeList.begin(),
                            nodeList.end(),
                            [&](auto nodeView){ return nodeView.Contains(event.GetPosition()); }
                            );
    // If one is remove all incident edges and delete node
    if (nodeIter != nodeList.end()) {
        // TBD Remove incident edges
        /*
        auto edgeIter = remove_if(edgeList.begin(),
                                    edgeList.end(),
                                    [&](auto edgeView) {
                                        return edgeView.endpoint1 == nodeIter->GetCenter() 
                                            || edgeView.endpoint2 == nodeIter->GetCenter();
                                    });
        */
        edgeList.erase(edgeIter, edgeList.end());
        nodeList.erase(nodeIter);
    }
    else {
        NodeView newNode(event.GetPosition(), 20.0);
        nodeList.push_back(newNode);
    }
    Refresh();
}

void DrawingPane::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
    if (gc) {
        for (auto& edgeView: edgeList) {
            edgeView.Draw(gc);
        }
        for (auto& nodeView : nodeList) {
            nodeView.Draw(gc);
        }
        delete gc;
    }
}
