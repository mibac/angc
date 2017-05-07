#ifndef HOLEVIEW_H_
#include "HoleView.h"
#endif

#ifndef CGLOBALS_H
#include "globals.h"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
#endif

#define ORIENTATION 0
#define TEEBOX 1
#define FAIRWAY 2
#define GREEN 301
#define TRAPGREEN 302
#define TRAP 4
#define TREES 5
#define WATER 6
#define TEEAREA 7
#define CARTPATH 21
#define OB 22
#define HOUSE 31
#define STREET 32
#define DRIVEWAY 33

#define FULLVIEW 0
#define GREENVIEW 1
#define ZOOMVIEW 2

#define ZOOMLIST 100
#define GREENLIST 200
#define CURRENTPOINTLIST 300
#define ZOOMBUTTONLIST 400
#define GREENBUTTONLIST 500
#define MARKPOINTLIST 600

void HoleView::initHoleWindow(int x,int y,Course *course) {
  xres = x;
  yres = y;
  ngc = course;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D((double) 0 ,(double) x, (double) 0, (double) y);
  glMatrixMode(GL_MODELVIEW);
}

void HoleView::makeCurrentPointList(int h) {
     double xp,yp;
     const char *sh, *st;

        ngc->hole[h].computeYardageToHole();
        ngc->hole[h].computeYardageFromTee();
        ngc->hole[h].rotCurrentPoint = ngc->hole[h].rotatePoint(ngc->hole[h].currentPoint,ngc->hole[h].currentUnit);
        glDeleteLists(h+CURRENTPOINTLIST,1);
        glNewList(h+CURRENTPOINTLIST,GL_COMPILE);
        glPointSize(16.0);
        glBegin(GL_POINTS);
          glColor3f(1.0,0.0,0.0);
          xp = ngc->hole[h].scale*(ngc->hole[h].rotCurrentPoint.v[0]-ngc->hole[h].xminmax.v[0]);
          yp = ngc->hole[h].scale*(ngc->hole[h].rotCurrentPoint.v[1]-ngc->hole[h].yminmax.v[0]);
          xp += ngc->hole[h].xtran;
          yp += 2*ngc->hole[h].ytran;
           if (ngc->hole[h].viewType==ZOOMVIEW) {
                xp = xp*ngc->hole[h].zoomScale;
                yp = yp*ngc->hole[h].zoomScale;
                xp = xp+xres/2.0-ngc->hole[h].zoomScale*xPressed;
                yp = yp+yres/2.0-ngc->hole[h].zoomScale*yPressed;
           }
          glVertex2d(xp,yp);
        glEnd();
          glColor3f(0.0,0.0,0.0);
        gl_font(FL_HELVETICA_BOLD,48);
        sh = ngc->hole[h].currentYardageToHoleStr.c_str();
        st = ngc->hole[h].currentYardageFromTeeStr.c_str();
        gl_draw(sh,(float) 10.0,(float)(yp));
        gl_draw(st,(float) 380.0,(float)(yp));
        glFlush();
        glEndList();
}

void HoleView::makeMarkPointList(int h) {
     double xp,yp;
     Vector rot;
     const char *sm;
     string s;

      rot = ngc->hole[h].rotatePoint(ngc->hole[h].markPoint,ngc->hole[h].currentUnit);
        glDeleteLists(h+MARKPOINTLIST,1);
        glNewList(h+MARKPOINTLIST,GL_COMPILE);
        glPointSize(16.0);
        glBegin(GL_POINTS);
          glColor3f(1.0,0.0,0.0);
          xp = ngc->hole[h].scale*(rot.v[0]-ngc->hole[h].xminmax.v[0]);
          yp = ngc->hole[h].scale*(rot.v[1]-ngc->hole[h].yminmax.v[0]);
          xp += ngc->hole[h].xtran;
          yp += 2*ngc->hole[h].ytran;
           if (ngc->hole[h].viewType==ZOOMVIEW) {
                xp = xp*ngc->hole[h].zoomScale;
                yp = yp*ngc->hole[h].zoomScale;
                xp = xp+xres/2.0-ngc->hole[h].zoomScale*xPressed;
                yp = yp+yres/2.0-ngc->hole[h].zoomScale*yPressed;
           }
          glVertex2d(xp,yp);
        glEnd();

        glColor3f(0.0,0.0,0.0);
        gl_font(FL_HELVETICA_BOLD,48);
        
        int yard = (int) ngc->hole[h].yardDistance(ngc->hole[h].markPoint,ngc->hole[h].currentPoint);
        s = to_string(yard); 
        sm = s.c_str();
        gl_draw(sm,(float) (xp-100),(float)(yp));

        glFlush();
        glEndList();
}

