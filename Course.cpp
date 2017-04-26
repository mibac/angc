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
/*
void Hole::setCurrentPoint(double w) {
   walk = walk+w;
//cout << "Walk = " << walk << endl;
   if (walk>1.0) walk = 0.0;
   currentPoint.v[0] = (1-walk)*startOrient[0].v[0] + walk*startOrient[1].v[0];
   currentPoint.v[1] = (1-walk)*startOrient[0].v[1] + walk*startOrient[1].v[1];
//cout << currentPoint.v[0] << " " << currentPoint.v[1] << endl;
}
*/
void Hole::setCurrentPoint(double east,double north) {
  currentPoint.v[0] = east;
  currentPoint.v[1] = north;
}

void Hole::computeYardageToHole() {

   double x,y;
   x = startOrient[1].v[0]-currentPoint.v[0];
   y = startOrient[1].v[1]-currentPoint.v[1];
   yardageToHole  = (int) (1.0936*sqrt(x*x+y*y));
   currentYardageToHoleStr = to_string(yardageToHole);
//cout << "ssh " << currentYardageToHoleStr << endl;
}
 
void Hole::computeYardageFromTee() {

   double x,y;

   x = startOrient[0].v[0]-currentPoint.v[0];
   y = startOrient[0].v[1]-currentPoint.v[1];
   yardageFromTee  = (int) (1.0936*sqrt(x*x+y*y));
   currentYardageFromTeeStr = to_string(yardageFromTee);
 //cout << "sst " << currentYardageFromTeeStr << endl;
}
 
 
Course::Course(int mh) {
  maxHole = mh;
}

void Course::readCourse() {
    ifstream fin,finlist;
    int h,n,i,j,k,t;
    double walk,east,north;
    string holeprefix,flistname,orient,fn,fname;
    string holenum[] = {"","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18"};
    LL2UTM latlon;	  
    	
    for (h=1;h<=maxHole;h++) {
        holeprefix = pathprefix+"Hole"+holenum[h]+"/";
        flistname = holeprefix+ "list.txt";
        finlist.open(flistname);
        finlist >> t;
        hole[h].featureNum=t-1;
        finlist >> orient;
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
        walk = 0.0;
        hole[h].currentPoint.v[0] = (1-walk)*hole[h].startOrient[0].v[0]+walk*hole[h].startOrient[1].v[0];
        hole[h].currentPoint.v[1] = (1-walk)*hole[h].startOrient[0].v[1]+walk*hole[h].startOrient[1].v[1];
        fin.close();
        for (k=0;k<hole[h].featureNum;k++) {
            finlist >> fn;
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
/*
      if (h==3) {
        string walkpath = holeprefix+"HoleInterest.pts";
        fin.open(walkpath);
        double xx,yy;
        for (j=0;j<700;j++) {
           fin >> xx>>yy;
           if (j>25) {
              hole[h].pathPoint[j-26].v[0] = xx;
              hole[h].pathPoint[j-26].v[1] = yy;
           }
          hole[h].pathPointNum = 674;
        }
        fin.close();

      }
*/
    }
}
