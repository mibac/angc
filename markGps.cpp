/* je compile command
goodby
g++ markGps.cpp gps.cpp calcDist.cpp -o _NGCApp -g  -I/usr/include/cairo
-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
-I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12
-D_LARGEFILE_SOURCE -D_LARGEFILE64 -std=c++11 -lfltk -lgps
*/

// Demonstrate how to use Fl_Input in a touchscreen application -erco 08/25/06

#include <unistd.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Timer.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

#ifndef HOLEVIEW_H_
#include "HoleView.hpp"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

#ifndef GPS_H
#include "gps.h"
#endif

#ifndef _GPSD_GPSMM_H_
#include "libgpsmm.h"
#endif

#ifndef C2UTM_hpp
#include "C2UTM.hpp"
#endif

#ifndef CHOLESPOPUP_H
#include "CHolesPopup.h"
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

#ifndef CMARKBTN_H
#include "CMarkBtn.h"
#endif

#ifndef CWRITEMARKBTN_H
#include "CWriteMarkBtn.h"
#endif

#ifndef CWRITEALLBTN_H
#include "CWriteAllBtn.h"
#endif

using namespace std;

// Conditionals
#define USEGPS 1

// GLOBALS
const int WAITING_TIME = 5000000;
const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;
const int kNumMarks = 10;

int oldvGPGGAsz = 0;
int nowvGPGGAsz = 0;
int currentHole = 1;

float refMarkf = 0.0;
float nowMarkf = 0.0;

struct LatLng {
  double lat;
  double lng;
};

LatLng currentRefMarker;

Fl_Window *win;
Fl_Input *my_input;
Fl_Box *boxYardage;
Fl_Button *btnMark;
Fl_Button *btnWrite;
MyInput *in;
CMarkBtn *markBtn;
CWriteMarkBtn *writeMarkBtn;
CWriteAllBtn *writeAllBtn;

FILE *G_fp = NULL;
const char *SIMPLEGPS_CMD = "simplegps";

string strDistFromMark("0");

vector<string> vGPGGA;
vector<string> vMarkers;

GPS myGPS;

HoleView *hv;
Course *ngc;

// Prototypes
void setupYardage(string s);
string getFilename();

// string getHoleName() {
//   string str;
//   if (vbtn[kBtn1]->value() == 1)
//     str = vbtn[kBtn1]->label();
//   else if (vbtn[kBtn2]->value() == 1)
//     str = vbtn[kBtn2]->label();
//   else if (vbtn[kBtn3]->value() == 1)
//     str = vbtn[kBtn3]->label();
//   else if (vbtn[kBtn4]->value() == 1)
//     str = vbtn[kBtn4]->label();
//   else if (vbtn[kBtn5]->value() == 1)
//     str = vbtn[kBtn5]->label();
//   else if (vbtn[kBtn6]->value() == 1)
//     str = vbtn[kBtn6]->label();
//   else if (vbtn[kBtn7]->value() == 1)
//     str = vbtn[kBtn7]->label();
//   else if (vbtn[kBtn8]->value() == 1)
//     str = vbtn[kBtn8]->label();
//   else if (vbtn[kBtn9]->value() == 1)
//     str = vbtn[kBtn9]->label();
//   else if (vbtn[kBtn10]->value() == 1)
//     str = vbtn[kBtn10]->label();
//   else if (vbtn[kBtn11]->value() == 1)
//     str = vbtn[kBtn11]->label();
//   else if (vbtn[kBtn12]->value() == 1)
//     str = vbtn[kBtn12]->label();
//   else if (vbtn[kBtn13]->value() == 1)
//     str = vbtn[kBtn13]->label();
//   else if (vbtn[kBtn14]->value() == 1)
//     str = vbtn[kBtn14]->label();
//   else if (vbtn[kBtn15]->value() == 1)
//     str = vbtn[kBtn15]->label();
//   else if (vbtn[kBtn16]->value() == 1)
//     str = vbtn[kBtn16]->label();
//   else if (vbtn[kBtn17]->value() == 1)
//     str = vbtn[kBtn17]->label();
//   else if (vbtn[kBtn18]->value() == 1)
//     str = vbtn[kBtn18]->label();
//   return str;
// }
//
// string getMarkerName() {
//   string str;
//   if (vbtn[kBtnT]->value() == 1)
//     str = "Tee";
//   else if (vbtn[kBtnM]->value() == 1)
//     str = "150";
//   else if (vbtn[kBtnG]->value() == 1)
//     str = "Green";
//   return str;
// }

