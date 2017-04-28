#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#ifndef UTILS_H
#include "utils.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#include <fstream>

using namespace std;

void CExitBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(24);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}
void CExitBtn::Button_CB() {
  // fileMark.close();
  fileClub.close();
  fileAll.close();
  DEBUG_LOG << "Exit button hit" << endl;
  pclose(gpsin);
  mainwin->hide();
}

// Handle numeric keypad buttons pressed
void CExitBtn::staticButton_CB(Fl_Widget *, void *data) {
  CExitBtn *ceb = (CExitBtn *)data;
  ceb->Button_CB();
}

CExitBtn::CExitBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
  setBtnAttributes(this);
  callback(staticButton_CB, (void *)this);
}
