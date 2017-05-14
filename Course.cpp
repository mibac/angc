#include "Course.h"
#define JACK   1


const string pathprefix = "/home/pi/golf/angc/NGCHoles/";

Hole::Hole() {
}

Vector  Hole::rotatePoint(Vector x,Vector u) {
    Vector v;

    v.v[0] = u.v[1]*x.v[0] - u.v[0]*x.v[1];
    v.v[1] = u.v[0]*x.v[0] + u.v[1]*x.v[1];
    return v;
}

Vector  Hole::unrotatePoint(Vector x,Vector u) {
    Vector v;

    v.v[0] = u.v[1]*x.v[0] + u.v[0]*x.v[1];
    v.v[1] = -u.v[0]*x.v[0] + u.v[1]*x.v[1];
    return v;
}

void Hole::rotateHoleToOrientation() {
    int i,j,k;
    for (k=0;k<featureNum;k++) {
         for (j=0;j<feature[k].polyNum;j++) {
             for (i=0;i<feature[k].poly[j].vertNum;i++) {
                 feature[k].poly[j].rot[i] = rotatePoint(feature[k].poly[j].UTM[i],currentUnit);
             }
         }
    }
    rotCurrentPoint = rotatePoint(currentPoint,currentUnit);
}
void Hole::rotateToGreenOrientation() {
    int i,j,k;
    for (k=0;k<featureNum;k++) {
         for (j=0;j<feature[k].polyNum;j++) {
             for (i=0;i<feature[k].poly[j].vertNum;i++) {
                 feature[k].poly[j].rot[i] = rotatePoint(feature[k].poly[j].UTM[i],currentGreenUnit);
             }
         }
    }
    rotCurrentPoint = rotatePoint(currentPoint,currentGreenUnit);
}

void Hole::findMinMax() {
    int i,j,k;

    xminmax.v[0] = yminmax.v[0] = 100000000000.0;
    xminmax.v[1] = yminmax.v[1] = -100000000000.0;

    for (k=0;k<featureNum;k++) {
        for (j=0;j<feature[k].polyNum;j++) {
            for (i=0;i<feature[k].poly[j].vertNum;i++) {
              if (feature[k].poly[j].rot[i].v[1]>rotCurrentPoint.v[1]-20) {
                if (feature[k].poly[j].rot[i].v[0]<xminmax.v[0]) xminmax.v[0]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[0]>xminmax.v[1]) xminmax.v[1]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[1]<yminmax.v[0]) yminmax.v[0]=feature[k].poly[j].rot[i].v[1];
                if (feature[k].poly[j].rot[i].v[1]>yminmax.v[1]) yminmax.v[1]=feature[k].poly[j].rot[i].v[1];
               }
            }
        }
    }
}

void Hole::findGreenMinMax() {
    int i,j,k;

    xgreenminmax.v[0] = ygreenminmax.v[0] = 100000000000.0;
    xgreenminmax.v[1] = ygreenminmax.v[1] = -100000000000.0;

    for (k=0;k<featureNum;k++) {
        for (j=0;j<feature[k].polyNum;j++) {
            for (i=0;i<feature[k].poly[j].vertNum;i++) {
              if (feature[k].featureType>300) {
                if (feature[k].poly[j].rot[i].v[0]<xgreenminmax.v[0]) xgreenminmax.v[0]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[0]>xgreenminmax.v[1]) xgreenminmax.v[1]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[1]<ygreenminmax.v[0]) ygreenminmax.v[0]=feature[k].poly[j].rot[i].v[1];
                if (feature[k].poly[j].rot[i].v[1]>ygreenminmax.v[1]) ygreenminmax.v[1]=feature[k].poly[j].rot[i].v[1];
                }
            }
        }
    }

}



void Hole::setCurrentPoint(double east,double north) {
  currentPoint.v[0] = east;
  currentPoint.v[1] = north;
}

