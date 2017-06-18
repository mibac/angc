#ifndef DOUT_H
#define DOUT_H

#include <iostream>
#include <string>

using namespace std;

#define DBG 1
extern void dout1(string s1);
extern void dout2(string s1, string s2);
extern void dout3(string s1, string s2, string s3);
extern void dout4(string s1, string s2, string s3, string s4);
extern void dout5(string s1, string s2, string s3, string s4, string s5);

#endif // DOUT_H