void HoleView::makeZoomButtonList() {

     zoomButtonX = 5.0; zoomButtonY = yres-90; zoomButtonS = 80;
     glDeleteLists(ZOOMBUTTONLIST,1);
     glNewList(ZOOMBUTTONLIST,GL_COMPILE);
        glBegin(GL_POLYGON);
          glColor3f(1.0,1.0,1.0);
          glVertex2d(zoomButtonX,zoomButtonY);
          glVertex2d(zoomButtonX+zoomButtonS,zoomButtonY);
          glVertex2d(zoomButtonX+zoomButtonS,zoomButtonY+zoomButtonS);
          glVertex2d(zoomButtonX,zoomButtonY+zoomButtonS);
        glEnd();
        gl_font(FL_HELVETICA_BOLD,32);
        glColor3f(0.0,0.0,0.0);
        if (ngc->hole[gCurrentHole].viewType==FULLVIEW) 
           gl_draw("Z",(float) (zoomButtonX+0.25*zoomButtonS), (float) (zoomButtonY+0.25*zoomButtonS));
        else
           gl_draw("F",(float) (zoomButtonX+0.25*zoomButtonS), (float) (zoomButtonY+0.25*zoomButtonS));
        glFlush();
      glEndList();
} 
     
void HoleView::makeGreenButtonList() {

     greenButtonX = xres-90; greenButtonY = yres-90; greenButtonS = 80;
     glDeleteLists(GREENBUTTONLIST,1);
     glNewList(GREENBUTTONLIST,GL_COMPILE);
        glBegin(GL_POLYGON);
          glColor3f(1.0,1.0,1.0);
          glVertex2d(greenButtonX,greenButtonY);
          glVertex2d(greenButtonX+greenButtonS,greenButtonY);
          glVertex2d(greenButtonX+greenButtonS,greenButtonY+greenButtonS);
          glVertex2d(greenButtonX,greenButtonY+greenButtonS);
        glEnd();
        gl_font(FL_HELVETICA_BOLD,32);
        glColor3f(0.0,0.0,0.0);
        if (ngc->hole[gCurrentHole].viewType==FULLVIEW) 
           gl_draw("G",(float) (greenButtonX+0.25*greenButtonS), (float) (greenButtonY+0.25*greenButtonS));
        else
           gl_draw("F",(float) (greenButtonX+0.25*greenButtonS), (float) (greenButtonY+0.25*greenButtonS));
        glFlush();
      glEndList();
} 
     
