#pragma once

#include <wx/wx.h>
#include "Model/Node.h"

// Connect node views to nodes in underlying model
// by id to avoid templating node views.
class NodeView {
    public:
        NodeView(wxPoint center, wxDouble radius);
        void Draw(wxGraphicsContext* gc);
        void Move(wxPoint dest);
        bool Contains(wxPoint point);
        wxPoint GetCenter();
        wxDouble GetRadius();
    
        bool isSelected;
    private:
        wxPoint m_center;
        wxDouble m_radius;
        NodeId m_id;
        wxString m_label;
};