// #if USEGPS
// void setRefMarker() {
//   LatLng ll;
//   ll.lat = 0;
//   ll.lng = 0;
//   size_t n = 10;
//
//   vector<string> v(vGPGGA.end() - std::min(vGPGGA.size(), n), vGPGGA.end());
//
//   for (auto itr : v) {
//     if (myGPS.isValidGGA(itr)) {
//       myGPS.setValuesGGA(itr);
//       ll.lat += myGPS.latitude;
//       ll.lng += myGPS.longitude;
//     }
//   }
//
//   ll.lat /= v.size();
//   ll.lng /= v.size();
//   ostringstream oss;
//   oss << "Lat: " << ll.lat << " Lng: " << ll.lng << " GGAs: " <<
//   vGPGGA.size()
//       << " MKRs: " << v.size();
//   my_input->value(oss.str().c_str());
//   vMarkers = v;
//   currentRefMarker = ll;
// }
// #endif
//
// static void updateYardage(string s) {
//   boxYardage->label(s.c_str());
//   boxYardage->redraw();
// }
//
// static void updateYardage(double d) {
//   ostringstream oss;
//   unsigned int ui = static_cast<unsigned int>(d);
//   oss << ui;
//   updateYardage(oss.str().c_str());
// }
//
// void handleWriteMarker() {
// #if USEGPS
//   string fname = getFilename();
//   if (fname.empty()) return;
//
//   ofstream file(fname.c_str());
//   for (auto itr : vMarkers) file << itr;
//   file.close();
//   vMarkers.clear();
//
//   string s = fname + " written";
//   my_input->value(s.c_str());
// #endif
// }
//
// void handleWriteAll() {
// #if USEGPS
//   string fname = "WalkTheCourse.txt";
//
//   ofstream file(fname.c_str());
//   for (auto itr : vGPGGA) file << itr;
//   file.close();
//
//   string s = fname + " written";
//   my_input->value(s.c_str());
// #endif
// }
//
// string getFilename() {
//   string fname = "";
//   string h = getHoleName();
//   string m = getMarkerName();
//
//   if (h.empty()) {
//     my_input->value("Select a hole. Try again");
//   } else if (m.empty()) {
//     my_input->value("Select a marker: T M G. Try again");
//   } else {
//     fname = getHoleName() + "_" + getMarkerName() + ".txt";
//   }
//   return fname;
// }
//
// #if USEGPS
// gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
//
// bool isgpsup() {
//   bool ok = false;
//   for (int i = 0; i < 5; ++i) {
//     // For version 3.7
//
//     if (gps_rec.stream(WATCH_ENABLE | WATCH_NMEA) == NULL) {
//       cout << "No GPSD running. Retry to connect in " << RETRY_TIME
//            << " seconds." << endl;
//       usleep(RETRY_TIME * ONE_SECOND);
//       continue;  // It will try to connect to gpsd again
//     } else {
//       ok = true;
//     }
//   }
//   return ok;
// }
//
// double NMEA2DecimalDegrees(double nmea) {
//   double deg = double(int(nmea / 100));
//   double min = nmea - (deg * 100);
//   double minOver60 = min / 60.0;
//   double dec_deg = deg + minOver60;
//   cout << fixed << setprecision(9);
//   //	cout << "nmea\t" << nmea << "\t" << deg << "\t" << min << "\t" <<
//   // dec_deg << endl;
//   return dec_deg;
// }
//
// void updateDistanceFromMarkerUTM(string strCurrent, const LatLng rLL) {
//   // C2UTM method
//   LL2UTM latlon;   //	JACK C2UTM
//   LL2UTM rlatlon;  //	r for reference
//   double rlt, lt;
//   double rlg, lg;
//   double d;
//
//   if (nowvGPGGAsz == oldvGPGGAsz) return;
//   if (myGPS.isValidGGA(strCurrent)) {
//     myGPS.setValuesGGA(strCurrent);
//
//     rlt = NMEA2DecimalDegrees(rLL.lat);
//     rlg = NMEA2DecimalDegrees(-rLL.lng);
//     rlatlon.setLatLon(rlt, rlg);
//     rlatlon.convert2UTM();
//
//     lt = NMEA2DecimalDegrees(myGPS.latitude);
//     lg = NMEA2DecimalDegrees(-myGPS.longitude);
//     latlon.setLatLon(lt, lg);
//     latlon.convert2UTM();
//
//     d = sqrt(pow(-(latlon.UTMEast - rlatlon.UTMEast), 2) +
//              pow(latlon.UTMNorth - rlatlon.UTMNorth, 2));
//     d *= 1.0936139;  // meters to yards
//     updateYardage(d);
//     oldvGPGGAsz = nowvGPGGAsz;
//   }
// }
//#endif

