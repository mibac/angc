#ifndef CScoreBtn_H
#define CScoreBtn_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

#ifndef CSCOREDLG_H
#include "CScoreDlg2.h"
#endif

class CScoreBtn : public Fl_Button {

  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void Button_CB();
  static void staticButton_CB(Fl_Widget *w, void *data);

  int handle(int e);

 public:
  CScoreBtn(int X, int Y, int W, int H, const char *L = 0);
};

extern CScoreDlg2 *scoreDlg2;

#endif  // CScoreBtn_H
