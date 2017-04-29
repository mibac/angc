/* je compile command
goodby
g++ markGps.cpp gps.cpp calcDist.cpp -o _NGCApp -g  -I/usr/include/cairo
-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
-I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12
-D_LARGEFILE_SOURCE -D_LARGEFILE64 -std=c++11 -lfltk -lgps
*/

// Demonstrate how to use Fl_Output in a touchscreen application -erco 08/25/06

/*   CHANGE LOG
        4/17/17 JE: revised nmea2DecimalDegrees. Checked with Google Maps
                                added functions to show nmea, decimal degrees,
   and UTM in file output.

*/
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
#include "CHoleButton.h"  //MyInput *in
#endif

// #ifndef CMARKBTN_H
// #include "CMarkBtn.h"
// #endif

// #ifndef CWRITEMARKBTN_H
// #include "CWriteMarkBtn.h"
// #endif

#ifndef CCLUBBTN_H
#include "CClubBtn.h"
#endif

#ifndef CWRITEALLBTN_H
#include "CWriteAllBtn.h"
#endif

#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

using namespace std;

// Conditionals
#define USEGPS 1

// GLOBALS
int pathStep = 0;

Fl_Window *win;
Fl_Output *my_input;
Fl_Box *boxYardage;
Fl_Button *btnMark;
Fl_Button *btnWrite;
MyInput *in;
// CMarkBtn *markBtn;
// CWriteMarkBtn *writeMarkBtn;
CClubBtn *clubBtn;
CWriteAllBtn *writeAllBtn;
CExitBtn *exitBtn;

// FILE *G_fp = NULL;
// const char *GPS_CMD = "simplegps";
const char *GPS_CMD = "gpspipe -r /dev/ttyACM0";

// USB GPS
FILE *gpsin;
///

vector<string> vGPGGA;
vector<string> vMarkers;

HoleView *hv;
Course *ngc;

// Handler for add_fd() -- called whenever the simplegps command outputs a new
// line of data Note: FL_SOCKET as 1st argument is used to fix a compiler
// error(!) on Windows 64-bit. Unfortunately we need this in FLTK 1.3 -should
// hopefully be fixed in 1.4 with a better solution.
// #if USEGPS
// void HandleFD(FL_SOCKET fd, void *data) {
//   const int bufSz = 1023;
//   char chRA[bufSz + 1];
//
//   if (fgets(chRA, bufSz, G_fp) == NULL) {  // read the line of data
//     Fl::remove_fd(fileno(G_fp));           // command ended? disconnect
//     callback pclose(G_fp);                          // close the descriptor
//     return;
//   }
//   string s(chRA);
//   cll.updateLatLng(s.c_str());
//   cll.updateDistanceFromMarkerUTM(boxYardage);
// }
// #endif

#if USEGPS
void HandleFD(FL_SOCKET fd, void *data) {
  const int bufSz = 1023;
  char chRA[bufSz + 1];

  int n = atoi(in->value());
  if (n == 0) n = 1;
  if (CLatLng::currentHole != n) {
    // hv->redraw();
    CLatLng::currentHole = n;
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
      // cout << "In IdleCallback: " << s << endl;
      UtmLatLng u = cll.getNowMark();
      hv->ngc->hole[CLatLng::currentHole].setCurrentPoint(u.lng, u.lat);
      hv->redraw();
    }
  }
}
#endif

// void IdleCallback(void *pData) {
//   int n = atoi(in->value());
//   if (n == 0) n = 1;
//   if (currentHole == n) {
//     hv->ngc->hole[currentHole].setCurrentPoint(0.001);
//     hv->redraw();
//   } else {
//     hv->redraw();
//     currentHole = n;
//   }
// }

const int kBUFSIZE = 1024;
char gpsBuf[kBUFSIZE];
void clearGpsBuf() {
  for (int ix = 0; ix < kBUFSIZE; ++ix) gpsBuf[ix] = '\0';
}

void IdleCallback(void *pData) {
  int n = atoi(in->value());
  if (n == 0) n = 1;
  if (CLatLng::currentHole != n) {
    // hv->redraw();
    CLatLng::currentHole = n;
  }

  /*
     if (currentHole==n) {
       if (currentHole==3) {
        Vector cp = hv->ngc->hole[currentHole].pathPoint[pathStep];
         hv->ngc->hole[currentHole].setCurrentPoint(cp.v[0],cp.v[1]);
         pathStep++;
         if (pathStep>hv->ngc->hole[currentHole].pathPointNum) pathStep=0;
         sleep(0.5);
         hv->redraw();
        }
     }
  */
  clearGpsBuf();
  if (fgets(gpsBuf, sizeof(gpsBuf), gpsin) != NULL) {
    string gpsStr(gpsBuf);
    size_t found = gpsStr.find("GPGGA");
    // size_t found = s.find("GPGLL");
    if (found != string::npos) {
      cll.updateLatLng(gpsStr.c_str());
      string s = cll.distanceFromLastMark();
      boxYardage->label(s.c_str());
      // cout << "In IdleCallback: " << s << endl;
      UtmLatLng u = cll.getNowMark();
      hv->ngc->hole[CLatLng::currentHole].setCurrentPoint(u.lng, u.lat);
      hv->redraw();
    }
  }

  usleep(100000);  // microseconds or idle called 10x second
}

// This window callback allows the user to save & exit, don't save, or
// cancel.
static void window_cb(Fl_Widget *widget, void *) {
  Fl_Window *window = (Fl_Window *)widget;

  // fl_choice presents a modal dialog window with up to three choices.
  myClubPopup->hide();
  numpad->hide();
  window->hide();
}

int main(int argc, char **argv) {
#if USEGPS
  // if (cll.isgpsup() == false) {
  //   cout << "No GPS found" << endl;
  //   return 0;
  // }
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

  in = new MyInput(kHoleLeft, kBtnRow1Top, kHoleWid, kBoxSize);
  in->align(FL_ALIGN_CENTER);
  in->value("Hole");
  in->textfont(1);
  in->textsize(30);
  // in->color(FL_GRAY);
  in->cursor_color(FL_GRAY);

  // markBtn = new CMarkBtn(280, kBtnRow1Top, kBoxSize, kBoxSize / 2,
  // "Mark"); markBtn->holeview = hv;
  clubBtn = new CClubBtn(kClubLeft, kBtnRow1Top, kClubWid, kBoxSize, "Club");

  writeAllBtn = new CWriteAllBtn(kWriteLeft, kBtnRow1Top, kWriteWid, kBoxSize,
                                 "Write\nAll");

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

  // Fl::add_idle(IdleCallback, win);
  return (Fl::run());
}