void HoleView::makeCurrentHoleList(int h) {
     int i,k,j;
     double x[100],y[100],xscale,yscale,xcen,ycen;
     double xsize,ysize;
     double x1,y1,dd;

      x1 = ngc->hole[h].gd.Pin.v[0]-ngc->hole[h].startOrient[0].v[0];
      y1 = ngc->hole[h].gd.Pin.v[1]-ngc->hole[h].startOrient[0].v[1];
      dd = sqrt(x1*x1+y1*y1);
      ngc->hole[h].currentUnit.v[0] = x1/dd;
      ngc->hole[h].currentUnit.v[1] = y1/dd;
      ngc->hole[h].rotateHoleToOrientation();
      ngc->hole[h].rotCurrentPoint =
                     ngc->hole[h].rotatePoint(ngc->hole[h].currentPoint,ngc->hole[h].currentUnit);
      ngc->hole[h].findMinMax();

      xsize = ngc->hole[h].xminmax.v[1]-ngc->hole[h].xminmax.v[0];
      ysize = ngc->hole[h].yminmax.v[1]-ngc->hole[h].yminmax.v[0];
      xscale = xres/xsize;
      yscale = yres/ysize;
      ngc->hole[h].scale = xscale;
      if (yscale<ngc->hole[h].scale) ngc->hole[h].scale = yscale;

      xcen = ngc->hole[h].scale*xsize/2.0;
      ycen = ngc->hole[h].scale*ysize/2.0;
      ngc->hole[h].xtran = xres/2.0-xcen;
      ngc->hole[h].ytran = yres/2.0-ycen;
      glDeleteLists(h,1);
      glNewList(h,GL_COMPILE);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glEnable(GL_LINE_SMOOTH);
         glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
         for (k=0;k<ngc->hole[h].featureNum;k++) {
            for (j=0;j<ngc->hole[h].feature[k].polyNum;j++) {
              switch (ngc->hole[h].feature[k].featureType) {
                case TEEBOX:  glColor3d(76.0/255.0,155.0/255.0,0.0);  // Tee Box
                    break;
                case FAIRWAY:  glColor3d(102.0/255.0,204.0/255.0,0.0);  // Fairway
                    break;
                case GREEN:glColor3d(0.0,204.0/255.0,0.0);    // Green
                    break;
                case TRAP: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
                case TRAPGREEN: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
                case TREES: glColor3d(0.0,102.0/255.0,0.0);   // Trees
                    break;
                case WATER: glColor3d(51.0/255.0,153.0/255.0,1.0);   // Water
                    break;
                case TEEAREA: glColor4d(38.0/255.0,73.0/255.0,0.0,0.2);   // Tee Area
                    break;
                case CARTPATH: glColor4d(0.0,0.0,0.0,0.55);  // Cart Path
                    break;
                case OB: glColor4d(1.0,1.0,1.0,1.0);  // OB
                    break;
                case HOUSE: glColor3d(1.0,1.0,1.0);  // House
                    break;
                case STREET: glColor3d(0.1,0.1,0.1);  // Street
                    break;
                case DRIVEWAY: glColor3d(0.3,0.3,0.3);  // Driveway

            }
           if ((ngc->hole[h].feature[k].featureType<20)||(ngc->hole[h].feature[k].featureType>100))
                glBegin(GL_POLYGON);
           else {
                if (ngc->hole[h].feature[k].featureType==CARTPATH) {
                    glLineWidth(8.0);
                }
                else if (ngc->hole[h].feature[k].featureType==OB) glLineWidth(4.0);
                glBegin(GL_LINE_STRIP);
            }

           for (i=0;i<ngc->hole[h].feature[k].poly[j].vertNum;i++) {
                x[i] = ngc->hole[h].scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[0]
                      -ngc->hole[h].xminmax.v[0]);
                y[i] = ngc->hole[h].scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[1]
                      -ngc->hole[h].yminmax.v[0]);
                x[i] = x[i]+ngc->hole[h].xtran;
                y[i] = y[i]+2*ngc->hole[h].ytran;
                ngc->hole[h].feature[k].poly[j].XY[i].v[0]= x[i];
                ngc->hole[h].feature[k].poly[j].XY[i].v[1]= y[i];
                glVertex2d(x[i],y[i]);
            }
          glEnd();
        }
       }
    glEnd();
    glFlush();
    glEndList();
}

