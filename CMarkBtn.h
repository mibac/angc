#ifndef CMARKBTN_H
#define CMARKBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "HoleView.hpp"

class CMarkBtn : public Fl_Button {

  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void Button_CB();
  static void staticButton_CB(Fl_Widget *w, void *data);

 public:
  CMarkBtn(int X, int Y, int W, int H, const char *L = 0);
  HoleView *holeview;


};

extern CMarkBtn *markBtn;
#endif  // CMARKBTN_H
