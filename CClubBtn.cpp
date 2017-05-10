#ifndef CCLUBBTN_H
#include "CClubBtn.h"
#endif

#include <string>

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

using namespace std;

string CClubBtn::lastHitClub = "Dr";
string CClubBtn::goingToHitClub = "Dr";

CClubPopup *myClubPopup = nullptr;  // local instance of numeric keypad widget

void CClubBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(24);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}

// Called when user finishes entering data with numeric keypad
void CClubBtn::SetClubPopupValue_CB2() {
  string str(myClubPopup->value());
  CClubBtn::goingToHitClub = str;
  cll.updateClubVec(CClubBtn::lastHitClub);
  CClubBtn::lastHitClub = CClubBtn::goingToHitClub;
  myClubPopup->hide(); // hide ClubPopup
}

void CClubBtn::SetClubPopupValue_CB(Fl_Widget *, void *data) {
  CClubBtn *in = (CClubBtn *)data;
  in->SetClubPopupValue_CB2();
}

// Handle when user right clicks on our input widget
int CClubBtn::handle(int e) {
  int ret = 0;
  switch (e) {
    // Mouse click on input field? Open ClubPopup dialog..
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
        if (!myClubPopup) myClubPopup = new CClubPopup(0, 0, 72*3+8, 72*6+4);
        myClubPopup->SetEnterCallback(SetClubPopupValue_CB, (void *)this);
        myClubPopup->position(parent()->x()+112, parent()->y()+88);
        myClubPopup->clear_border();
        myClubPopup->clear();
        myClubPopup->show();
      }
      break;
  }
  return (Fl_Button::handle(e) ? 1 : ret);
}

CClubBtn::CClubBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
  myClubPopup = 0;
  setBtnAttributes(this);
}
