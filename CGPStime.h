#ifndef CGPSTIME_H
#define CGPSTIME_H

#include <string>

using namespace std;

class CGPStime 
{
public:
    CGPStime();
    CGPStime(int);

    ~CGPStime() = default;
    CGPStime(const CGPStime& other) = default;
    CGPStime(CGPStime&& other) = default;
    CGPStime& operator=(const CGPStime& other) = default;
    CGPStime& operator=(CGPStime&& other) = default;

    int utc;
    int h;
    int m;
    int s;

   int seconds();
   string sec2str(const int sec, const string &lbl);

};

#endif // CGPSTIME_H
