/* je compile command
g++ markGps.cpp gps.cpp calcDist.cpp -o _NGCApp -g  -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -D_LARGEFILE_SOURCE -D_LARGEFILE64 -std=c++11 -lfltk -lgps 
*/

// Demonstrate how to use Fl_Input in a touchscreen application -erco 08/25/06

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <unistd.h>

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Timer.H>
#include <FL/gl.h>
#include <FL/glu.h>

#ifndef COURSE_H_
#include "Course.h"
#endif

#ifndef GPS_H
#include "gps.h"
#endif

#ifndef _GPSD_GPSMM_H_
#include "libgpsmm.h"
#endif 

#ifndef C2UTM_hpp
#include "C2UTM.hpp"
#endif

using namespace std;

// Conditionals
#define USEGPS 1

// GLOBALS
const int kBtn1 = 0;
const int kBtn2 = 1;
const int kBtn3 = 2;
const int kBtn4 = 3;
const int kBtn5 = 4;
const int kBtn6 = 5;
const int kBtn7 = 6;
const int kBtn8 = 7;
const int kBtn9 = 8;
const int kBtnT = 9;
const int kBtnM = 10;
const int kBtnG = 11;
const int kBtnFB = 12;
const int kBtnMark = 13;
const int kBtnWriteMarker = 14;
const int kBtnWriteAll = 15;
const int kBtnSize = 80;
const int kLeftMargin = 300;
const int WAITING_TIME = 5000000;
const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;
const int kNumMarks = 10;

bool bFrontNine = true;

int oldvGPGGAsz =0;
int nowvGPGGAsz =0;
int currentHole;

float refMarkf = 0.0;
float nowMarkf = 0.0;

struct LatLng {
  double lat;
  double lng;
};

LatLng currentRefMarker;

Fl_Window *win;
Fl_Input *my_input;
Fl_Box *boxYardage;
Fl_Button *btnMark;
Fl_Button *btnWrite;


FILE *G_fp = NULL;
const char *SIMPLEGPS_CMD = "simplegps";	

string strDistFromMark("0");

vector<Fl_Button *> vbtn; // the hole and marker pushbuttons
vector<string> vGPGGA;
vector<string> vMarkers;

GPS myGPS;

class HoleView;
HoleView *hv;

Course *ngc;

// Prototypes
void setupYardage(string s);
string getFilename();

class HoleView: public Fl_Gl_Window {
 public:
   HoleView(int x,int y,int w,int h,const char *l):Fl_Gl_Window(x,y,w,h,l){}
   void makeList();
   void draw();
};

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


string getHoleName() {
	string str;
	if (vbtn[kBtn1]->value() == 1) str = vbtn[kBtn1]->label();
	else if (vbtn[kBtn2]->value() == 1) str = vbtn[kBtn2]->label();
	else if (vbtn[kBtn3]->value() == 1) str = vbtn[kBtn3]->label();
	else if (vbtn[kBtn4]->value() == 1) str = vbtn[kBtn4]->label();
	else if (vbtn[kBtn5]->value() == 1) str = vbtn[kBtn5]->label();
	else if (vbtn[kBtn6]->value() == 1) str = vbtn[kBtn6]->label();
	else if (vbtn[kBtn7]->value() == 1) str = vbtn[kBtn7]->label();
	else if (vbtn[kBtn8]->value() == 1) str = vbtn[kBtn8]->label();
	else if (vbtn[kBtn9]->value() == 1) str = vbtn[kBtn9]->label();
	return str;
}

string getMarkerName() {
	string str;
	if (vbtn[kBtnT]->value() == 1) str = "Tee";
	else if (vbtn[kBtnM]->value() == 1) str = "150";
	else if (vbtn[kBtnG]->value() == 1) str = "Green";
	return str;
}

void handleBtnFB() {
	if (bFrontNine) {
		vbtn[kBtn1]->label("10");
		vbtn[kBtn2]->label("11");
		vbtn[kBtn3]->label("12");
		vbtn[kBtn4]->label("13");
		vbtn[kBtn5]->label("14");
		vbtn[kBtn6]->label("15");
		vbtn[kBtn7]->label("16");
		vbtn[kBtn8]->label("17");
		vbtn[kBtn9]->label("18");
		bFrontNine = false;		
	} else {
		vbtn[kBtn1]->label("1");
		vbtn[kBtn2]->label("2");
		vbtn[kBtn3]->label("3");
		vbtn[kBtn4]->label("4");
		vbtn[kBtn5]->label("5");
		vbtn[kBtn6]->label("6");
		vbtn[kBtn7]->label("7");
		vbtn[kBtn8]->label("8");
		vbtn[kBtn9]->label("9");	
		bFrontNine = true;				
	}
	for (auto itr : vbtn) 
		itr->value(0); // all off 
	vbtn[kBtn1]->value(1);	
	vbtn[kBtnT]->value(1);
}

