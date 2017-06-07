#ifndef CHOLEBUTTON_H
#include "CHoleBtn.h"
#endif

#include <string>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef HOLEVIEW_H_
#include "HoleView.h"
#endif

using namespace std;

CHolesPopup *myHolePopup = nullptr;  // local instance of numeric keypad widget

string CHoleBtn::holeName;

// Called when user finishes entering data with numeric keypad
void CHoleBtn::SetNumPadValue_CB2() {
  string str(myHolePopup->value());
  gCurrentHole = atoi(str.c_str());
  bPlayedHole[gCurrentHole - 1] = true;
  gShotRA[gCurrentHole - 1].shot[0].utm = cll.getNowMark();
  updateHole(str);

  gStartHoleTimeStr = gNowTimeStr;
  gHoleTimeRA[gCurrentHole - 1].beg = stoi(gStartHoleTimeStr);
  gTmpTimes << gHoleTimeRA[gCurrentHole - 1].beg << "\t";
  cout << "CHoleBtn::SetNumPadValue_CB2: gHoleTimeRA[" << gCurrentHole - 1
       << "].beg " << gHoleTimeRA[gCurrentHole - 1].beg << endl;

  myHolePopup->hide();  // hide myHolePopup
}

void CHoleBtn::SetNumPadValue_CB(Fl_Widget *, void *data) {
  CHoleBtn *in = (CHoleBtn *)data;
  in->SetNumPadValue_CB2();
}

void CHoleBtn::setNewHole() {
  bPlayedHole[gCurrentHole - 1] = true;

  gCurrentHole++;
  if (gCurrentHole > 18) gCurrentHole = 18;
  string str = to_string(gCurrentHole);
  updateHole(str);

  gStartHoleTimeStr = gNowTimeStr;
  gHoleTimeRA[gCurrentHole - 1].beg = stoi(gStartHoleTimeStr);
  gTmpTimes << gHoleTimeRA[gCurrentHole - 1].beg << "\t";
  cout << "CHoleBtn::setNewHole: gHoleTimeRA[" << gCurrentHole - 1 << "].beg "
       << gHoleTimeRA[gCurrentHole - 1].beg << endl;
}

void CHoleBtn::updateHole(string str) {
  CHoleBtn::holeName = str;
  if (str.size() == 1)
    str = "  " + str;
  else
    str = " " + str;
  value(str.c_str());  // pass value from myHolePopup to our input
  gShotRA[gCurrentHole - 1].nmarks = 1;
  gShotCount = 1;
  markBtnLabel = "Mark\n1";
  markBtn->label(markBtnLabel.c_str());

  gThisGreen.lng = hv->ngc->hole[gCurrentHole].startOrient[1].v[0];
  gThisGreen.lat = hv->ngc->hole[gCurrentHole].startOrient[1].v[1];
  gNextTee.lng = hv->ngc->hole[gCurrentHole + 1].startOrient[0].v[0];
  gNextTee.lat = hv->ngc->hole[gCurrentHole + 1].startOrient[0].v[1];
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
