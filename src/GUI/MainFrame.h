#pragma once

#include <wx/wx.h>
#include "DrawingPane.h"

class MainFrame : public wxFrame {
    public:
        MainFrame();
        void SetUpMainMenu();
        void Save(wxCommandEvent& event);
        void Open(wxCommandEvent& event);

        DrawingPane* drawingPane;
    private:

};