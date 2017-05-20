#ifndef CFRONTBACKBTN_H
#include "CFrontBackBtn.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#include "FL/Fl_Window.H"
using namespace std;

void CFrontBackBtn::fbBtn_CB(Fl_Widget *w, void *data) {
  gFront9 = !gFront9;
  Fl_Window *win = window();
  win->redraw();
}

// Handle numeric keypad buttons pressed
void CFrontBackBtn::staticfbBtn_CB(Fl_Widget *w, void *data) {
  CFrontBackBtn *cfb = (CFrontBackBtn *)data;
  cfb->fbBtn_CB(w, data);
}

void CFrontBackBtn::draw() {
  if (gFront9)
    label("Back 9");
  else
    label("Front 9");
  Fl_Button::draw();
}

CFrontBackBtn::CFrontBackBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
  setButtonStyle(this);
  callback(staticfbBtn_CB, (void *)this);
}
