#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#include <iomanip>

#include <FL/fl_ask.H>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#ifndef CHOLEBUTTON_H
#include "CHoleBtn.h"
#endif

#ifndef CCLUBBTN_H
#include "CClubBtn.h"
#endif

using namespace std;

const string path = "/home/pi/golf/angc/stats/";

void CExitBtn::setFileSuffix() {
  ostringstream oss;
  struct tm * t;
  t = localtime(&gToday);
  string y = to_string(t->tm_year - 100);
  string m = to_string(t->tm_mon);
  if (m.length() == 1)
    m = "0" + m;
  string d = to_string(t->tm_mday);
  if (d.length() == 1)
    d = "0" + d;
  suffix =  y + m + d + ".txt";
}

void CExitBtn::writeGPS() {
  string s = path + "aGPS_" + suffix;
  gFileGPS.open(s.c_str());
  gFileGPS << setprecision(kPrecision);
  gFileGPS << asctime(std::localtime(&gToday));
  for (auto itr : vGPS) gFileGPS << itr;
  gFileGPS.close();
}

void CExitBtn::writeClubsUsed() {
  string s = path + "aClubs_" + suffix;
  gFileClub.open(s.c_str());
  gFileClub << setprecision(kPrecision);
  gFileClub << asctime(std::localtime(&gToday));
  for (auto itr : vClubsUsed) gFileClub << itr;
  gFileClub.close();
}

void CExitBtn::writeStats() {
  string s = path + "aStats_" + suffix;
  gFileStats.open(s.c_str());
  gFileStats << asctime(std::localtime(&gToday));
  for (auto itr : vNGCHoles) gFileStats << itr;
  gFileStats.close();
}

void CExitBtn::setBtnAttributes(Fl_Button *b) {
  b->labelfont(1);
  b->labelsize(24);
  b->color(FL_WHITE);
  b->down_color(FL_YELLOW);
}

void CExitBtn::Button_CB() {
  int result = fl_choice("Do you want to save before quitting?",
                         "Don't Save",  // 0
                         "Save",        // 1
                         "Cancel"       // 2
                         );
  if (result == 0) {  // Close without saving
    gFileClub.close();
    gFileStats.close();
    gFileGPS.close();
    if (myClubPopup != nullptr) myClubPopup->hide();
    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 1) {  // Save and close
    writeGPS();
    writeClubsUsed();
    writeStats();
    if (myClubPopup != nullptr) myClubPopup->hide();
    if (myHolePopup != nullptr) myHolePopup->hide();
    if (gpsin != nullptr) pclose(gpsin);
    mainwin->hide();
  } else if (result == 2) {  // Cancel / don't close
                             // don't do anything
  }
}

// Handle numeric keypad buttons pressed
void CExitBtn::staticButton_CB(Fl_Widget *, void *data) {
  CExitBtn *ceb = (CExitBtn *)data;
  ceb->Button_CB();
}

CExitBtn::CExitBtn(int X, int Y, int W, int H, const char *L)
    : Fl_Button(X, Y, W, H, L) {
  setBtnAttributes(this);
  setFileSuffix();
  callback(staticButton_CB, (void *)this);
}
