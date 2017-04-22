#ifndef CMARKBTN_H
#include "CMarkBtn.h"
#endif

#ifndef UTILS_H
#include "utils.h"
#endif

using namespace std;

void CMarkBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(24);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}
  void CMarkBtn::Button_CB() {
    DEBUG_LOG << "Mark button hit" << endl;
  }

// Handle numeric keypad buttons pressed
void CMarkBtn::staticButton_CB(Fl_Widget *, void *data) {
  CMarkBtn *cmb = (CMarkBtn *)data;
  cmb->Button_CB();
}

CMarkBtn::CMarkBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {

  setBtnAttributes(this);
  callback(staticButton_CB, (void *)this);
}
