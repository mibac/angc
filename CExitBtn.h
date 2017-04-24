#ifndef CEXITBTN_H
#define CEXITBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

class CExitBtn : public Fl_Button {
  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void Button_CB();
  static void staticButton_CB(Fl_Widget *w, void *data);

 public:
  Fl_Window *mainwin;

  CExitBtn(int X, int Y, int W, int H, const char *L = 0);
};

extern CExitBtn *exitBtn;
#endif  // CEXITBTN_H
