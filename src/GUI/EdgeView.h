#pragma once

#include <wx/wx.h>
#include "NodeView.h"

class EdgeView {
    public:
        EdgeView(wxPoint endpoint1, wxPoint endpoint2);
        void Draw(wxGraphicsContext* gc);
        bool Contains(wxPoint point);

        bool isSelected;
        // NodeView m_node1;
        // NodeView m_node2;

        wxPoint m_endpoint1;
        wxPoint m_endpoint2;
    private:

};