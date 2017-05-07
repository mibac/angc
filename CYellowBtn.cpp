#ifndef CYELLOWBTN_H
#include "CYellowBtn.h"
#endif

#include <iostream>
#include <string>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

using namespace std;

void CYellowBtn::setAttributes() {
  labeltype(FL_NORMAL_LABEL);
  align(FL_ALIGN_CENTER);

  textfont(1);
  textsize(24);
  textcolor(FL_BLACK);
  color(FL_YELLOW);
  readonly(1);
}

// Called when user finishes entering data with numeric keypad
void CYellowBtn::yellowBtn_CB2() {}

void CYellowBtn::yellowBtn_CB(Fl_Widget *, void *data) {}

void CYellowBtn::updateTime() {
  switch (count) {
    case 0:
      calcTime( gStartHoleClockTm, "     Hole\n     %M:%S");
      break;
    case 1:
      calcTime(gStartRoundClockTm, "   Round\n     %M:%S");
      break;
    case 2:
      calcTime(0, "    Clock\n  %I:%M:%S");
      break;
    default:;
  }
}

void CYellowBtn::calcTime(time_t tm, string str) {
  if (!bRoundStarted) return;

  struct tm *timeinfo;
  char buffer[80];

  time_t seconds = time(&gNowClockTm) - tm;
  timeinfo = localtime(&seconds);
  strftime(buffer, sizeof(buffer), str.c_str(), timeinfo);
  std::string s(buffer);

  yellowBtn->value(s.c_str());
  redraw();
}

// Handle when user right clicks on our input widget
int CYellowBtn::handle(int e) {
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
        count++;
        if (count > 2) count = 0;
        ret = 1;
      }
      break;
  }
  return (Fl_Output::handle(e) ? 1 : ret);
}

CYellowBtn::CYellowBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Multiline_Output(X, Y, W, H, L) {
  setAttributes();
  count = 0;
}
