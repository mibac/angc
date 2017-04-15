#ifndef HOLEVIEW_H_
#define HOLEVIEW_H_

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>

class HoleView: public Fl_Gl_Window {
 public:
   HoleView(int x,int y,int w,int h,const char *l):Fl_Gl_Window(x,y,w,h,l){}
   void makeList();
   void draw();
   
   int hole;
};

#endif