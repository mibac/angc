#ifndef HOLEVIEW_H_
#include "HoleView.hpp"
#endif

#ifndef COURSE_H_
#include "Course.h"
#endif

void HoleView::makeList() {
  int h,i,k,j,xtran;
  double x[100],y[100],scale,xscale,yscale,xcen;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D((double) 0,(double) 280,(double) 0,(double) 700);
  glMatrixMode(GL_MODELVIEW);
/*
        glDeleteLists(1,1);
        glNewList(1,GL_COMPILE);
           glColor3d(0.9,0.5,0.5);
        //   glClear(GL_COLOR_BUFFER_BIT);
           glBegin(GL_POLYGON);
             glVertex2d(0,0);
             glVertex2d(280,0);
             glVertex2d(280,700);
             glVertex2d(0,700);
           glEnd();
          glColor3d(0.1,0.8,0.1);
        //   glClear(GL_COLOR_BUFFER_BIT);
           glBegin(GL_POLYGON);
             glVertex2d(150,150);
             glVertex2d(200,150);
             glVertex2d(200,200);
             glVertex2d(150,200);
           glEnd();
         glEndList();
*/
  for (h=1;h<=ngc->maxHole;h++) {
        xscale = ngc->hole[h].xminmax.v[1]-ngc->hole[h].xminmax.v[0];
        yscale = ngc->hole[h].yminmax.v[1]-ngc->hole[h].yminmax.v[0];
        xscale = 280.0/xscale;
        yscale = 700.0/yscale;
        scale = xscale;
        if (yscale<scale) scale = yscale;

        glDeleteLists(h,1);
        glNewList(h,GL_COMPILE);
           glColor3d(153.0/255.0,1.0,153.0/255.0);
           glBegin(GL_POLYGON);
             glVertex2d(0,0);
             glVertex2d(280,0);
             glVertex2d(280,700);
             glVertex2d(0,700);
           glEnd();
        for (k=0;k<ngc->hole[h].featureNum;k++) {
            for (j=0;j<ngc->hole[h].feature[k].polyNum;j++) {

/*            
             Feature Types
             1 TeeBox
             2 Fairway;
             3 Green
             4 Bunker
             5 Trees
             6 Water
             7 Cart Path
 */

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
                x[i] = x[i];
                y[i] = y[i];
                glVertex2d(x[i],y[i]);
            }
           glEnd();
           }
         }
        glFlush();
        glEndList();
    }

}

void HoleView::draw() {
    cout << "In draw:  current hole = " << currentHole << endl;
    glCallList(currentHole);
}
