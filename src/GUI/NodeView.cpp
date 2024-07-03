#include "NodeView.h"

NodeView::NodeView(wxPoint center, wxDouble radius) 
    : m_center(center), m_radius(radius) {}

void NodeView::Draw(wxGraphicsContext* gc) {
    wxPen pen = wxPen(*wxWHITE_PEN);
    if (isSelected) {
        pen.SetWidth(3);
    }
    gc->SetPen(pen);
    wxGraphicsPath path = gc->CreatePath();
    path.AddCircle(m_center.x, m_center.y, m_radius);
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

wxDouble NodeView::GetRadius() {
    return m_radius;
}