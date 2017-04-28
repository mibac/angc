#ifndef CHOLEBUTTON_H
#include "CHoleButton.h"
#endif

#include <string>

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

using namespace std;

MyNumPad *numpad;  // local instance of numeric keypad widget

string MyInput::holeName;

// Called when user finishes entering data with numeric keypad
void MyInput::SetNumPadValue_CB2() {
  string str(numpad->value());
  MyInput::holeName = str;
  if (str.size() == 1)
    str = "    " + str;
  else
    str = "   " + str;
  value(str.c_str());  // pass value from numpad to our input
  numpad->hide();          // hide numpad
  cll.setRefMark();
}

void MyInput::SetNumPadValue_CB(Fl_Widget *, void *data) {
  MyInput *in = (MyInput *)data;
  in->SetNumPadValue_CB2();
}
// Handle when user right clicks on our input widget
int MyInput::handle(int e) {
  int ret = 0;
  switch (e) {
    // Mouse click on input field? Open numpad dialog..
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
        if (!numpad) numpad = new MyNumPad(0, 0, 72*3+8, 72*6+4);
        numpad->SetEnterCallback(SetNumPadValue_CB, (void *)this);
        numpad->position(parent()->x()+112, parent()->y()+88);
        numpad->clear_border();
        numpad->clear();
        numpad->show();
      }
      break;
  }
  return (Fl_Output::handle(e) ? 1 : ret);
}

MyInput::MyInput(int X, int Y, int W, int H, const char *L)
    : Fl_Output(X, Y, W, H, L) {
  numpad = 0;
}
