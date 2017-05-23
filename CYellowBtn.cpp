#ifndef CYELLOWBTN_H
#include "CYellowBtn.h"
#endif

#include <iostream>
#include <string>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CGPSTIME_H
#include "CGPStime.h"
#endif

#ifndef CHOLEBUTTON_H
#include "CHoleBtn.h"
#endif

using namespace std;

void CYellowBtn::setAttributes() {
  labeltype(FL_NORMAL_LABEL);
  align(FL_ALIGN_CENTER);
  box(FL_UP_BOX);
  textfont(1);
  textsize(36);
  textcolor(FL_BLACK);
  color(fl_rgb_color(162, 255, 146));
  selection_color(fl_rgb_color(162, 255, 146));
  cursor_color(fl_rgb_color(162, 255, 146));
  readonly(1);
}

// Called when user finishes entering data with numeric keypad
void CYellowBtn::yellowBtn_CB2() {}

void CYellowBtn::yellowBtn_CB(Fl_Widget *, void *data) {}

void CYellowBtn::calcGPStime(const string &lbl) {
  if (gNowTimeStr == "") return;
  string stm = gNowTimeStr;
  int len = stm.length();
  if (len < 6) {
    for (int ix = 0; ix < 6 - len; ++ix) stm = "0" + stm;
  }

  string hs = stm.substr(0, 2);
  string ms = stm.substr(2, 2);
  string ss = stm.substr(4, 2);

  string s;
  int hr = stoi(hs);
  if (hr < 6)
    hr += 12;
  else if (hr > 16)
    hr -= 12;
  hr -= 5;
  if (hr == 0) hr = 12;
  hs = to_string(hr);
  timeStr = lbl + hs + ":" + ms;

  value(timeStr.c_str());
  redraw();
}

void CYellowBtn::calcRoundGPStime(const string &lbl) {
  if ((count != 2) && (gStartRoundTimeStr == "")) return;
  CGPStime tm;
  int sec = tm.timeDifference(gNowTimeStr, gStartRoundTimeStr);
  CGPStime val(sec);
  timeStr = val.sec2str(sec, lbl).c_str();
  value(timeStr.c_str());
  redraw();
}

int countHolesPlayed() {
  int num = 0;
  for (int ix = 0; ix < 18; ++ix)
    if (bPlayedHole[ix]) num++;
  return num;
}

void CYellowBtn::calcAvgHoleGPStime(const string &lbl) {
  if ((count != 2) && (gStartRoundTimeStr == "")) return;
  CGPStime tm;
  int sec = tm.timeDifference(gNowTimeStr, gStartRoundTimeStr);
  int num = countHolesPlayed();
  if (num > 0) sec /= num;
  CGPStime val(sec);
  timeStr = val.sec2str(sec, lbl).c_str();
  value(timeStr.c_str());
  redraw();
}

void CYellowBtn::updateGPStime() {
  switch (count) {
    case 0:
      calcRoundGPStime("Round\n");
      break;
    case 1:
      calcAvgHoleGPStime("Avg\n");
      break;
    case 2:
      calcGPStime("Time\n");
      break;
    default:;
  }
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
  count = 2;
}