void HoleView::makeZoomList(int h) {
      double x,y;
      int i,j,k;

      glDeleteLists(ZOOMLIST+h,1);
      glNewList(ZOOMLIST+h,GL_COMPILE);
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glEnable(GL_LINE_SMOOTH);
         glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
         for (k=0;k<ngc->hole[h].featureNum;k++) {
            for (j=0;j<ngc->hole[h].feature[k].polyNum;j++) {
              switch (ngc->hole[h].feature[k].featureType) {
                case TEEBOX:  glColor3d(76.0/255.0,155.0/255.0,0.0);  // Tee Box
                    break;
                case FAIRWAY:  glColor3d(102.0/255.0,204.0/255.0,0.0);  // Fairway
                    break;
                case GREEN:glColor3d(0.0,204.0/255.0,0.0);    // Green
                    break;
                case TRAP: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
                case TRAPGREEN: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
                case TREES: glColor3d(0.0,102.0/255.0,0.0);   // Trees
                    break;
                case WATER: glColor3d(51.0/255.0,153.0/255.0,1.0);   // Water
                    break;
                case TEEAREA: glColor4d(38.0/255.0,73.0/255.0,0.0,0.2);   // Tee Area
                    break;
                case CARTPATH: glColor4d(0.0,0.0,0.0,0.55);  // Cart Path
                    break;
                case OB: glColor4d(1.0,1.0,1.0,1.0);  // OB
                    break;
                case HOUSE: glColor3d(1.0,1.0,1.0);  // House
                    break;
                case STREET: glColor3d(0.1,0.1,0.1);  // Street
                    break;
                case DRIVEWAY: glColor3d(0.3,0.3,0.3);  // Driveway

            }
           if ((ngc->hole[h].feature[k].featureType<20)||(ngc->hole[h].feature[k].featureType>100))
                glBegin(GL_POLYGON);
           else {
                if (ngc->hole[h].feature[k].featureType==CARTPATH) {
                    glLineWidth(8.0);
                }
                else if (ngc->hole[h].feature[k].featureType==OB) glLineWidth(4.0);
                glBegin(GL_LINE_STRIP);
            }

           for (i=0;i<ngc->hole[h].feature[k].poly[j].vertNum;i++) {
                x = ngc->hole[h].feature[k].poly[j].XY[i].v[0];
                y = ngc->hole[h].feature[k].poly[j].XY[i].v[1];
                x = x*ngc->hole[h].zoomScale;
                y = y*ngc->hole[h].zoomScale;
                x = x+xres/2.0-ngc->hole[h].zoomScale*xPressed;
                y = y+yres/2.0-ngc->hole[h].zoomScale*yPressed;
                glVertex2d(x,y);
            }
          glEnd();
        }
       }
    glEnd();
    glFlush();
    glEndList();
}

Vector HoleView::UTMFromGreenPixelCoord(double x, double y) {
    Vector tmp;
    int h = gCurrentHole;

    tmp.v[0] = (x-ngc->hole[h].greenxtran)/ngc->hole[h].greenscale + ngc->hole[h].xgreenminmax.v[0]; 
    tmp.v[1] = (y-1.5*ngc->hole[h].greenytran)/ngc->hole[h].greenscale + ngc->hole[h].ygreenminmax.v[0]; 
    return ngc->hole[h].unrotatePoint(tmp,ngc->hole[h].currentGreenUnit);
}

Vector HoleView::ZoomPixelCoordFromUTM(Vector utm) {
    Vector rot,tmp;
    
    rot = ngc->hole[gCurrentHole].rotatePoint(utm,ngc->hole[gCurrentHole].currentUnit);
    tmp.v[0] =  ngc->hole[gCurrentHole].scale*(rot.v[0] -ngc->hole[gCurrentHole].xminmax.v[0]);
    tmp.v[1] =  ngc->hole[gCurrentHole].scale*(rot.v[1] -ngc->hole[gCurrentHole].yminmax.v[0]);
    tmp.v[0] += ngc->hole[gCurrentHole].xtran;
    tmp.v[1] += 2*ngc->hole[gCurrentHole].ytran;
    tmp.v[0] = tmp.v[0]*ngc->hole[gCurrentHole].zoomScale;
    tmp.v[1] = tmp.v[1]*ngc->hole[gCurrentHole].zoomScale;
    tmp.v[0] += xres/2.0-ngc->hole[gCurrentHole].zoomScale*xPressed;
    tmp.v[1] += yres/2.0-ngc->hole[gCurrentHole].zoomScale*yPressed;
    return tmp;
} 

