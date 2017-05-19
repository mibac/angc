#ifndef CCLUBDLG_H
#define CCLUBDLG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>

#ifndef CCLUBCARD_H
#include "CClubcard.h"
#endif

#ifndef CCLUBPOPUP2_H
#include "CClubPopup2.h"
#endif

class CClubDlg : public Fl_Window {
public:
    CClubDlg(int X, int Y, int W, int H, const char *L = 0);

private:
    CClubDlg *clubcardDlg;
    Fl_Button *oKBtn;
    Fl_Button *skipBtn;
    CClubcard *clubcard;
    CClubPopup2 *clubPopup;
};

extern void createClubcardDlg();

#endif
