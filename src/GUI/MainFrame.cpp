#include <fstream>
#include "MainFrame.h"


MainFrame::MainFrame() 
    : wxFrame(nullptr, wxID_ANY, "GraphTutor", wxDefaultPosition, wxSize(800, 600)) {
        drawingPane = new DrawingPane(this, wxID_ANY);
        Bind(wxEVT_MENU, &MainFrame::Save, this, wxID_SAVE);
        Bind(wxEVT_MENU, &MainFrame::Open, this, wxID_OPEN);
        
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

void MainFrame::Save(wxCommandEvent& event) {
    ordered_json j = drawingPane->graphView;
    std::ofstream outFile{"graph.json"};
    if (!outFile) {
        std::cout << "save failed\n";
        return;
    }
    outFile << std::setw(4) << j;
    std::cout << "saved graph.json\n";
}

void MainFrame::Open(wxCommandEvent& event) {
    ordered_json j;
    std::ifstream inFile{"graph.json"};
    if (!inFile) {
        std::cout << "open failed\n";
        return;
    }
    inFile >> j;
    SimpleGraphView newGraphView = j;
    drawingPane->graphView = newGraphView;
    drawingPane->Refresh();
}