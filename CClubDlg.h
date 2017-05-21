#ifndef CCLUBDLG_H
#define CCLUBDLG_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Table.H>

#ifndef CCLUBCARD_H
#include "CClubcard.h"
#endif

class CClubDlg : public Fl_Window {
public:
    CClubDlg(int X, int Y, int W, int H, const char *L = 0);

    // Handle numeric keypad buttons pressed
    void popupBtn_CB(Fl_Widget *w);
    static void staticPopup_CB(Fl_Widget *w, void *data);

private:

    void setClubBtnStyle(Fl_Button *b);
    // int handle(int e);
};

extern void createCClubDlg();

#endif
