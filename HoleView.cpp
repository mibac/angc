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
        glDeleteLists(h+100,1);
        glNewList(h+100,GL_COMPILE);
        glPointSize(16.0);
        glBegin(GL_POINTS);
          glColor3f(1.0,0.0,0.0);
          xp = ngc->hole[h].scale*(ngc->hole[h].rotCurrentPoint.v[0]-ngc->hole[h].xminmax.v[0]);
          yp = ngc->hole[h].scale*(ngc->hole[h].rotCurrentPoint.v[1]-ngc->hole[h].yminmax.v[0]);
          xp += ngc->hole[h].xtran;
          yp += 2*ngc->hole[h].ytran;
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

void HoleView::makeCurrentHoleList(int h) {
     int i,k,j;
     double x[100],y[100],xscale,yscale,xcen,ycen;
     double xsize,ysize;
     double x1,y1,dd;

      x1 = ngc->hole[h].startOrient[1].v[0]-ngc->hole[h].startOrient[0].v[0];
      y1 = ngc->hole[h].startOrient[1].v[1]-ngc->hole[h].startOrient[0].v[1];
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
                glVertex2d(x[i],y[i]);
            }
          glEnd();
        }
       }
    glEnd();
    glFlush();
    glEndList();
}

void HoleView::makeCurrentGreenList(int h) {
    double x1,y1,dd;
    double x[100],y[100],xscale,yscale,ycen,xcen,xsize,ysize;
    int i,j,k;

    x1 = ngc->hole[h].startOrient[1].v[0]-ngc->hole[h].currentPoint.v[0];
    y1 = ngc->hole[h].startOrient[1].v[1]-ngc->hole[h].currentPoint.v[1];
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

    glDeleteLists(h+300,1);
    glNewList(h+300,GL_COMPILE);

    for (k=0;k<ngc->hole[h].featureNum;k++) {
        if (ngc->hole[h].feature[k].featureType==GREEN) {
            ngc->hole[h].gd.Pin =ngc->hole[h].startOrient[1];
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
    double xp,yp,yfront,ypin,yback;
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
      ypin = yp;
      xp = ngc->hole[h].greenscale*(ngc->hole[h].gd.FrontRot.v[0]-ngc->hole[h].xgreenminmax.v[0]);
      yp = ngc->hole[h].greenscale*(ngc->hole[h].gd.FrontRot.v[1]-ngc->hole[h].ygreenminmax.v[0]);
      xp = xp+ngc->hole[h].greenxtran;
      yp = yp+1.5*ngc->hole[h].greenytran;
      glVertex2d(xp,yp);
      yfront = yp;
      glColor3f(1.0,0.0,0.0);
      xp = ngc->hole[h].greenscale*(ngc->hole[h].gd.BackRot.v[0]-ngc->hole[h].xgreenminmax.v[0]);
      yp = ngc->hole[h].greenscale*(ngc->hole[h].gd.BackRot.v[1]-ngc->hole[h].ygreenminmax.v[0]);
      xp = xp+ngc->hole[h].greenxtran;
      yp = yp+1.5*ngc->hole[h].greenytran;
      glVertex2d(xp,yp);
      yback = yp;
    glEnd();
      int offset = 40;
      glColor3f(0.0,0.0,0.0);
      gl_font(FL_HELVETICA_BOLD,48);
      spin = to_string((int) ngc->hole[h].gd.pinYardage);
      sp = spin.c_str();
      gl_draw(sp,(float) 10.0,(float) (ypin-offset));
      gl_font(FL_HELVETICA_BOLD,48);
      sfront = to_string((int) ngc->hole[h].gd.frontYardage);
      sf = sfront.c_str();
      gl_draw(sf,(float) 10.0,(float) (yfront-offset));
      gl_font(FL_HELVETICA_BOLD,48);
      sback = to_string((int) ngc->hole[h].gd.backYardage);
      sb = sback.c_str();
      gl_draw(sb,(float) 10.0,(float) (yback-offset));
    glFlush();
    glEndList();

}



void HoleView::makeList() {
  int h;
   for (h=1;h<=ngc->maxHole;h++) {
    ngc->hole[h].viewType=0;
    makeCurrentHoleList(h);
    makeCurrentPointList(h);
  }
}

void HoleView::draw() {
    glClearColor(153.0/255.0,1.0,153.0/255.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);  // Clear window
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    if (ngc->hole[gCurrentHole].viewType==0) {
         makeCurrentPointList(gCurrentHole);
//cout <<setprecision(8) << " in draw " << ngc->hole[gCurrentHole].currentPoint.v[0] << " " << ngc->hole[gCurrentHole].v[1] << endl;
         glCallList(gCurrentHole);
         glCallList(gCurrentHole+100);
    }
    else {
         makeCurrentGreenList(gCurrentHole); 
         glCallList(gCurrentHole+300);
     }
}
