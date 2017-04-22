#ifndef CHOLEBUTTON_H
#define CHOLEBUTTON_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

#ifndef CHOLESPOPUP_H
#include "CHolesPopup.h"
#endif

class MyInput : public Fl_Input {
  MyNumPad *numpad;  // local instance of numeric keypad widget

  // Called when user finishes entering data with numeric keypad
  void SetNumPadValue_CB2();

  static void SetNumPadValue_CB(Fl_Widget *, void *data);

  // Handle when user right clicks on our input widget
  int handle(int e);

 public:
  MyInput(int X, int Y, int W, int H, const char *L = 0);
};

#endif //CHOLEBUTTON_H
