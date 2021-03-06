#ifndef CSCORECARDDLG_H
#define CSCORECARDDLG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>

#ifndef CSCORECARD_H
#include "CScorecard.h"
#endif


class CScorecardDlg : public Fl_Window {
public:

    CScorecardDlg(int X, int Y, int W, int H, const char *L = 0);
    void updateStats();
};

extern void createScorecardDlg();
extern CScorecardDlg *scorecardDlg;
extern CScorecard *gScorecard;

#endif
