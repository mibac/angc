#ifndef CGPSTIME_H
#include "CGPStime.h"
#endif

CGPStime::CGPStime() : /*utc(0),*/ h(0), m(0), s(0), hs(""), ms(""), ss("") {}

CGPStime::CGPStime(string utc) {
  int len = utc.length();
  if (len < 6) {
    for (int ix = 0; ix < 6 - len; ++ix) utc = "0" + utc;
  }

  hs = utc.substr(0, 2);
  ms = utc.substr(2, 2);
  ss = utc.substr(4, 2);

  h = stoi(hs);
  m = stoi(ms);
  s = stoi(ss);
}

CGPStime::CGPStime(int seconds) {
  h = seconds / 3600;
  int tmp = seconds % 3600;
  m = tmp / 60;
  s = tmp % 60;
}

int CGPStime::seconds() { return h * 3600 + m * 60 + s; }

string prefixTm(const string &str) {
  string rtn;
  if (str.length() == 1)
    rtn = "0" + str;
  else if (str.length() == 2)
    rtn = str;
  else
    rtn = "xx";
  return rtn;
}

string CGPStime::sec2str(const int sec, const string &lbl) {
  // string utc = to_string(sec);
  // int len = utc.length();
  // if (len < 6) {
  //   for (int ix = 0; ix < 6 - len; ++ix) utc = "0" + utc;
  // }

  CGPStime tm(sec);
  string hs = to_string(tm.h);
  string ms = to_string(tm.m);
  string ss = to_string(tm.s);
  hs = prefixTm(hs);
  ms = prefixTm(ms);
  ss = prefixTm(ss);

  string s;
  if (hs == "00")
    s = lbl + ms + ":" + ss;
  else
    s = lbl + hs + ":" + ms + ":" + ss;
  return s;
}

int CGPStime::timeDifference(string s1, string s2) {
  // t1 >= t2
  CGPStime t1(s1);
  CGPStime t2(s2);
  int t1sec = t1.seconds();
  int t2sec = t2.seconds();
  int diff;
  if (t1sec >= t2sec)
    diff = t1.seconds() - t2.seconds();
  else
    diff = t2.seconds() - t1.seconds();
  return diff;
}
