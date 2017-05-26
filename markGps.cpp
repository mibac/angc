#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <FL/gl.h>
#include <FL/glu.h>
#include <unistd.h>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Timer.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/fl_draw.H>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef HOLEVIEW_H_
#include "HoleView.h"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef C2UTM_hpp
#include "C2UTM.h"
#endif

#ifndef CHOLESPOPUP_H
#include "CHolesPopup.h"
#endif

#ifndef CHOLEBUTTON_H
#include "CHoleBtn.h"  //CHoleBtn *holeBtn
#endif

#ifndef CScoreBtn_H
#include "CScoreBtn.h"
#endif

#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#ifndef CTIMEDISPLAY_H
#include "CTimeDisplay.h"
#endif

using namespace std;

Fl_Window *win;
Fl_Output *my_input;
CHoleBtn *holeBtn;
CScoreBtn *scoreBtn;
CExitBtn *exitBtn;
FILE *gpsin = nullptr;
HoleView *hv;
Course *ngc;

const int kBUFSIZE = 1024;
char gpsBuf[kBUFSIZE];
#define JACK 0
#if JACK
const char *GPS_CMD = "gpspipe -r /dev/ttyACM0";
#else
const char *GPS_CMD = "gpspipe -r /dev/ttyAMA0";
// const char *GPS_CMD = "gpspipe -r /dev/ttyACM0";
// const char *GPS_CMD = "gpspipe -r /dev/ttyUSB0";
#endif

void setMainBtnStyle(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(24);
  b->color(FL_WHITE);
  // b->down_color(FL_DARK_BLUE);
  b->down_color(FL_DARK_BLUE);
}

// This window callback allows the user to save & exit, don't save, or cancel.
static void window_cb(Fl_Widget *widget, void *) { exitBtn->Button_CB(); }

static void markBtn_cb(Fl_Widget *widget, void *) {
  gShotCount++;
  if (gShotCount > kMAX_SHOTS) gShotCount = kMAX_SHOTS;
  markBtnLabel = "Mark\n" + to_string(gShotCount);
  markBtn->label(markBtnLabel.c_str());

  UtmLatLng u = cll.getNowMark();
  gShotRA[gCurrentHole - 1].shot[gShotCount-1].utm = u;
  gShotRA[gCurrentHole - 1].nmarks++;
}

void HandleFD(FL_SOCKET fd, void *data) {
  int n = atoi(holeBtn->value());
  if (n == 0) n = 1;
  // double dt;
  if (gCurrentHole == n) {
#if USEGPS == 0
    hv->redraw();

#endif
  }
  if (gCurrentHole != n) {
    gCurrentHole = n;
#if USEGPS == 0
    hv->redraw();
#endif
  }
#if USEGPS
  const int bufSz = 1023;
  char chRA[bufSz + 1];
  if (fgets(chRA, sizeof(chRA), gpsin) == NULL) {  // read the line of data
    Fl::remove_fd(fileno(gpsin));                  // command ended? disconnect
    pclose(gpsin);                                 // close the descriptor
    return;
  } else {
    string gpsStr(chRA);
    size_t found = gpsStr.find("GPGGA");
    // size_t found = s.find("GPGLL");
    if (found != string::npos) {
      gTmDisplay->updateGPStime();
      cll.updateLatLng(gpsStr.c_str());
      UtmLatLng u = cll.getNowMark();
      if ((fabs(u.lng - hv->ngc->hole[gCurrentHole].startOrient[0].v[0]) >
           3000.0) ||
          ((fabs(u.lat - hv->ngc->hole[gCurrentHole].startOrient[0].v[1]) >
            3000.0)))
        hv->ngc->hole[gCurrentHole].setCurrentPoint(
            hv->ngc->hole[gCurrentHole].startOrient[0].v[0],
            hv->ngc->hole[gCurrentHole].startOrient[0].v[1]);
      else
        hv->ngc->hole[gCurrentHole].setCurrentPoint(u.lng, u.lat);
      hv->redraw();
    }
  }
#endif
}

int main(int argc, char **argv) {
#if USEGPS
  if (!(gpsin = popen(GPS_CMD, "r"))) {
    cout << "No GPS found" << endl;
    return (1);
  }
#endif

  const int kXDelta = 3;
  const int kBoxSize = 80;
  const int kHoleViewTop = 0;
  const int kBtnRow1Top = 680;
  const int kYardageLeft = kXDelta;
  const int kYardageWid = 130;
  const int kHoleLeft = kYardageLeft + kYardageWid + kXDelta;
  const int kHoleWid = kBoxSize + kXDelta;
  const int kMarkLeft = kHoleLeft + kHoleWid + kXDelta;
  const int kMarkWid = kBoxSize + kXDelta;
  const int kScoreLeft = kMarkLeft + kMarkWid + kXDelta;
  const int kScoreWid = kBoxSize + kXDelta;
  const int kExitLeft = kScoreLeft + kScoreWid + kXDelta;
  const int kExitWid = kBoxSize;

  initGlobals();  // in globals.h

  ngc = new Course(18);
  ngc->readCourse();
  int x = 480;
  int y = 674;
  win = new Fl_Window(0, 0, 480, 800, "NGC Golf");
  win->size_range(480, 800, 480, 800);
  win->color(getBkgRGBcolor());
  win->callback(window_cb);

  win->begin();
  hv = new HoleView(0, kHoleViewTop, x, y, 0);
  hv->mode(FL_DOUBLE);

  gTmDisplay = new CTimeDisplay(3, kBtnRow1Top, kYardageWid + 1, kBoxSize, 0);

  holeBtn = new CHoleBtn(kHoleLeft, kBtnRow1Top, kHoleWid, kBoxSize);
  holeBtn->align(FL_ALIGN_CENTER);

  holeBtn->value("  1");
  holeBtn->textfont(1);
  holeBtn->textsize(48);
  holeBtn->cursor_color(FL_GRAY);

  markBtn =
      new Fl_Button(kMarkLeft, kBtnRow1Top, kMarkWid, kBoxSize, "Mark\n1");
  setMainBtnStyle(markBtn);
  markBtn->callback(markBtn_cb);

  scoreBtn =
      new CScoreBtn(kScoreLeft, kBtnRow1Top, kScoreWid, kBoxSize, "Score");
  setMainBtnStyle(scoreBtn);

  exitBtn = new CExitBtn(kExitLeft, kBtnRow1Top, kExitWid, kBoxSize, "Exit");
  setMainBtnStyle(exitBtn);
  exitBtn->mainwin = win;
  win->end();

  win->resizable(win);
  win->show();

  gShotCount = 1;
  hv->make_current();
  hv->initHoleWindow(x, y, ngc);
  hv->makeList();
  hv->show();
  hv->draw();
  // setup a callback for the popen() ed descriptor
  Fl::add_fd(fileno(gpsin), HandleFD, 0);
  return (Fl::run());
}