#if USEGPS
void setRefMarker() {
    LatLng ll;
	ll.lat = 0;
	ll.lng = 0;
    size_t n = 10;
	
	vector<string> v(vGPGGA.end() - std::min(vGPGGA.size(), n), vGPGGA.end());
	
	for ( auto itr : v ) {
		if (myGPS.isValidGGA(itr)) {
		  myGPS.setValuesGGA(itr);
		  ll.lat += myGPS.latitude;
		  ll.lng += myGPS.longitude;
		}
	}
	
	ll.lat /= v.size();
	ll.lng /= v.size();
	ostringstream oss;
	oss << "Lat: " << ll.lat << " Lng: " << ll.lng 
	    << " GGAs: " << vGPGGA.size()
	    << " MKRs: " << v.size();
	my_input->value(oss.str().c_str());
	vMarkers = v;
	currentRefMarker = ll;
}
#endif

static void updateYardage(string s) {
    boxYardage->label(s.c_str());
    boxYardage->redraw();
}

static void updateYardage(double d) {
    ostringstream oss;
    unsigned int ui = static_cast<unsigned int>(d);
    oss << ui;
    updateYardage(oss.str().c_str());
}

void handleWriteMarker() {
	#if USEGPS
		string fname = getFilename();
		if ( fname.empty() )
			return;
		
		ofstream file(fname.c_str());
		for (auto itr : vMarkers )
			file << itr;
		file.close();
		vMarkers.clear();
		
		string s = fname + " written";
		my_input->value( s.c_str() );
	#endif
}

void handleWriteAll() {
	#if USEGPS
		string fname = "WalkTheCourse.txt";
		
		ofstream file(fname.c_str());
		for (auto itr : vGPGGA )
			file << itr;
		file.close();
		
		string s = fname + " written";
		my_input->value( s.c_str() );
	#endif
}

static void Button_CB(Fl_Widget *w, void *data) {
	Fl_Button * b = static_cast<Fl_Button *>(w);
    int id = (int)data;
    
    switch (id ) {
		case kBtn1:
		case kBtn2:
		case kBtn3:
		case kBtn4:
		case kBtn5:
		case kBtn6:
		case kBtn7:
		case kBtn8:
		case kBtn9:
			vbtn[kBtn1]->value(0);
			vbtn[kBtn2]->value(0);
			vbtn[kBtn3]->value(0);
			vbtn[kBtn4]->value(0);
			vbtn[kBtn5]->value(0);
			vbtn[kBtn6]->value(0);
			vbtn[kBtn7]->value(0);
			vbtn[kBtn8]->value(0);
			vbtn[kBtn9]->value(0);
			b->value(1);
			currentHole = id+1;
			cout << "pressed button = " << currentHole << endl;
            hv->redraw();
			break;
		case kBtnT:
		case kBtnM:
		case kBtnG:
			vbtn[kBtnT]->value(0);
			vbtn[kBtnM]->value(0);
			vbtn[kBtnG]->value(0);
			b->value(1);
			break;
		case kBtnFB: 
			handleBtnFB();
			break;

		case kBtnMark:
		#if USEGPS
			setRefMarker();
		#endif
			break;

		case kBtnWriteMarker:
		    handleWriteMarker();
			break;

		case kBtnWriteAll:
			handleWriteAll();
			break;

		default:
			cout << "In Button_CB: default case should never be called" << endl;
			break;
	}
}

