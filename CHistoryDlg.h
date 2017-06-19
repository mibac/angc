#ifndef CHISTORY_H
#define CHISTORY_H

#include <vector>
#include <string>
#include <array>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

using namespace std;

class CHistoryDlg : public Fl_Window {
public:
    CHistoryDlg(int X, int Y, int W, int H, const char *L = 0);

};

extern void createHistoryDlg();
extern CHistoryDlg *historyDlg;

#endif