double Hole::yardDistance(Vector p1,Vector p2) {
    return 1.0936*sqrt((p1.v[0]-p2.v[0])*(p1.v[0]-p2.v[0])+ (p1.v[1]-p2.v[1])*(p1.v[1]-p2.v[1]));
}

void Hole::findGreenYardage() {
    int i,j;
    double u1,u2,v1,v2;
    double x1,x2,y1,y2;
    double a1,a2,b1,b2,c1,c2,det;
    double s,t,big = 10000000.0;
    double smin = big, smax = -big;

    u1 = gd.currentP.v[0]; v1 = gd.currentP.v[1];
    //u2 = gd.Pin.v[0]; v2 = gd.Pin.v[1];
    u2 = gd.Center.v[0]; v2 = gd.Center.v[1];
    a1 = u2-u1; a2 = v2-v1;
    for (j=0;j<gd.green->polyNum;j++)  {
            for (i=0;i<gd.green->poly[j].vertNum;i++) {
                if (i<gd.green->poly[j].vertNum-1) {
                    x1 = gd.green->poly[j].UTM[i].v[0];
                    y1 = gd.green->poly[j].UTM[i].v[1];
                    x2 = gd.green->poly[j].UTM[i+1].v[0];
                    y2 = gd.green->poly[j].UTM[i+1].v[1];
                 }
                else {
                    x1 = gd.green->poly[j].UTM[i].v[0];
                    y1 = gd.green->poly[j].UTM[i].v[1];
                    x2 = gd.green->poly[j].UTM[0].v[0];
                    y2 = gd.green->poly[j].UTM[0].v[1];
                }
                b1 = x1-x2; c1= x1-u1;
                b2 = y1-y2; c2 = y1-v1;
                det = a2*b1-a1*b2;
                if (fabs(det)>0.00001) {
                    t = (c1*a2-c2*a1)/det;
                    if ((t>=0.0)&&(t<=1.0)) {
                        s = (c2*b1-c1*b2)/det;
                        if (s<smin) smin = s;
                        if (s>smax) smax = s;
                    }

                }
            }
    }
    if ((smin<big)&&(smax>-big)) {
        gd.Front.v[0] = u1+smin*a1; gd.Front.v[1] = v1+smin*a2;
        gd.Back.v[0] = u1+smax*a1; gd.Back.v[1] = v1+smax*a2;
        gd.pinYardage= yardDistance(gd.Pin,gd.currentP);
        gd.frontYardage= yardDistance(gd.Front,gd.currentP);
        gd.backYardage= yardDistance(gd.Back,gd.currentP);

    }
    else {
        cout << "problem finding front,back" << endl;
    }

}

void Hole::computeYardageToHole() {

   double x,y;
   //x = startOrient[1].v[0]-currentPoint.v[0];
   //y = startOrient[1].v[1]-currentPoint.v[1];
   x = gd.Pin.v[0]-currentPoint.v[0];
   y = gd.Pin.v[1]-currentPoint.v[1];
   yardageToHole  = (int) (1.0936*sqrt(x*x+y*y));
   currentYardageToHoleStr = to_string(yardageToHole);
}

void Hole::computeYardageFromTee() {

   double x,y;

   x = startOrient[0].v[0]-currentPoint.v[0];
   y = startOrient[0].v[1]-currentPoint.v[1];
   yardageFromTee  = (int) (1.0936*sqrt(x*x+y*y));
   currentYardageFromTeeStr = to_string(yardageFromTee);
}

