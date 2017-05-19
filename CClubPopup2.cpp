#ifndef CCLUBPOPUP2_H
#include "CClubPopup2.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include <iostream>
using namespace std;

void CClubPopup2::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(30);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}

// Handle numeric keypad buttons pressed
void CClubPopup2::popupBtn_CB(Fl_Widget *w) {
  Fl_Button *b = (Fl_Button *)w;
  shotsRA[count].club = b->label();
  count++;
  if (count >= kMAX_SHOTS) count = kMAX_SHOTS - 1;
  Fl_Window *win = window();
  win->redraw();
}

void CClubPopup2::staticButton_CB(Fl_Widget *w, void *data) {
  CClubPopup2 *clubpad = (CClubPopup2 *)data;
  clubpad->popupBtn_CB(w);
}

CClubPopup2::CClubPopup2(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  const int bsize = 72;
  const int kDeltaX = 4;
  // Numeric keypad
  Fl_Button *b;
  int colstart = 2;
  int col = colstart;
  int row = 2;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kDr].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k3w].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k5w].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  setBtnAttributes(b);
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k7w].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kHy].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k2].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k3].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k4].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k5].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k6].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k7].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k8].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[k9].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kPW].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kGW].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kSW].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kLW].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, clubNamesRA[kx].c_str());
  b->callback(staticButton_CB, (void *)this);
  setBtnAttributes(b);
  end();

  count = 0;
}
