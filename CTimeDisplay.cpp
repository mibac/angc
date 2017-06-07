#ifndef CTIMEDISPLAY_H
#include "CTimeDisplay.h"
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

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

using namespace std;

void CTimeDisplay::setAttributes() {
  labeltype(FL_NORMAL_LABEL);
  align(FL_ALIGN_CENTER);
  box(FL_UP_BOX);
  textfont(1);
  textsize(36);
  textcolor(FL_BLACK);
  color(getBkgRGBcolor());
  selection_color(getBkgRGBcolor());
  cursor_color(getBkgRGBcolor());
  box(FL_NO_BOX);
  scrollbar_width(0);
}

// Called when user finishes entering data with numeric keypad
void CTimeDisplay::gTmDisplay_CB2() {}

void CTimeDisplay::gTmDisplay_CB(Fl_Widget *, void *data) {}

void CTimeDisplay::calcGPStime(const string &lbl) {
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
  gTmbuff->text(timeStr.c_str());
}

void CTimeDisplay::calcRoundGPStime(const string &lbl) {
  if ((count != 2) && (gStartRoundTimeStr == "")) return;
  CGPStime tm;
  int sec = tm.timeDifference(gNowTimeStr, gStartRoundTimeStr);
  CGPStime val(sec);
  timeStr = val.sec2str(sec, lbl).c_str();
  gTmbuff->text(timeStr.c_str());
}

int countHolesPlayed() {
  int num = 0;
  for (int ix = 0; ix < 18; ++ix)
    if (bPlayedHole[ix]) num++;
  return num;
}

void CTimeDisplay::calcAvgHoleGPStime(const string &lbl) {
  if ((count != 2) && (gStartRoundTimeStr == "")) return;
  CGPStime val(avgTm);
  timeStr = val.sec2str(avgTm, lbl).c_str();
  gTmbuff->text(timeStr.c_str());
}

void CTimeDisplay::showAvgHoleGPStime(int holesPlayed) {
  CGPStime tm;
  string lbl("Avg\n");
  int sec = tm.timeDifference(gNowTimeStr, gStartRoundTimeStr);
  avgTm = sec / holesPlayed;
  CGPStime val(avgTm);
  timeStr = val.sec2str(avgTm, lbl).c_str();
  gTmbuff->text(timeStr.c_str());
}

void CTimeDisplay::updateGPStime() {
  if (!bRoundStarted) {
    textcolor(FL_BLUE);
    timeStr = "Start";
    gTmbuff->text(timeStr.c_str());
  } else {
    textcolor(FL_BLACK);
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
}

// Handle when user right clicks on the Start button
int CTimeDisplay::handle(int e) {
  int ret = 0;
  switch (e) {
    case FL_PUSH:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        ret = 1;
      }
      break;
    case FL_RELEASE:
      if (Fl::event_button() == FL_LEFT_MOUSE) {
        if (!bRoundStarted) {
          bRoundStarted = true;
          gCurrentHole = 1;
          gShotRA[gCurrentHole - 1].shot[0].utm = cll.getNowMark();
          gShotRA[gCurrentHole - 1].nmarks = 1;
          gShotCount = 1;
          gStartRoundTimeStr = gNowTimeStr;
          gHoleTimeRA[gCurrentHole - 1].begstr = gNowTimeStr;
          gTmpTimes << "CTimeDisplay::handle-if: gHoleTimeRA[" << gCurrentHole - 1 << "].begstr\t"
               << gHoleTimeRA[gCurrentHole - 1].begstr << endl;
        } else {
          count++;
          if (count > 2) count = 0;
          gHoleTimeRA[gCurrentHole - 1].begstr = gNowTimeStr;
          gTmpTimes << "CTimeDisplay::handle-else: gHoleTimeRA[" << gCurrentHole - 1 << "].begstr\t"
               << gHoleTimeRA[gCurrentHole - 1].begstr << endl;
        }
        ret = 1;
      }
      break;
  }
  return (Fl_Text_Display::handle(e) ? 1 : ret);
}

CTimeDisplay::CTimeDisplay(int X, int Y, int W, int H, const char *L)
    : Fl_Text_Display(X, Y, W, H, L) {
  gTmbuff = new Fl_Text_Buffer();
  buffer(gTmbuff);
  setAttributes();
  count = 2;
}
