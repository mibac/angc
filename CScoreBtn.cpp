#ifndef CScoreBtn_H
#include "CScoreBtn.h"
#endif

using namespace std;

CScoreDlg2 *scoreDlg2 = nullptr;

// Handle when user right clicks on our input widget
int CScoreBtn::handle(int e) {
  int ret = 0;
  switch (e) {
    // Mouse click on input field? Open scoreDlg dialog..
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
        createScoreDlg2();
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
  }
  return (Fl_Button::handle(e) ? 1 : ret);
}

CScoreBtn::CScoreBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
}
