#ifndef CCLUBPOPUP2_H
#define CCLUBPOPUP2_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <string>

#include <string>
using namespace std;

class CClubPopup2 : public Fl_Window {
  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void popupBtn_CB(Fl_Widget *w);
  static void staticButton_CB(Fl_Widget *w, void *data);

 public:
  int count;
  CClubPopup2(int X, int Y, int W, int H, const char *L = 0);
};

#endif  // CCLUBPOPUP_H
