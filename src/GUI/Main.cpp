#include <wx/wx.h>
#include "DrawingPane.h"

class Main : public wxApp {
    public:
        bool OnInit();
};

bool Main::OnInit() {
    wxFrame* mainFrame = new wxFrame(nullptr, wxID_ANY, "GraphTutor", wxDefaultPosition, wxSize(800, 600));
    DrawingPane* drawingPane = new DrawingPane(mainFrame, wxID_ANY);
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);