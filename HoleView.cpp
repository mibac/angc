#ifndef HOLEVIEW_H_
#include "HoleView.hpp"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

void HoleView::initHoleWindow(int x,int y,Course *course) {
     xres = x;
     yres = y;
     ngc = course;
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D((double) 0 ,(double) x, (double) 0, (double) y);
     glMatrixMode(GL_MODELVIEW);
}

void HoleView::makeCurrentList(int h) {
     int i,k,j;
     double x[100],y[100],scale,xscale,yscale,xcen,ycen;
     double xtran,ytran,yt,xt,xsize,ysize;
     double x1,y1,dd,xp,yp;

      x1 = ngc->hole[h].startOrient[1].v[0]-ngc->hole[h].currentPoint.v[0];
      y1 = ngc->hole[h].startOrient[1].v[1]-ngc->hole[h].currentPoint.v[1];
      dd = sqrt(x1*x1+y1*y1);
      ngc->hole[h].currentUnit.v[0] = x1/dd;
      ngc->hole[h].currentUnit.v[1] = y1/dd;
      ngc->hole[h].rotateHoleToOrientation();
      ngc->hole[h].findMinMax();
      xsize = ngc->hole[h].xminmax.v[1]-ngc->hole[h].xminmax.v[0];
      ysize = ngc->hole[h].yminmax.v[1]-ngc->hole[h].yminmax.v[0];
      xscale = xres/xsize;
      yscale = yres/ysize;
      scale = xscale;
      if (yscale<scale) scale = yscale;
      xcen = scale*xsize/2.0;
      ycen = scale*ysize/2.0;
      cout << "hole " << h << " " << xscale << " " << yscale  << endl;
      xtran = xres/2.0-xcen;
      ytran = yres/2.0-ycen;
      cout << xsize << " " << ysize << " " << xcen << " " << ycen << " " << xtran << " " << ytran << endl;
        glDeleteLists(h,1);
        glNewList(h,GL_COMPILE);
           glColor3d(153.0/255.0,1.0,153.0/255.0);
           glBegin(GL_POLYGON);
             glVertex2d(0,0);
             glVertex2d(xres,0);
             glVertex2d(xres,yres);
             glVertex2d(0,yres);
           glEnd();
        for (k=0;k<ngc->hole[h].featureNum;k++) {
            for (j=0;j<ngc->hole[h].feature[k].polyNum;j++) {
            switch (ngc->hole[h].feature[k].featureType) {
                case 1:  glColor3d(76.0/255.0,155.0/255.0,0.0);  // Tee Box
                    break;
                case 2:  glColor3d(102.0/255.0,204.0/255.0,0.0);  // Fairway
                   break;
                case 3:glColor3d(0.0,204.0/255.0,0.0);    // Green
                    break;
                case 4: glColor3d(1.0,1.0,204.0/255.0);   // Trap
                    break;
                case 5: glColor3d(0.0,102.0/255.0,0.0);   // Trees
                    break;
                case 6: glColor3d(51.0/255.0,153.0/255.0,1.0);   // Water
                    break;
                case 7: glColor3d(0.3,0.3,0.3);   // Cart Path
                    break;

            }
            glBegin(GL_POLYGON);
              for (i=0;i<ngc->hole[h].feature[k].poly[j].vertNum;i++) {
                x[i] = scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[0]-ngc->hole[h].xminmax.v[0]);
                y[i] = scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[1]-ngc->hole[h].yminmax.v[0]);
                x[i] = x[i]+xtran;
                y[i] = y[i]+2*ytran;
                glVertex2d(x[i],y[i]);
            }
           glEnd();
           }
         }
        glPointSize(9.0);
        glBegin(GL_POINTS);
          glColor3f(1.0,0.0,0.0);
          xp = scale*(ngc->hole[h].rotCurrentPoint.v[0]-ngc->hole[h].xminmax.v[0]);
          yp = scale*(ngc->hole[h].rotCurrentPoint.v[1]-ngc->hole[h].yminmax.v[0]);
          xp += xtran;
          yp += 2*ytran;
          glVertex2d(xp,yp);
        glEnd();
        glFlush();
        glEndList();
}

void HoleView::makeList() {
     int h;
     for (h=1;h<=ngc->maxHole;h++) makeCurrentList(h);
}

void HoleView::draw() {
    cout << "In draw:  current hole = " << currentHole << endl;
    glCallList(currentHole);
}
