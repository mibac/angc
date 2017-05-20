#ifndef CFRONTBACKBTN_H
#define CFRONTBACKBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class CFrontBackBtn : public Fl_Button {
  // Handle numeric keypad buttons pressed
  void fbBtn_CB(Fl_Widget *w, void *data);
  static void staticfbBtn_CB(Fl_Widget *w, void *data);

  void draw();

 public:
  CFrontBackBtn(int X, int Y, int W, int H, const char *L = 0);
};

#endif  // CFRONTBACKBTN_H
