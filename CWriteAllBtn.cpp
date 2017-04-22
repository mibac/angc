#ifndef CWRITEALLBTN_H
#include "CWriteAllBtn.h"
#endif

#ifndef UTILS_H
#include "utils.h"
#endif

using namespace std;

void CWriteAllBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(18);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}
  void CWriteAllBtn::Button_CB() {
    DEBUG_LOG << "Write All button hit" << endl;
  }

// Handle numeric keypad buttons pressed
void CWriteAllBtn::staticButton_CB(Fl_Widget *, void *data) {
  CWriteAllBtn *cmb = (CWriteAllBtn *)data;
  cmb->Button_CB();
}

CWriteAllBtn::CWriteAllBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {

  setBtnAttributes(this);
  callback(staticButton_CB, (void *)this);
}
