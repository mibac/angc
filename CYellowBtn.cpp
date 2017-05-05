#ifndef CYELLOWBTN_H
#include "CYellowBtn.h"
#endif

#include <iostream>
#include <string>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

using namespace std;

string CYellowBtn::holeName;

void CYellowBtn::setAttributes() {
  labeltype(FL_NORMAL_LABEL);
  align(FL_ALIGN_CENTER);

  textfont(1);
  textsize(36);
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
      updateHoleTime();
      break;
    case 1:
      updateElapsedTime();
      break;
    case 2:
      updateLocalTime();
      break;
    default:;
  }
}

void CYellowBtn::updateHoleTime() {
  if (gNowUTC != gLastUTC) {
    int seconds = gNowUTC - gLastUTC;
    int hr = seconds / 3600;
    int mn = seconds / 60;
    int sc = seconds - (hr * 3600 + mn * 60);
    string hs = to_string(hr);
    string ms = to_string(mn);
    string ss = to_string(sc);
    if (hr == 0)
      hs = "";
    else if (hs.length() == 1)
      hs = "0" + hs + ":";
    else if (hs.length() == 2)
      hs = hs + ":";
    else
      hs = "";

    if (ms.length() == 1)
      ms = "0" + ms + ":";
    else if (ms.length() == 2)
      ms = ms + ":";
    else
      ms = "";

    if (ss.length() == 1)
      ss = "0" + ss;
    else if (ss.length() != 2)
      ss = "";

    string s = hs + ms + ss;
    yellowBtn->value(s.c_str());
    gLastUTC = gNowUTC;
    redraw();
  }
}

void CYellowBtn::updateElapsedTime() {
  if (gNowUTC != 0) {
    // cout << "In CYellowBtn::updateTime now, last " << gNowUTC << " " <<
    // gLastUTC
    //      << endl;
    int seconds = gNowUTC - gStartRoundUTC;
    int hr = seconds / 3600;
    int mn = seconds / 60;
    int sc = seconds - (hr * 3600 + mn * 60);
    string hs = to_string(hr);
    string ms = to_string(mn);
    string ss = to_string(sc);
    if (hr == 0)
      hs = "";
    else if (hs.length() == 1)
      hs = "0" + hs + ":";
    else if (hs.length() == 2)
      hs = hs + ":";
    else
      hs = "";

    if (ms.length() == 1)
      ms = "0" + ms + ":";
    else if (ms.length() == 2)
      ms = ms + ":";
    else
      ms = "";

    if (ss.length() == 1)
      ss = "0" + ss;
    else if (ss.length() != 2)
      ss = "";

    string s = hs + ms + ss;
    yellowBtn->value(s.c_str());
    gLastUTC = gNowUTC;
    redraw();
  }
}

void CYellowBtn::updateLocalTime() {
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);
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
    : Fl_Output(X, Y, W, H, L) {
  setAttributes();
  count = 0;
}
