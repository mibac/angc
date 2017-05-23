#ifndef CGPSTIME_H
#define CGPSTIME_H

#include <string>

using namespace std;

class CGPStime {
 public:
  CGPStime();
  CGPStime(string utc);
  CGPStime(int seconds);

  ~CGPStime() = default;
  CGPStime(const CGPStime& other) = default;
  CGPStime(CGPStime&& other) = default;
  CGPStime& operator=(const CGPStime& other) = default;
  CGPStime& operator=(CGPStime&& other) = default;

  int h;
  int m;
  int s;
  string hs;
  string ms;
  string ss;

  int seconds();
  int timeDifference( string t1,  string t2); // t1 >= t2
  string sec2str(const int sec, const string& lbl);
};

#endif  // CGPSTIME_H