void setupButtons(Fl_Window *win) {
	Fl_Input *in;               // input preview
	Fl_Callback *enter_cb;      // callback when user hits 'enter'
	void *enter_data;
	
	int X=kLeftMargin;
	int Y=10;
	int W=100;
	int H=140;
	const int kDeltaX = 8;

	// Numeric keypad
	int colstart = X;
	int	col = colstart;
	int	row = Y;
	int num;

	num = kBtn1; 
	vbtn.push_back(new Fl_Button(col,row, kBtnSize, kBtnSize,  "1"));  
	vbtn[kBtn1]->callback(Button_CB, (void *)num); 
	col += vbtn[kBtn1]->w() + kDeltaX;
	
	num = kBtn2; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "2"));   
	vbtn[kBtn2]->callback(Button_CB, (void *)num); 
	col += vbtn[kBtn2]->w();
	col=colstart; 
	row += vbtn[kBtn2]->h();
	
	num = kBtn3; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "3"));
    vbtn[kBtn3]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn3]->w() + kDeltaX;
		
	num = kBtn4; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "4"));
    vbtn[kBtn4]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn4]->w();
	col=colstart; 
	row += vbtn[kBtn4]->h();
	
	num = kBtn5; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "5"));
    vbtn[kBtn5]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn5]->w() + kDeltaX;

	num = kBtn6; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "6"));
    vbtn[kBtn6]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn6]->w();
	col=colstart; 
	row += vbtn[kBtn6]->h();
	
	num = kBtn7; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "7"));
    vbtn[kBtn7]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn7]->w() + kDeltaX;

	num = kBtn8; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "8"));
    vbtn[kBtn8]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn8]->w();
	col=colstart; 
	row += vbtn[kBtn8]->h();

	num = kBtn9; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "9"));
    vbtn[kBtn9]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtn9]->w() + kDeltaX;
	
	num = kBtnT; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "T")); 	
	vbtn[kBtnT]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtnT]->w();
	col=colstart; 
	row += vbtn[kBtnT]->h();
	
	num = kBtnM; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "M"));
    vbtn[kBtnM]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtnM]->w() + kDeltaX;
	
	num = kBtnG; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "G"));
    vbtn[kBtnG]->callback(Button_CB, (void *)num); 
    col += vbtn[kBtnG]->w();
	col=colstart; 
	row += vbtn[kBtnG]->h();
	
	num = kBtnFB; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,"F/B"));  
	vbtn[kBtnFB]->callback(Button_CB, (void *)num); 
	vbtn[kBtnFB]->labelfont(1);
	vbtn[kBtnFB]->labelsize(24);	
	col += vbtn[kBtnFB]->w() + kDeltaX;

	num = kBtnMark; 
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,"Mark")); 
	vbtn[kBtnMark]->callback(Button_CB, (void *)num); 
	vbtn[kBtnMark]->labelfont(1);
	vbtn[kBtnMark]->labelsize(24);	
	col=colstart; 
	row += vbtn[kBtnMark]->h() + kDeltaX;

	num = kBtnWriteMarker; 
	btnWrite = new Fl_Button(col, row, kBtnSize, kBtnSize, "Write\nMark");
	vbtn.push_back(btnWrite);
	vbtn[kBtnWriteMarker]->labelfont(1);
	vbtn[kBtnWriteMarker]->labelsize(20);	
	btnWrite->callback(Button_CB, (void *)num);
	col += vbtn[kBtnWriteMarker]->w() + kDeltaX;

	num = kBtnWriteAll; 
	btnWrite = new Fl_Button(col, row, kBtnSize, kBtnSize, "Write\nAll");
	vbtn.push_back(btnWrite);
	vbtn[kBtnWriteAll]->labelfont(1);
	vbtn[kBtnWriteAll]->labelsize(20);	
	btnWrite->callback(Button_CB, (void *)num);
	col=colstart; 
	row += vbtn[kBtnWriteAll]->h() + kDeltaX;

	boxYardage = new Fl_Box(FL_FRAME_BOX, col, row, kBtnSize*2+kDeltaX, kBtnSize, 0);
    boxYardage->labeltype(FL_NORMAL_LABEL);
    boxYardage->align(FL_ALIGN_CENTER);
    boxYardage->labelfont(1);
    boxYardage->labelsize(64);
    boxYardage->labelcolor(FL_BLACK);
    boxYardage->color(FL_YELLOW);
    updateYardage(strDistFromMark);
	
	enter_cb = 0;
	enter_data = 0;
	
	for (int i = 0; i < kBtnFB; ++i) {
		vbtn[i]->labelfont(1);
		vbtn[i]->labelsize(48);	
	}
	for (auto itr : vbtn) {
	    itr->color(FL_WHITE);
	    itr->down_color(FL_YELLOW);
	}
	
	// INITIAL STATE
	vbtn[kBtn1]->value(1);
	vbtn[kBtnT]->value(1);

}

string getFilename() {
    string fname = "";
    string h = getHoleName();
    string m = getMarkerName();

    if (h.empty()) {
   		my_input->value( "Select a hole. Try again" );
    } else if (m.empty()) {
   		my_input->value( "Select a marker: T M G. Try again" );
    } else {    	   	
		fname = getHoleName() + "_" + getMarkerName() + ".txt";
	}
	return fname;
}


