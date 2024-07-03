#include <wx/wx.h>

class Main : public wxApp {
    public:
        bool OnInit();
};

bool Main::OnInit() {
    wxFrame* mainFrame = new wxFrame(nullptr, wxID_ANY, "GraphTutor");
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);