Vector HoleView::UTMFromZoomPixelCoord(double x, double y) {
    Vector tmp;
    int h = gCurrentHole;

    
    tmp.v[0] = (x-xres/2.0+ngc->hole[h].zoomScale*xPressed)/ngc->hole[h].zoomScale-ngc->hole[h].xtran;
    tmp.v[0] = tmp.v[0]/ngc->hole[h].scale+ngc->hole[h].xminmax.v[0];
    tmp.v[1] = (y-yres/2.0+ngc->hole[h].zoomScale*yPressed)/ngc->hole[h].zoomScale-2*ngc->hole[h].ytran;
    tmp.v[1] = tmp.v[1]/ngc->hole[h].scale+ngc->hole[h].yminmax.v[0];
    return ngc->hole[h].unrotatePoint(tmp,ngc->hole[h].currentUnit);
}

void HoleView::makeCurrentGreenList(int h) {
    double x1,y1,dd;
    double x[100],y[100],xscale,yscale,ycen,xcen,xsize,ysize;
    int i,j,k;

    x1 = ngc->hole[h].gd.Pin.v[0]-ngc->hole[h].currentPoint.v[0];
    y1 = ngc->hole[h].gd.Pin.v[1]-ngc->hole[h].currentPoint.v[1];
    dd = sqrt(x1*x1+y1*y1);
    ngc->hole[h].currentGreenUnit.v[0] = x1/dd;
    ngc->hole[h].currentGreenUnit.v[1] = y1/dd;
    ngc->hole[h].rotateToGreenOrientation();
    ngc->hole[h].rotCurrentPoint =
                     ngc->hole[h].rotatePoint(ngc->hole[h].currentPoint,ngc->hole[h].currentGreenUnit);
    ngc->hole[h].findGreenMinMax();

    xsize = ngc->hole[h].xgreenminmax.v[1]-ngc->hole[h].xgreenminmax.v[0];
    ysize = ngc->hole[h].ygreenminmax.v[1]-ngc->hole[h].ygreenminmax.v[0];
    xscale = xres/xsize;
    yscale = yres/ysize;
    ngc->hole[h].greenscale = xscale;
    if (yscale<ngc->hole[h].greenscale) ngc->hole[h].greenscale = yscale;

    xcen = ngc->hole[h].greenscale*xsize/2;
    ycen = ngc->hole[h].greenscale*ysize/2;
    ngc->hole[h].greenxtran = xres/2.0-xcen;
    ngc->hole[h].greenytran = yres/2.0-ycen;

    glDeleteLists(h+GREENLIST,1);
    glNewList(h+GREENLIST,GL_COMPILE);

    for (k=0;k<ngc->hole[h].featureNum;k++) {
        if (ngc->hole[h].feature[k].featureType==GREEN) {
            ngc->hole[h].gd.currentP = ngc->hole[h].currentPoint;
            ngc->hole[h].gd.green = &ngc->hole[h].feature[k];
            ngc->hole[h].findGreenYardage();
        }

      for (j=0;j<ngc->hole[h].feature[k].polyNum;j++) {
        if (ngc->hole[h].feature[k].featureType>300) {
            switch (ngc->hole[h].feature[k].featureType) {
                case GREEN:glColor3d(0.0,204.0/255.0,0.0);    // Green
                     break;
                case TRAPGREEN: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
            }
           glBegin(GL_POLYGON);
            for (i=0;i<ngc->hole[h].feature[k].poly[j].vertNum;i++) {
                x[i] = ngc->hole[h].greenscale*(ngc->hole[h].feature[k].poly[j].rot[i].v[0]-ngc->hole[h].xgreenminmax.v[0]);
                y[i] = ngc->hole[h].greenscale*(ngc->hole[h].feature[k].poly[j].rot[i].v[1]-ngc->hole[h].ygreenminmax.v[0]);
                x[i] = x[i]+ngc->hole[h].greenxtran;
                y[i] = y[i]+1.5*ngc->hole[h].greenytran;
                glVertex2d(x[i],y[i]);
            }
            glEnd();
        }

        }

    }
    double xp,yp;
  //  double yfront,ypin,yback;
    const char *sf,*sp,*sb;
    string sfront,spin,sback;
    ngc->hole[h].gd.PinRot = ngc->hole[h].rotatePoint(ngc->hole[h].gd.Pin,ngc->hole[h].currentGreenUnit);
    ngc->hole[h].gd.FrontRot = ngc->hole[h].rotatePoint(ngc->hole[h].gd.Front,ngc->hole[h].currentGreenUnit);
    ngc->hole[h].gd.BackRot = ngc->hole[h].rotatePoint(ngc->hole[h].gd.Back,ngc->hole[h].currentGreenUnit);
    glPointSize(16.0);
    glBegin(GL_POINTS);
      glColor3f(1.0,0.0,0.0);
      xp = ngc->hole[h].greenscale*(ngc->hole[h].gd.PinRot.v[0]-ngc->hole[h].xgreenminmax.v[0]);
      yp = ngc->hole[h].greenscale*(ngc->hole[h].gd.PinRot.v[1]-ngc->hole[h].ygreenminmax.v[0]);
      xp = xp+ngc->hole[h].greenxtran;
      yp = yp+1.5*ngc->hole[h].greenytran;
      glVertex2d(xp,yp);
      //ypin = yp;
      xp = ngc->hole[h].greenscale*(ngc->hole[h].gd.FrontRot.v[0]-ngc->hole[h].xgreenminmax.v[0]);
      yp = ngc->hole[h].greenscale*(ngc->hole[h].gd.FrontRot.v[1]-ngc->hole[h].ygreenminmax.v[0]);
      xp = xp+ngc->hole[h].greenxtran;
      yp = yp+1.5*ngc->hole[h].greenytran;
      glVertex2d(xp,yp);
      //yfront = yp;
      glColor3f(1.0,0.0,0.0);
      xp = ngc->hole[h].greenscale*(ngc->hole[h].gd.BackRot.v[0]-ngc->hole[h].xgreenminmax.v[0]);
      yp = ngc->hole[h].greenscale*(ngc->hole[h].gd.BackRot.v[1]-ngc->hole[h].ygreenminmax.v[0]);
      xp = xp+ngc->hole[h].greenxtran;
      yp = yp+1.5*ngc->hole[h].greenytran;
      glVertex2d(xp,yp);
      //yback = yp;
    glEnd();
      int offset = 10;
      int dy = 64;
      glColor3f(0.0,0.0,0.0);
      gl_font(FL_HELVETICA_BOLD,48);
      spin = to_string((int) ngc->hole[h].gd.pinYardage);
      sp = spin.c_str();
     // gl_draw(sp,(float) 10.0,(float) (ypin-offset));
      gl_draw(sp,(float) 10,(float) (offset+dy));
      gl_font(FL_HELVETICA_BOLD,48);
      sfront = to_string((int) ngc->hole[h].gd.frontYardage);
      sf = sfront.c_str();
      //gl_draw(sf,(float) 10.0,(float) (yfront-offset));
      gl_draw(sf,(float) 10.0,(float) (offset));
      gl_font(FL_HELVETICA_BOLD,48);
      sback = to_string((int) ngc->hole[h].gd.backYardage);
      sb = sback.c_str();
//      gl_draw(sb,(float) 10.0,(float) (yback-offset));
      gl_draw(sb,(float) 10,(float) (offset +2*dy));

    glFlush();
    glEndList();

}



