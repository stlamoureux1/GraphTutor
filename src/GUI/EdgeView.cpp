#include "EdgeView.h"

EdgeView::EdgeView(NodeView& node1, NodeView& node2)
    : endpoint1(node1.GetCenter()), endpoint2(node2.GetCenter()) {}

void EdgeView::Draw(wxGraphicsContext* gc) {
    wxPen pen = wxPen(*wxWHITE_PEN);
    if (isSelected) {
        pen.SetWidth(3);
    }
    gc->SetPen(pen);
    wxGraphicsPath path = gc->CreatePath();
    path.MoveToPoint(endpoint1);
    path.AddLineToPoint(endpoint2);
    gc->StrokePath(path);
}

bool EdgeView::Contains(wxPoint point) {
    return point.y - (((point.y - endpoint1.y) / (point.x - endpoint1.x)) * point.x) <= 3;
}