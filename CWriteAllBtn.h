#ifndef CWRITEALLBTN_H
#define CWRITEALLBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class CWriteAllBtn : public Fl_Button {

  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void Button_CB();
  static void staticButton_CB(Fl_Widget *w, void *data);

 public:
  CWriteAllBtn(int X, int Y, int W, int H, const char *L = 0);


};

extern CWriteAllBtn *writeAllBtn;
#endif  // CWRITEALLBTN_H
