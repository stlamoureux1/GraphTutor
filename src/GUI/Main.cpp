#include <wx/wx.h>
#include "MainFrame.h"
#include "DrawingPane.h"

class Main : public wxApp {
    public:
        bool OnInit();
};

bool Main::OnInit() {
    MainFrame* mainFrame = new MainFrame();
    mainFrame->SetUpMainMenu();
    mainFrame->Show();
    return true;
}

wxIMPLEMENT_APP(Main);