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

#ifndef UTILS_H
#include "utils.h"
#endif

#ifndef CHOLESPOPUP_H
#include "CHolesPopup.h"
#endif

#ifndef CHOLEBUTTON_H
#include "CHoleButton.h"  //CHoleBtn *holeBtn
#endif

#ifndef CCLUBBTN_H
#include "CClubBtn.h"
#endif

#ifndef CScoreBtn_H
#include "CScoreBtn.h"
#endif

#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#ifndef CSCORES_H
#include "CScores.h"
#endif

using namespace std;

// Conditionals
#define USEGPS 1

// GLOBALS

Fl_Window *win;
Fl_Output *my_input;
Fl_Box *boxYardage;
Fl_Button *btnMark;
Fl_Button *btnWrite;
CHoleBtn *holeBtn;
CClubBtn *clubBtn;
CScoreBtn *scoreBtn;
CExitBtn *exitBtn;
FILE *gpsin = nullptr;
HoleView *hv;
Course *ngc;

const int kBUFSIZE = 1024;
char gpsBuf[kBUFSIZE];
const char *GPS_CMD = "gpspipe -r /dev/ttyACM0";


#if USEGPS
void HandleFD(FL_SOCKET fd, void *data) {
  const int bufSz = 1023;
  char chRA[bufSz + 1];

  int n = atoi(holeBtn->value());
  if (n == 0) n = 1;
  if (gCurrentHole != n) {
    // hv->redraw();
    gCurrentHole = n;
  }

  if (fgets(chRA, sizeof(chRA), gpsin) == NULL) {  // read the line of data
    Fl::remove_fd(fileno(gpsin));                  // command ended? disconnect
    pclose(gpsin);                                 // close the descriptor
    return;
  } else {
    string gpsStr(chRA);
    size_t found = gpsStr.find("GPGGA");
    // size_t found = s.find("GPGLL");
    if (found != string::npos) {
      cll.updateLatLng(gpsStr.c_str());
      string s = cll.distanceFromLastMark();
      boxYardage->label(s.c_str());
      // cout << "holeBtn IdleCallback: " << s << endl;
      UtmLatLng u = cll.getNowMark();
      hv->ngc->hole[gCurrentHole].setCurrentPoint(u.lng, u.lat);
      hv->redraw();
    }
  }
}
#endif

// This window callback allows the user to save & exit, don't save, or cancel.
static void window_cb(Fl_Widget *widget, void *) { exitBtn->Button_CB(); }

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
  const int kClubLeft = kHoleLeft + kHoleWid + kXDelta;
  const int kClubWid = kBoxSize + kXDelta;
  const int kWriteLeft = kClubLeft + kClubWid + kXDelta;
  const int kWriteWid = kBoxSize + kXDelta;
  const int kExitLeft = kWriteLeft + kWriteWid + kXDelta;
  const int kExitWid = kBoxSize;

  initGlobals(); // in globals.h

  ngc = new Course(18);
  ngc->readCourse();
  int x = 480;
  int y = 674;
  win = new Fl_Window(0, 40, 480, 800, "NGC Golf");
  win->color(fl_rgb_color(162, 255, 146));
  win->callback(window_cb);
  win->begin();
  hv = new HoleView(0, kHoleViewTop, x, y, 0);
  hv->mode(FL_DOUBLE);

  boxYardage =
      new Fl_Box(FL_FRAME_BOX, 4, kBtnRow1Top, kYardageWid, kBoxSize, 0);
  boxYardage->labeltype(FL_NORMAL_LABEL);
  boxYardage->align(FL_ALIGN_CENTER);
  boxYardage->labelfont(1);
  boxYardage->labelsize(64);
  boxYardage->labelcolor(FL_BLACK);
  boxYardage->color(FL_YELLOW);

  holeBtn = new CHoleBtn(kHoleLeft, kBtnRow1Top, kHoleWid, kBoxSize);
  holeBtn->align(FL_ALIGN_CENTER);
  holeBtn->value("  H");
  holeBtn->textfont(1);
  holeBtn->textsize(48);
  // holeBtn->color(FL_GRAY);
  holeBtn->cursor_color(FL_GRAY);

  clubBtn = new CClubBtn(kClubLeft, kBtnRow1Top, kClubWid, kBoxSize, "Club");

  scoreBtn =
      new CScoreBtn(kWriteLeft, kBtnRow1Top, kWriteWid, kBoxSize, "Score");

  exitBtn = new CExitBtn(kExitLeft, kBtnRow1Top, kExitWid, kBoxSize, "Exit");
  exitBtn->mainwin = win;
  win->end();

  win->resizable(win);
  win->show();
  hv->make_current();
  hv->initHoleWindow(x, y, ngc);
  hv->makeList();
  hv->show();
  hv->draw();
#if USEGPS
  // from howto-add_fd_popen()
  if ((gpsin = popen(GPS_CMD, "r")) == NULL) {  // start the
                                                // external unix command
    perror("popen failed");
    return (1);
  }
  // setup a callback for the popen() ed descriptor
  Fl::add_fd(fileno(gpsin), HandleFD, 0);
#endif

  cout << asctime(localtime(&gToday)) << gToday << " seconds since the Epoch\n";

  // Fl::add_idle(IdleCallback, win);
  return (Fl::run());
}