void HoleView::makeList() {
  int h;
   makeZoomButtonList();
   makeGreenButtonList();
   for (h=1;h<=ngc->maxHole;h++) {
    ngc->hole[h].viewType=FULLVIEW;
    makeCurrentHoleList(h);
    makeCurrentPointList(h);
  }
}

void HoleView::draw() {
    glClearColor(153.0/255.0,1.0,153.0/255.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);  // Clear window
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    switch (ngc->hole[gCurrentHole].viewType) {
       case FULLVIEW:
         makeCurrentPointList(gCurrentHole);
         makeZoomButtonList();
         makeGreenButtonList();
         glCallList(gCurrentHole);
         glCallList(gCurrentHole+CURRENTPOINTLIST);
         glCallList(ZOOMBUTTONLIST);
         glCallList(GREENBUTTONLIST);
        break;
       case GREENVIEW:    
         makeCurrentGreenList(gCurrentHole); 
         makeGreenButtonList();
         glCallList(gCurrentHole+GREENLIST);
         glCallList(GREENBUTTONLIST);
        break;
       case ZOOMVIEW:
         makeZoomList(gCurrentHole);
         makeZoomButtonList();
         glCallList(gCurrentHole+ZOOMLIST);
         glCallList(ZOOMBUTTONLIST);
         if (ngc->hole[gCurrentHole].showMarkPoint) {
            makeMarkPointList(gCurrentHole);
            glCallList(gCurrentHole+MARKPOINTLIST);
         }
       break;
     }
}

