#ifndef DOUT_H
#include "dout.h"
#endif


#if DBG
void dout1(string s1) {
  cout << s1 << endl;
}
void dout2(string s1, string s2) {
  cout << s1 << " " << s2 << endl;
}
void dout3(string s1, string s2, string s3) {
  cout << s1 << " " << s2 << " " << s3 << endl;
}
void dout4(string s1, string s2, string s3, string s4) {
  cout << s1 << " " << s2 << " " << s3 << " " << s4 << endl;
}
void dout5(string s1, string s2, string s3, string s4, string s5) {
  cout << s1 << " " << s2 << " " << s3 << " " << s4 << " " << s5 << endl;
}
#else
void dout1(string s1) { ; }
void dout2(string s1, string s2) { ; }
void dout3(string s1, string s2, string s3) { ; }
void dout4(string s1, string s2, string s3, string s4) { ; }
void dout5(string s1, string s2, string s3, string s4, string s5) { ; }
#endif
