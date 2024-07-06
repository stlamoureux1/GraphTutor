#pragma once

#include <wx/wx.h>
#include "NodeView.h"
#include "EdgeView.h"
#include "Model/SimpleGraphImpl.h"

class DrawingPane : public wxWindow {
    public:
        DrawingPane(wxFrame* parent, wxWindowID id);
        void OnMouseLeftDown(wxMouseEvent&);
        void OnMouseLeftUp(wxMouseEvent&);
        void OnMouseLeftDrag(wxMouseEvent&);
        void OnDoubleClick(wxMouseEvent&);
        void OnPaint(wxPaintEvent&);
    private:
        std::vector<NodeView> nodeList;
        std::vector<EdgeView> edgeList;
        wxPoint dragOrigin;
        std::optional<NodeView> newEdgeStart;
        std::optional<NodeView> newEdgeEnd; 
        NodeId nodeCounter;
        EdgeId edgeCounter;
};
