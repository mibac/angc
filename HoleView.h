#ifndef HOLEVIEW_H_
#define HOLEVIEW_H_

#include <FL/Fl.H>

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
   void makeZoomButtonList();
   void makeGreenButtonList();
   void makeMarkPointList(int h);
   void makeZoomList(int h);
   void initHoleWindow(int x, int y,Course *course);
   void draw();
   bool insideZoomButton(double x,double y);
   bool insideGreenButton(double x,double y);
   int handle(int e);
   int xres,yres; //JE
   double zoomButtonX,zoomButtonY,zoomButtonS;
   double greenButtonX,greenButtonY,greenButtonS;
   double xPressed,yPressed,xReleased,yReleased;
   Vector UTMFromZoomPixelCoord(double x, double y);
   Vector ZoomPixelCoordFromUTM(Vector utm);
   Vector UTMFromGreenPixelCoord(double x, double y);
   Course *ngc;
};

#endif
