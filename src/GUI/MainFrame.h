#pragma once

#include <wx/wx.h>
#include "DrawingPane.h"

class MainFrame : public wxFrame {
    public:
        MainFrame();
        void SetUpMainMenu();
        void OnSave(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);

        DrawingPane* drawingPane;
    private:

};