bool HoleView::insideZoomButton(double x, double y) {
    if ((x>=zoomButtonX)&&(x<=zoomButtonX+zoomButtonS)&&
        (y>=zoomButtonY)&&(y<=zoomButtonY+zoomButtonS))
        return true;
    else return false;
}

bool HoleView::insideGreenButton(double x, double y) {
    if ((x>=greenButtonX)&&(x<=greenButtonX+greenButtonS)&&
        (y>=greenButtonY)&&(y<=greenButtonY+greenButtonS))
        return true;
    else return false;
}

int HoleView::handle(int e) {
   double x,y;
   switch (e) {
      case FL_PUSH:
          x = Fl::event_x(); y = yres-Fl::event_y();
          if (insideZoomButton(x,y))  {
             if (ngc->hole[gCurrentHole].viewType==ZOOMVIEW) {
                      ngc->hole[gCurrentHole].viewType = FULLVIEW;
                      redraw();
                    }
             else if (ngc->hole[gCurrentHole].viewType==FULLVIEW) {
                 ngc->hole[gCurrentHole].viewType = ZOOMVIEW;
                 ngc->hole[gCurrentHole].showMarkPoint=false;
                 if (!ngc->hole[gCurrentHole].zoomPointSelected) {
                   xPressed= xres/2;
                   yPressed=yres/2;
                 }
                    
                 redraw();
               }
          }
          else if (insideGreenButton(x,y)) {
             if (ngc->hole[gCurrentHole].viewType==FULLVIEW) {
                      ngc->hole[gCurrentHole].viewType = GREENVIEW;
                      redraw();
                    }
             else if (ngc->hole[gCurrentHole].viewType==GREENVIEW) {
                 ngc->hole[gCurrentHole].viewType = FULLVIEW;
                 redraw();
               }
             }
          else {      
              switch (ngc->hole[gCurrentHole].viewType) {
              case FULLVIEW:
                xPressed = x; yPressed=y;
                ngc->hole[gCurrentHole].zoomPointSelected=true;
                break; 
              case GREENVIEW:
                xPressed = x; yPressed=y;
                ngc->hole[gCurrentHole].gd.Pin= UTMFromGreenPixelCoord(xPressed,yPressed);;
                redraw();
                break; 
              case ZOOMVIEW: 
                ngc->hole[gCurrentHole].markPoint = UTMFromZoomPixelCoord(x,y);
                ngc->hole[gCurrentHole].showMarkPoint=true;
                redraw();
                break;
              }
           } 
      return 1;
  case FL_DRAG:
     //     cout   << "Drag " << Fl::event_x() << " " << Fl::event_y() << endl;
      return 1;
  case FL_RELEASE:
      //    cout   << "Release  " << Fl::event_x() << " " << Fl::event_y() << endl;
          x = Fl::event_x(); y = yres-Fl::event_y();
          xReleased = x; yReleased=y;
      return 1;
    default:
      return Fl_Gl_Window::handle(e);
  }
}
      
