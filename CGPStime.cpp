#ifndef CGPSTIME_H
#include "CGPStime.h"
#endif

CGPStime::CGPStime() : utc(0), h(0), m(0), s(0) {}

CGPStime::CGPStime(int tm) {
  string stm = to_string(tm);
  int len = stm.length();
  if (len < 6) {
    for (int ix = 0; ix < 6 - len; ++ix) stm = "0" + stm;
  }

  string hs = stm.substr(0, 2);
  string ms = stm.substr(2, 2);
  string ss = stm.substr(4, 2);

  h = stoi(hs);
  m = stoi(ms);
  s = stoi(ss);
}

int CGPStime::seconds() { return h * 3600 + m * 60 + s; }

string CGPStime::sec2str(const int sec, const string &lbl) {
  string stm = to_string(sec);
  int len = stm.length();
  if (len < 6) {
    for (int ix = 0; ix < 6 - len; ++ix) stm = "0" + stm;
  }

  string hs = stm.substr(0, 2);
  string ms = stm.substr(2, 2);
  string ss = stm.substr(4, 2);

  string s;
  if (hs == "00")
    s = lbl + ms + ":" + ss;
  else
    s = lbl + hs + ":" + ms + ":" + ss;
  return s;
}
