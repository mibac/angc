#ifndef CCLUBBTN_H
#define CCLUBBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.H>

#ifndef CCLUBPOPUP_H
#include "CClubPopup.h"
#endif

#include <string>
using namespace std;

class CClubBtn : public Fl_Button {

  void setBtnAttributes(Fl_Button *b);

  // Called when user finishes entering data with numeric keypad
  void SetClubPopupValue_CB2();

  static void SetClubPopupValue_CB(Fl_Widget *, void *data);

  // Handle when user right clicks on our input widget
  int handle(int e);

 public:
  static string clubName;

  CClubBtn(int X, int Y, int W, int H, const char *L = 0);
};

    extern CClubPopup *myClubPopup;  // local instance of numeric keypad widget
#endif  // CCLUBBTN_H
