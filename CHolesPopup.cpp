#ifndef CHOLESPOPUP_H
#include "CHolesPopup.h"
#endif

using namespace std;

void CHolesPopup::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(48);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}

// Handle numeric keypad buttons pressed
void CHolesPopup::Button_CB2(Fl_Widget *w) {
  Fl_Button *b = (Fl_Button *)w;
  s = b->label();
  in->replace(in->position(), in->mark(), b->label(), s.size());  // je
  (*enter_cb)(in, enter_data);
}

void CHolesPopup::Button_CB(Fl_Widget *w, void *data) {
  CHolesPopup *myHolePopup = (CHolesPopup *)data;
  myHolePopup->Button_CB2(w);
}

CHolesPopup::CHolesPopup(int X, int Y, int W, int H, const char *L)
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
  b = new Fl_Button(col, row, bsize, bsize, "1");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "2");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "3");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  setBtnAttributes(b);
  b = new Fl_Button(col, row, bsize, bsize, "4");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "5");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "6");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "7");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "8");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "9");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "10");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "11");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "12");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "13");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "14");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "15");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col = colstart;
  row += b->h();

  b = new Fl_Button(col, row, bsize, bsize, "16");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "17");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  col += b->w() + kDeltaX;
  b = new Fl_Button(col, row, bsize, bsize, "18");
  b->callback(Button_CB, (void *)this);
  setBtnAttributes(b);
  end();
  enter_cb = 0;
  enter_data = 0;
}
// Return current value
const char *CHolesPopup::value() { return (in->value()); }
// Clear current value
void CHolesPopup::clear() { in->value(""); }
// Set callback for when Enter is pressed
void CHolesPopup::SetEnterCallback(Fl_Callback *cb, void *data) {
  enter_cb = cb;
  enter_data = data;
  hide();
}
