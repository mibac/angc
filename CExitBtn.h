#ifndef CEXITBTN_H
#define CEXITBTN_H

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

using namespace std;

class CExitBtn : public Fl_Button {
  string suffix;
  void setFileSuffix();
  void setBtnAttributes(Fl_Button *b);
  void writeGPS();
  void writeClubsUsed();
  void writeStats();

  // Handle numeric keypad buttons pressed
  static void staticButton_CB(Fl_Widget *w, void *data);

 public:
  Fl_Window *mainwin;

  void Button_CB();
  CExitBtn(int X, int Y, int W, int H, const char *L = 0);
};

extern CExitBtn *exitBtn;
extern FILE *gpsin;

#endif  // CEXITBTN_H
