#ifndef CWRITEMARKBTN_H
#include "CWriteMarkBtn.h"
#endif

#ifndef UTILS_H
#include "utils.h"
#endif

using namespace std;

void CWriteMarkBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(18);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}
  void CWriteMarkBtn::Button_CB() {
    DEBUG_LOG << "Write Mark button hit" << endl;
  }

// Handle numeric keypad buttons pressed
void CWriteMarkBtn::staticButton_CB(Fl_Widget *, void *data) {
  CWriteMarkBtn *cmb = (CWriteMarkBtn *)data;
  cmb->Button_CB();
}

CWriteMarkBtn::CWriteMarkBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {

  setBtnAttributes(this);
  callback(staticButton_CB, (void *)this);
}
