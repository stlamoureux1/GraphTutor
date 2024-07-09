#include <fstream>
#include <wx/file.h>
#include "MainFrame.h"


MainFrame::MainFrame() 
    : wxFrame(nullptr, wxID_ANY, "GraphTutor", wxDefaultPosition, wxSize(800, 600)) {
        drawingPane = new DrawingPane(this, wxID_ANY);
        Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
        Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
        
}

void MainFrame::SetUpMainMenu() {
    wxMenuBar* menuBar = new wxMenuBar();

    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);

    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar);
}

void MainFrame::OnSave(wxCommandEvent& event) {

    wxFileDialog saveDialog(this, "Save", "", "", "JSON Files (*.json)|*.json", wxFD_SAVE);

    if (saveDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    ordered_json j = drawingPane->graphView;
    std::ofstream outFile{saveDialog.GetPath()};

    if (!outFile) {
        wxMessageBox("Failes to save file.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    outFile << std::setw(4) << j;
}

void MainFrame::OnOpen(wxCommandEvent& event) {

    wxFileDialog openDialog(this, "Open", "", "", "JSON Files (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::ifstream inFile{openDialog.GetPath()};

    // wxFile inFile(openDialog.GetPath(), wxFile::read);
    if (!inFile) {
        wxMessageBox("Failed to open file.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    ordered_json j = nlohmann::json::parse(inFile);
    SimpleGraphView newGraphView = j;
    drawingPane->graphView = newGraphView;
    drawingPane->Refresh();
}