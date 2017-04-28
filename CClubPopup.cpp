#ifndef CCLUBPOPUP_H
#include "CClubPopup.h"
#endif

using namespace std;

void CClubPopup::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(30);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}

// Handle numeric keypad buttons pressed
void CClubPopup::Button_CB2(Fl_Widget *w) {
  Fl_Button *b = (Fl_Button *)w;
  // Appends label of button
  // in->replace(in->position(), in->mark(), b->label(), 1);
  // je
  s = b->label();
  in->replace(in->position(), in->mark(), b->label(), s.size());  // je
  (*enter_cb)(in, enter_data);
}

void CClubPopup::Button_CB(Fl_Widget *w, void *data) {
  CClubPopup *clubpad = (CClubPopup *)data;
  clubpad->Button_CB2(w);
}

CClubPopup::CClubPopup(int X, int Y, int W, int H, const char *L)
    : Fl_Window(X, Y, W, H, L) {
  const int bsize = 72;
  const int kDeltaX = 2;
  // Preview input
  in = new Fl_Input(0, 0, 1, 1);
  in->hide();
  // Numeric keypad
  Fl_Button *b;
  int colstart = 2;
  int col = colstart;
  int row = 2;
  b = new Fl_Button(col, row, bsize, bsize, "W\n1");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "W\n3");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "W\n5");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  setBtnAttributes(b);
  b = new Fl_Button(col, row, bsize, bsize, "W\n7");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "HY\n1");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "HY\n2");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "2");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "3");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "4");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "5");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "6");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "7");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "8");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "9");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "PW");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "GW");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "SW");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "LW");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  end();
  enter_cb = 0;
  enter_data = 0;
}
// Return current value
const char *CClubPopup::value() { return (in->value()); }
// Clear current value
void CClubPopup::clear() { in->value(""); }
// Set callback for when Enter is pressed
void CClubPopup::SetEnterCallback(Fl_Callback *cb, void *data) {
  enter_cb = cb;
  enter_data = data;
  hide();
}