bool Hole::isOnGreen() {
   int i,j,pos,neg;
   double x1,x2,y1,y2,x,y;
   double d;

   x = gd.Pin.v[0];
   y = gd.Pin.v[1];

   for (j=0;j<gd.green->polyNum;j++)  {
        pos=neg=0;
        for (i=0;i<gd.green->poly[j].vertNum;i++) {
                if (i<gd.green->poly[j].vertNum-1) {
                    x1 = gd.green->poly[j].UTM[i].v[0];
                    y1 = gd.green->poly[j].UTM[i].v[1];
                    x2 = gd.green->poly[j].UTM[i+1].v[0];
                    y2 = gd.green->poly[j].UTM[i+1].v[1];
                 }
                else {
                    x1 = gd.green->poly[j].UTM[i].v[0];
                    y1 = gd.green->poly[j].UTM[i].v[1];
                    x2 = gd.green->poly[j].UTM[0].v[0];
                    y2 = gd.green->poly[j].UTM[0].v[1];
                }
               d = (x-x1)*(y2-y1)-(y-y1)*(x2-x1);
               if (d>0) pos++;
               if (d<0) neg++;
          }
          if ((pos==0)||(neg==0)) return true;
     }
  return false;
}

Course::Course(int mh) {
  maxHole = mh;
}

void Course::readCourse() {
    ifstream fin,finlist;
    int h,n,i,j,k,t;
    double east,north;
    string holeprefix,flistname,orient,fn,fname;
    string holenum[] = {"","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18"};
    LL2UTM latlon;

    for (h=1;h<=maxHole;h++) {
        hole[h].showMarkPoint=false;
        hole[h].zoomPointSelected=false;
        hole[h].viewType = 0;
        hole[h].zoomScale = 3.0;
        holeprefix = pathprefix+"Hole"+holenum[h]+"/";
        flistname = holeprefix+ "list.txt";
        finlist.open(flistname);
        finlist >> t;
        hole[h].featureNum=t-1;
        finlist >> orient >> t;
        fname = holeprefix+orient +"Final.txt";
        fin.open(fname);
        fin >> n ;
        if (n!=2) {
            cout << "First file in list is not the orientation file" << endl;
            exit(0);
        }
        for (i=0;i<n;i++) {
            fin >> east >> north ;
            hole[h].startOrient[i].v[0] = hole[h].currentOrient[i].v[0] = east;
            hole[h].startOrient[i].v[1] = hole[h].currentOrient[i].v[1] = north;
        }
        hole[h].gd.Pin.v[0] = hole[h].gd.Center.v[0] = hole[h].startOrient[1].v[0];
        hole[h].gd.Pin.v[1] = hole[h].gd.Center.v[1] = hole[h].startOrient[1].v[1];
        hole[h].gd.pinOnGreen=true;
        hole[h].walk = 0.0;
      //  hole[h].currentPoint.v[0] = (1-hole[h].walk)*hole[h].startOrient[0].v[0]+
      //                              hole[h].walk*hole[h].startOrient[1].v[0];
      //  hole[h].currentPoint.v[1] = (1-hole[h].walk)*hole[h].startOrient[0].v[1]+
       //                              hole[h].walk*hole[h].startOrient[1].v[1];
        hole[h].currentPoint.v[0] = (1-hole[h].walk)*hole[h].startOrient[0].v[0]+
                                    hole[h].walk*hole[h].gd.Pin.v[0];
        hole[h].currentPoint.v[1] = (1-hole[h].walk)*hole[h].startOrient[0].v[1]+
                                     hole[h].walk*hole[h].gd.Pin.v[1];
        fin.close();
        for (k=0;k<hole[h].featureNum;k++) {
            finlist >> fn >> t;
            fname = holeprefix + fn+"Final.txt";
            fin.open(fname);
            fin >> hole[h].feature[k].polyNum;
            for (j=0;j<hole[h].feature[k].polyNum;j++) {
                fin >> hole[h].feature[k].poly[j].vertNum >> hole[h].feature[k].featureType;
                for (i=0;i<hole[h].feature[k].poly[j].vertNum;i++) {
                    fin >> hole[h].feature[k].poly[j].UTM[i].v[0] >> hole[h].feature[k].poly[j].UTM[i].v[1];
                }
            }

            fin.close();
        }
       finlist.close();
    }
}
