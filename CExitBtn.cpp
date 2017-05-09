#ifndef CEXITBTN_H
#include "CExitBtn.h"
#endif

#include <iomanip>

#include <FL/fl_ask.H>

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef UTILS_H
#include "utils.h"
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

#ifndef CSCORESTATS_H
#include "CScoreStats.h"
#endif

using namespace std;

const string path = "/home/pi/golf/angc/";

void CExitBtn::setFileSuffix() {
  ostringstream oss;
  oss << gToday;
suffix = oss.str() + ".txt";
}

void CExitBtn::writeGPS() {
  string s = path + "aGPS_" + suffix;
  gFileGPS.open(s.c_str());
  gFileGPS << setprecision(kPrecision);
  for (auto itr : vGPS) gFileGPS << itr;
  gFileGPS.close();
}

void CExitBtn::writeClubsUsed() {
  string s = path + "aClubs_" + suffix;
  gFileClub.open(s.c_str());
  gFileClub << setprecision(kPrecision);
  for (auto itr : vClubsUsed) gFileClub << itr;
  gFileClub.close();
}

void CExitBtn::writeStats() {
  string s = path + "aStats_" + suffix;
  gFileStats.open(s.c_str());
  for (auto itr : cStats.statsRA) gFileStats << itr;
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
