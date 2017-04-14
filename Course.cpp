#include "Course.h"

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

}

void Hole::findMinMax() {
    int i,j,k;

    xminmax.v[0] = yminmax.v[0] = 100000000000.0;
    xminmax.v[1] = yminmax.v[1] = -100000000000.0;

    for (k=0;k<featureNum;k++) {
        for (j=0;j<feature[k].polyNum;j++) {
            for (i=0;i<feature[k].poly[j].vertNum;i++) {
                if (feature[k].poly[j].rot[i].v[0]<xminmax.v[0]) xminmax.v[0]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[0]>xminmax.v[1]) xminmax.v[1]=feature[k].poly[j].rot[i].v[0];
                if (feature[k].poly[j].rot[i].v[1]<yminmax.v[0]) yminmax.v[0]=feature[k].poly[j].rot[i].v[1];
                if (feature[k].poly[j].rot[i].v[1]>yminmax.v[1]) yminmax.v[1]=feature[k].poly[j].rot[i].v[1];
            }
        }
    }
}

Course::Course(int mh) {
  maxHole = mh;
}

void Course::readCourse() {
    ifstream fin,finlist;
    int h,n,i,j,k,t;
    double lt,lg,x1,y1,dd;
    string pathprefix,holeprefix,flistname,orient,fn,fname;
    string holenum[] = {"","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18"};
    LL2UTM latlon;

	bool JACK = false;
	if (JACK)
    	pathprefix = "/home/pi/golf/GolfCourseMap/rpigolf/holes/";
    else
    	pathprefix = "/home/pi/projects/gpsdclient/holes/";
    	
    for (h=1;h<=maxHole;h++) {
        holeprefix = pathprefix+"Hole"+holenum[h]+"/";
        flistname = holeprefix+ "list.txt";
        finlist.open(flistname);
        finlist >> t;
        hole[h].featureNum=t-1;
        finlist >> orient;
        fname = holeprefix+orient +".txt";
        fin.open(fname);
        fin >> n ;
        if (n!=2) {
            cout << "First file in list is not the orientation file" << endl;
            exit(0);
        }
        for (i=0;i<n;i++) {
            fin >> lg >> lt ;
            latlon.setLatLon(lt,lg);
            latlon.convert2UTM();
            hole[h].startOrient[i].v[0] = hole[h].currentOrient[i].v[0] = latlon.UTMEast;
            hole[h].startOrient[i].v[1] = hole[h].currentOrient[i].v[1] = latlon.UTMNorth;
        }
        x1 = hole[h].startOrient[1].v[0]-hole[h].startOrient[0].v[0];
        y1 = hole[h].startOrient[1].v[1]-hole[h].startOrient[0].v[1];
        dd = sqrt(x1*x1+y1*y1);
        hole[h].startUnit.v[0] = hole[h].currentUnit.v[0] = x1/dd;
        hole[h].startUnit.v[1] = hole[h].currentUnit.v[1] = y1/dd;
        fin.close();
        for (k=0;k<hole[h].featureNum;k++) {
            finlist >> fn;
            fname = holeprefix + fn+"ConvexUM.txt";
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
       hole[h].rotateHoleToOrientation();
       hole[h].findMinMax();
       finlist.close();
    }


}
