#pragma once

#include <wx/wx.h>
#include "NodeView.h"

class EdgeView {
    public:
        EdgeView(NodeView& node1, NodeView& node2);
        void Draw(wxGraphicsContext* gc);
        bool Contains(wxPoint point);

        bool isSelected;
    private:
        wxPoint endpoint1;
        wxPoint endpoint2;
};