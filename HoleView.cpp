#ifndef HOLEVIEW_H_
#include "HoleView.h"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

#ifndef CLATLNG_H
#include "CLatLng.h"
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

void HoleView::makeCurrentPointList(int h) {
     double xp,yp;
     const char *sh, *st;
        ngc->hole[h].computeYardageToHole();
        ngc->hole[h].computeYardageFromTee();
//cout << "in mcp " << ngc->hole[h].currentYardageToHoleStr << endl;
//cout << "in mcp " << ngc->hole[h].currentYardageFromTeeStr << endl;
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
/*
void HoleView::makePathList(int h) {
        double xp,yp;
        Vector rot;
        glDeleteLists(h+200,1);
        glNewList(h+200,GL_COMPILE);
        glPointSize(9.0);
        glBegin(GL_POINTS);
          glColor3f(1.0,0.0,0.0);
        for (int j=0;j< ngc->hole[h].pathPointNum;j++) {
          rot = ngc->hole[h].rotatePoint(ngc->hole[h].pathPoint[j],ngc->hole[h].currentUnit);
          xp = ngc->hole[h].scale*(rot.v[0]-ngc->hole[h].xminmax.v[0]);
          yp = ngc->hole[h].scale*(rot.v[1]-ngc->hole[h].yminmax.v[0]);
          xp += ngc->hole[h].xtran;
          yp += 2*ngc->hole[h].ytran;
//cout << xp << " " << yp << endl;
          glVertex2d(xp,yp);
        }
        glEnd();
        glFlush();
        glEndList();
}
*/
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
      //cout << xsize << " " << ysize << " " << xcen << " " << ycen << " " << xtran << " " << ytran << endl;
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
                case 31: glColor3d(1.0,1.0,1.0);   // House
                    break;
                case 32: glColor3d(0.1,0.1,0.1);   // Street
                    break;
                case 33: glColor3d(0.3,0.3,0.3);   // Driveway
                    break;

      }
      glBegin(GL_POLYGON);
              for (i=0;i<ngc->hole[h].feature[k].poly[j].vertNum;i++) {
                x[i] = ngc->hole[h].scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[0]-ngc->hole[h].xminmax.v[0]);
                y[i] = ngc->hole[h].scale*(ngc->hole[h].feature[k].poly[j].rot[i].v[1]-ngc->hole[h].yminmax.v[0]);
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

void HoleView::makeList() {
  int h;
     for (h=1;h<=ngc->maxHole;h++) {
    makeCurrentHoleList(h);
    makeCurrentPointList(h);
    //        if (h==3) makePathList(h);
  }
}

void HoleView::draw() {
    makeCurrentPointList(CLatLng::currentHole);
    glCallList(CLatLng::currentHole);
    glCallList(CLatLng::currentHole+100);
   // if (CLatLng::currentHole==3) glCallList(CLatLng::currentHole+200);
}
