#include "EdgeView.h"

EdgeView::EdgeView(wxPoint endpoint1, wxPoint endpoint2)
    : m_endpoint1(endpoint1), m_endpoint2(endpoint2) {}

void EdgeView::Draw(wxGraphicsContext* gc) {
    wxPen pen = wxPen(*wxWHITE_PEN);
    if (isSelected) {
        pen.SetWidth(3);
    }
    gc->SetPen(pen);
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(m_endpoint1);
    path.AddLineToPoint(m_endpoint1);
    gc->StrokePath(path);
}

/*
bool EdgeView::Contains(wxPoint point) {
    return point.y - (((point.y - m_node1.GetCenter().y) / (point.x - m_node1.GetCenter().x)) * point.x) <= 3;
}
*/