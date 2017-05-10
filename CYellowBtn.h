#ifndef CYELLOWBTN_H
#define CYELLOWBTN_H

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Window.H>

#include <string>

using namespace std;

class CYellowBtn : public Fl_Multiline_Output {
  int count;
  // Called when user finishes entering data with numeric keypad
  void yellowBtn_CB2();
  static void yellowBtn_CB(Fl_Widget *, void *data);

  void setAttributes();
  // Handle when user clicks on our input widget
  int handle(int e);

  void calcAvgHoleGPStime(const string &lbl);
  void calcRoundGPStime(const string &lbl);
  void calcGPStime(const string &lbl);

 public:
  CYellowBtn(int X, int Y, int W, int H, const char *L = 0);
  void updateGPStime();
};

extern CYellowBtn *yellowBtn;  // local instance of numeric keypad widget

#endif  // CYELLOWBTN_H
