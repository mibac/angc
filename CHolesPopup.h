#ifndef CHOLESPOPUP_H
#define CHOLESPOPUP_H

#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>

class CHolesPopup : public Fl_Window {
  Fl_Input *in;           // input preview
  Fl_Callback *enter_cb;  // callback when user hits 'enter'
  void *enter_data;
  std::string s;

  void setBtnAttributes(Fl_Button *b);

  // Handle numeric keypad buttons pressed
  void Button_CB2(Fl_Widget *w);
  static void Button_CB(Fl_Widget *w, void *data);

 public:
  CHolesPopup(int X, int Y, int W, int H, const char *L = 0);
  // Return current value
  const char *value();
  // Clear current value
  void clear();
  // Set callback for when Enter is pressed
  void SetEnterCallback(Fl_Callback *cb, void *data);
};

#endif  // CHOLESPOPUP_H