#if USEGPS
gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

bool isgpsup() {
	bool ok = false;
    for(int i = 0; i < 5; ++i) {
        //For version 3.7

        if (gps_rec.stream(WATCH_ENABLE|WATCH_NMEA) == NULL) {
            cout << "No GPSD running. Retry to connect in " << RETRY_TIME << " seconds." << endl;
            usleep(RETRY_TIME * ONE_SECOND);
            continue;    // It will try to connect to gpsd again
        }
        else {
          ok = true;
        }
    }
    return ok;
}


double nema2utm(double nmea) {
	double deg, min, min60, sec, sec60, dec_deg;
	deg = floor(nmea/100);
	min = floor(nmea - deg*100);
	min60 = min / 60.0;
	sec = nmea - (deg*100 + min);
	sec60 = sec / 60.0;
	dec_deg = deg + min60 + sec60;
// 	cout << "nmea\t" << nmea;
// 	cout << "\tdeg\t" << deg;
// 	cout << "\tmin\t" << min;
// 	cout << "\tmin60\t" << min60;
// 	cout << "\tsec\t" << sec;
// 	cout << "\tsec60\t" << sec60;
//	cout << "\tdec_deg\t" << dec_deg << endl;
	return dec_deg;
}

void updateDistanceFromMarkerUTM(string strCurrent, const LatLng rLL) {
  // C2UTM method
  	LL2UTM latlon; //	JACK C2UTM
  	LL2UTM rlatlon; //	r for reference
	double rlt, lt;
	double rlg, lg;
	double d;

    if (nowvGPGGAsz == oldvGPGGAsz)
    	return;
	if (myGPS.isValidGGA(strCurrent)) {
		myGPS.setValuesGGA(strCurrent);
		
		rlt = nema2utm(rLL.lat);
		rlg = nema2utm(-rLL.lng);
		rlatlon.setLatLon(rlt ,rlg);
        rlatlon.convert2UTM();

		lt = nema2utm(myGPS.latitude);
		lg = nema2utm(-myGPS.longitude);		
		latlon.setLatLon(lt,lg);
		latlon.convert2UTM();

        d = sqrt( pow(-(latlon.UTMEast-rlatlon.UTMEast), 2) + pow(latlon.UTMNorth-rlatlon.UTMNorth, 2) );
        d *= 1.0936139; // meters to yards
		updateYardage(d);
		oldvGPGGAsz = nowvGPGGAsz;
	}
}

// Handler for add_fd() -- called whenever the simplegps command outputs a new line of data
// Note: FL_SOCKET as 1st argument is used to fix a compiler error(!) on Windows 64-bit.
// Unfortunately we need this in FLTK 1.3 - should hopefully be fixed in 1.4 with a better solution.
void HandleFD(FL_SOCKET fd, void *data) {
  char s[1024];
  string str;
  int counter = 0;
  
  if ( fgets(s, 1023, G_fp) == NULL ) {		// read the line of data
    Fl::remove_fd(fileno(G_fp));		// command ended? disconnect callback
    pclose(G_fp);				// close the descriptor
    return;
  }
  str = s;
  vGPGGA.push_back( str );
  nowvGPGGAsz = vGPGGA.size();
  updateDistanceFromMarkerUTM(str, currentRefMarker);
  
}
#endif

int main(int argc, char **argv) {
  //#if USEGPS
  //    if (isgpsup() == false) {
  //   	cout << "No GPS found" << endl;
  //   	return 0;
  //  }
//#endif
    ngc = new Course(5);
    ngc->readCourse();
    
    win = new Fl_Window(10, 40, 480, 800, "NGC Golf");
    win->begin();
    hv = new HoleView(10,40,280,700,0);
    my_input = new Fl_Input(10,10,274,30,"");
	setupButtons(win);
    win->end();
 
    win->resizable(win);
    win->show();
    currentHole = 1;
    hv->make_current();
    hv->makeList();
    hv->show();
    hv->draw();
#if USEGPS    
// from howto-add_fd_popen()
  if ( ( G_fp = popen(SIMPLEGPS_CMD, "r") ) == NULL ) {	// start the external unix command
    perror("popen failed");
    return(1);
  }
  Fl::add_fd(fileno(G_fp), HandleFD, 0);	// setup a callback for the popen()ed descriptor
#endif
 
    return(Fl::run());
}

