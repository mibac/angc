#ifndef HOLEVIEW_H_
#define HOLEVIEW_H_

#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include "Course.h"

class HoleView: public Fl_Gl_Window {
 public:
   HoleView(int x,int y,int w,int h,const char *l):Fl_Gl_Window(x,y,w,h,l){}
   void makeList();
   void makeCurrentHoleList(int h);
   void makeCurrentPointList(int h);
   void makeCurrentGreenList(int h);
   void initHoleWindow(int x, int y,Course *course);
   void draw();
   int xres,yres; //JE
   Course *ngc;
};

#endif
