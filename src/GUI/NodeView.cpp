#include "NodeView.h"

NodeView::NodeView(wxPoint center, wxDouble radius) 
    : m_center(center), m_radius(radius), isSelected(false) {}

void NodeView::Draw(wxGraphicsContext* gc) {
    wxPen pen = wxPen(*wxWHITE_PEN);
    if (isSelected) {
        pen.SetWidth(3);
    }
    wxBrush brush = wxBrush(wxColour(45, 45, 45));
    gc->SetPen(pen);
    gc->SetBrush(brush);
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(m_center.x, m_center.y, m_radius);
    gc->FillPath(path);
    gc->StrokePath(path);
    
}

void NodeView::Move(wxPoint dest) {
    m_center = dest;
}

bool NodeView::Contains(wxPoint point) {
    return abs(point.x - m_center.x) < m_radius && abs(point.y - m_center.y) < m_radius;
}

wxPoint NodeView::GetCenter() {
    return m_center;
}

void NodeView::SetCenter(wxPoint point) {
    m_center = point;
}

wxDouble NodeView::GetRadius() {
    return m_radius;
}

NodeId NodeView::GetId() {
    return m_id;
}

bool operator==(NodeView node1, NodeView node2) {
    return node1.GetId() == node2.GetId();
}