// Handler for add_fd() -- called whenever the simplegps command outputs a new
// line of data Note: FL_SOCKET as 1st argument is used to fix a compiler
// error(!) on Windows 64-bit. Unfortunately we need this in FLTK 1.3 -should
// hopefully be fixed in 1.4 with a better solution.
void HandleFD(FL_SOCKET fd, void *data) {
  char s[1024];
  string str;

  if (fgets(s, 1023, G_fp) == NULL) {  // read the line of data
    Fl::remove_fd(fileno(G_fp));       // command ended? disconnect callback
    pclose(G_fp);                      // close the descriptor
    return;
  }
  str = s;
  vGPGGA.push_back(str);
  nowvGPGGAsz = vGPGGA.size();
  // updateDistanceFromMarkerUTM(str, currentRefMarker);
}

void IdleCallback(void *pData) {
  int n = atoi(in->value());
  if (currentHole != n) {
    hv->redraw();
    currentHole = n;
  }
}

int main(int argc, char **argv) {
  //#if USEGPS
  //    if (isgpsup() == false) {
  //   	cout << "No GPS found" << endl;
  //   	return 0;
  //  }
  //#endif
  const int kBoxSize = 80;

  ngc = new Course(9);
  ngc->readCourse();

  int x, y;
  cout << "Enter width and height of hole window" << endl;
  cout << "280<= width<=470  and 400<= height <= 700" << endl;
  cin >> x >> y;
  win = new Fl_Window(10, 40, 480, 800, "NGC Golf");
  win->begin();
  hv = new HoleView(0, 0, x, y, 0);

  boxYardage = new Fl_Box(FL_FRAME_BOX, 4, 676, kBoxSize * 2, kBoxSize, 0);
  boxYardage->labeltype(FL_NORMAL_LABEL);
  boxYardage->align(FL_ALIGN_CENTER);
  boxYardage->labelfont(1);
  boxYardage->labelsize(64);
  boxYardage->labelcolor(FL_BLACK);
  boxYardage->color(FL_YELLOW);
  //    updateYardage(strDistFromMark);

  in = new MyInput(170, 676, 100, 30);
  in->value("-click here-");

  markBtn = new CMarkBtn(280, 676, 80, 40, "Mark");
  writeMarkBtn = new CWriteMarkBtn(280, 720, 80, 40, "Write\nMark");
  writeAllBtn = new CWriteAllBtn(366, 676, 80, 40, "Write\nAll");

  win->end();

  win->resizable(win);
  win->show();
  // hv->currentHole = 1; //JE
  hv->make_current();
  hv->initHoleWindow(x, y, ngc);
  hv->makeList();
  hv->show();
  hv->draw();
#if USEGPS
  // from howto-add_fd_popen()
  if ((G_fp = popen(SIMPLEGPS_CMD, "r")) == NULL) {  // start the
                                                     // external unix command
    perror("popen failed");
    return (1);
  }
  // setup a callback for the popen() ed descriptor
  Fl::add_fd(fileno(G_fp), HandleFD, 0);
#endif

  Fl::add_idle(IdleCallback, win);
  return (Fl::run());
}
