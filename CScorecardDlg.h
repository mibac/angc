#ifndef CSCORECARDDLG_H
#define CSCORECARDDLG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>

class CScorecardDlg : public Fl_Window {
public:
    CScorecardDlg(int X, int Y, int W, int H, const char *L = 0);
    void updateCard();

};

extern void createScorecardDlg();
extern CScorecardDlg *scorecardDlg;

// Fl_Window* make_window();


#endif
