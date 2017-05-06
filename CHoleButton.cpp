#ifndef CHOLEBUTTON_H
#include "CHoleButton.h"
#endif

#include <string>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

using namespace std;

CHolesPopup *myHolePopup = nullptr;  // local instance of numeric keypad widget

string CHoleBtn::holeName;

// Called when user finishes entering data with numeric keypad
void CHoleBtn::SetNumPadValue_CB2() {
  string str(myHolePopup->value());
  gCurrentHole = atoi(str.c_str());
  bPlayedHole[gCurrentHole] = true;
  time(&gNowClockTm);
  gStartHoleClockTm = gNowClockTm;
  if (bRoundStartFlag == false) {
      gStartRoundClockTm = gNowClockTm;
      bRoundStartFlag = true;
  }
  //cout << "In CHoleBtn::SetNumPadValue_CB2 " << gCurrentHole << endl;
  CHoleBtn::holeName = str;
  if (str.size() == 1)
    str = "  " + str;
  else
    str = " " + str;
  value(str.c_str());   // pass value from myHolePopup to our input
  myHolePopup->hide();  // hide myHolePopup
  cll.setRefMark();
}

void CHoleBtn::SetNumPadValue_CB(Fl_Widget *, void *data) {
  CHoleBtn *in = (CHoleBtn *)data;
  in->SetNumPadValue_CB2();
}
// Handle when user right clicks on our input widget
int CHoleBtn::handle(int e) {
  int ret = 0;
  switch (e) {
    // Mouse click on input field? Open myHolePopup dialog..
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
        if (!myHolePopup)
          myHolePopup = new CHolesPopup(0, 0, 72 * 3 + 8, 72 * 6 + 4);
        myHolePopup->SetEnterCallback(SetNumPadValue_CB, (void *)this);
        myHolePopup->position(parent()->x() + 112, parent()->y() + 88);
        myHolePopup->clear_border();
        myHolePopup->clear();
        myHolePopup->show();
      }
      break;
  }
  return (Fl_Output::handle(e) ? 1 : ret);
}

CHoleBtn::CHoleBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Output(X, Y, W, H, L) {
  myHolePopup = nullptr;
}
