#ifndef CHISTORY_H
#define CHISTORY_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class CHistoryDlg : public Fl_Window {
public:
    CHistoryDlg(int X, int Y, int W, int H, const char *L = 0);
};

extern void createHistoryDlg();
extern CHistoryDlg *historyDlg;

#endif
