/* je compile command
g++ markGps.cpp gps.cpp calcDist.cpp -o markGps -g  -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -D_LARGEFILE_SOURCE -D_LARGEFILE64 -std=c++11 -lfltk -lgps 
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
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/glu.h>


// #include  <FL/Enumerations.H>

#ifndef GPS_H
#include "gps.h"
#endif

#ifndef CALC_DISTANCE_H
#include "calcDist.h"
#endif

#ifndef C2UTM_hpp
#include "C2UTM.hpp"
#endif

#include "libgpsmm.h"

using namespace std;

// GLOBALS
#define USEGPS 0

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
const int kBtnG = 10;
const int kBtnM = 11;
const int kBtnFB = 12;
const int kBtnMark = 13;
const int kBtnWrite = 14;

const int kBtnSize = 80;

const int kLeftMargin = 300;

const int WAITING_TIME = 5000000;
const int RETRY_TIME = 5;
const int ONE_SECOND = 1000000;
const int kNumMarks = 10;

bool bFrontNine = true;
bool bGoodFilename = false;

float refMarkf = 0.0;
float nowMarkf = 0.0;

struct LatLng {
  double lat;
  double lng;
};

class HoleView: public Fl_Gl_Window {
 public:
   HoleView(int x,int y,int w,int h,const char *l):Fl_Gl_Window(x,y,w,h,l){}
   void makeList();
   void draw();
};


void HoleView::makeList() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D((double) 0,(double) 300,(double) 0,(double) 700);
 // glViewport(0,0,pixel_w(),pixel_h());
  glMatrixMode(GL_MODELVIEW);
        glDeleteLists(1,1);
        glNewList(1,GL_COMPILE);
           glColor3d(153.0/255.0,1.0,153.0/255.0);
           glClear(GL_COLOR_BUFFER_BIT); 
           glBegin(GL_POLYGON);
             glVertex2d(0,100);
             glVertex2d(300,100);
             glVertex2d(300,700);
             glVertex2d(0,700);
           glEnd();
         glEndList();
}

void HoleView::draw() {
    glCallList(1);
}
   
LatLng currentRefMarker;


Fl_Window *win;
Fl_Input *my_input;
Fl_Box *boxYardage;
Fl_Button *btnMark;
Fl_Button *btnWrite;
HoleView *hv; 

FILE *G_fp = NULL;
const char *SIMPLEGPS_CMD = "simplegps";	

string strDistFromMark("150");
//string fname;
vector<Fl_Button *> vbtn; // the hole and marker pushbuttons
vector<string> vGPGGA;
vector<string> vMarkers;
int oldvGPGGAsz =0;
int nowvGPGGAsz =0;
GPS myGPS;

// Prototypes
void writeFile_CB(Fl_Widget *);
void mark_CB(Fl_Widget *);
void setRefMarker();
void setupYardage(string s);

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
	if (vbtn[kBtnT]->value() == 1) str = "BlueTeeMarker";
	else if (vbtn[kBtnM]->value() == 1) str = "150YardMarker";
	else if (vbtn[kBtnG]->value() == 1) str = "MiddleOfGreen";
	return str;
}

bool isBtn1to9(Fl_Button* b) {
	if (vbtn[kBtn1] == b) return true;
	else if (vbtn[kBtn2] == b) return true;
	else if (vbtn[kBtn3] == b) return true;
	else if (vbtn[kBtn4] == b) return true;
	else if (vbtn[kBtn5] == b) return true;
	else if (vbtn[kBtn6] == b) return true;
	else if (vbtn[kBtn7] == b) return true;
	else if (vbtn[kBtn8] == b) return true;
	else if (vbtn[kBtn9] == b) return true;
	else return false;
}

bool isBtnTMG(Fl_Button *b) {
	if (vbtn[kBtnT] == b) return true;
	else if (vbtn[kBtnM] == b) return true;
	else if (vbtn[kBtnG] == b) return true;
	else return false;
}

void handleBtns(Fl_Button * b) {
// all off
	if (isBtn1to9(b)) {
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
		vGPGGA.clear();
	}
	else if (isBtnTMG(b)) {
		vbtn[kBtnT]->value(0);
		vbtn[kBtnM]->value(0);
		vbtn[kBtnG]->value(0);
		b->value(1);	
	}
	else if (b == vbtn[kBtnFB]) {
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
	}
	else if (b == vbtn[kBtnMark]) {
//		for (auto itr : vbtn) itr->value(0); // all off 
	}

	else if (b == vbtn[kBtnWrite]) {
//		for (auto itr : vbtn) itr->value(0); // all off 
	}
}

static void Button_CB(Fl_Widget *w, void *data) {
    
	handleBtns((Fl_Button *)w);
}

void setupKeypad(Fl_Window *win) {
	Fl_Input *in;               // input preview
	Fl_Callback *enter_cb;      // callback when user hits 'enter'
	void *enter_data;
	
	//	const int kBtnSize = 20;
	int X=kLeftMargin;
	int Y=10;
	int W=100;
	int H=140;
	const int kDeltaX = 8;

	// Numeric keypad
	int colstart = X;
	int	col = colstart;
	int	row = Y;

	vbtn.push_back(new Fl_Button(col,row, kBtnSize, kBtnSize,  "1"));   
	vbtn[0]->callback(Button_CB, (void*)win); 
	col += vbtn[0]->w() + kDeltaX;
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "2"));   
	vbtn[1]->callback(Button_CB, (void*)win); 
	col += vbtn[1]->w();
	col=colstart; 
	row += vbtn[1]->h();
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "3"));
    vbtn[2]->callback(Button_CB, (void*)win); 
    col += vbtn[2]->w() + kDeltaX;
		
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "4"));
    vbtn[3]->callback(Button_CB, (void*)win); 
    col += vbtn[3]->w();
	col=colstart; 
	row += vbtn[3]->h();
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "5"));
    vbtn[4]->callback(Button_CB, (void*)win); 
    col += vbtn[4]->w() + kDeltaX;

	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "6"));
    vbtn[5]->callback(Button_CB, (void*)win); 
    col += vbtn[5]->w();
	col=colstart; 
	row += vbtn[5]->h();
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "7"));
    vbtn[6]->callback(Button_CB, (void*)win); 
    col += vbtn[6]->w() + kDeltaX;

	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "8"));
    vbtn[7]->callback(Button_CB, (void*)win); 
    col += vbtn[7]->w();
	col=colstart; 
	row += vbtn[7]->h();

	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "9"));
    vbtn[8]->callback(Button_CB, (void*)win); 
    col += vbtn[8]->w() + kDeltaX;
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "T")); 	
	vbtn[9]->callback(Button_CB, (void*)win); 
    col += vbtn[9]->w();
	col=colstart; 
	row += vbtn[9]->h();
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "M"));
    vbtn[10]->callback(Button_CB, (void*)win); 
    col += vbtn[10]->w() + kDeltaX;
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,  "G"));
    vbtn[11]->callback(Button_CB, (void*)win); 
    col += vbtn[11]->w();
	col=colstart; 
	row += vbtn[11]->h();
	
	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,"F/B"));  
	vbtn[12]->callback(Button_CB, (void*)win); 
	vbtn[12]->labelfont(1);
	vbtn[12]->labelsize(24);	
	col += vbtn[12]->w() + kDeltaX;

	vbtn.push_back(new Fl_Button(col,row,kBtnSize,kBtnSize,"Mark")); 
	vbtn[13]->callback(mark_CB); 
	vbtn[13]->labelfont(1);
	vbtn[13]->labelsize(24);	
	col=colstart; 
	row += vbtn[13]->h() + kDeltaX;

	// vbtn[14]
	btnWrite = new Fl_Button(col, row, kBtnSize*2+kDeltaX, kBtnSize, "Write File");
	vbtn.push_back(btnWrite);
	vbtn[14]->labelfont(1);
	vbtn[14]->labelsize(24);	
	btnWrite->callback(writeFile_CB);
	col=colstart; 
	row += vbtn[14]->h() + kDeltaX;

	boxYardage = new Fl_Box(FL_FRAME_BOX, col, row, kBtnSize*2+kDeltaX, kBtnSize, 0);
	setupYardage(strDistFromMark);
	
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
}

static void updateYardage(string s) {
    boxYardage->label(s.c_str());
    boxYardage->redraw();
//    win->redraw();
}

static void updateYardage(double d) {
    ostringstream oss;
    unsigned int ui = static_cast<unsigned int>(d);
    oss << ui;
    my_input->value(oss.str().c_str());
    my_input->redraw();
//    win->redraw();
}

void setupYardage(string s) {
    boxYardage->labeltype(FL_NORMAL_LABEL);
    boxYardage->align(FL_ALIGN_CENTER);
    boxYardage->labelfont(1);
    boxYardage->labelsize(64);
    boxYardage->labelcolor(FL_BLACK);
    boxYardage->color(FL_YELLOW);
    updateYardage(s);
}

string getFilename() {
    string fname;
    string h = getHoleName();
    if (h.empty()) {
   		my_input->value(  );
   		bGoodFilename = false;
		return "Select a hole. Try again";
    }

    string m = getMarkerName();
    if (m.empty()) {
   		my_input->value( "Select a marker: T M G. Try again" );
   		bGoodFilename = false;
		return "Select a marker: T M G. Try again";
    }
    	   	
 	fname = "Hole" + getHoleName() + "_" + getMarkerName() + ".txt";
	bGoodFilename = true;
	return fname;
}

void mark_CB(Fl_Widget *) {
#if USEGPS
    setRefMarker();
#endif
}

void writeFile_CB(Fl_Widget *) {
#if USEGPS
    string fname = getFilename();
	
	ofstream file(fname.c_str());
	for (auto itr : vMarkers )
		file << itr;
	file.close();
	vMarkers.clear();
	
	string s = fname + " written";
	my_input->value( s.c_str() );
#endif
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

void updateDistanceFromMarker(string strCurrent, LatLng refLL) {
    if (nowvGPGGAsz == oldvGPGGAsz)
    	return;
   	LatLng curLL;
	double d;
	if (myGPS.isValidGGA(strCurrent)) {
		myGPS.setValuesGGA(strCurrent);
		curLL.lat += myGPS.latitude;
		curLL.lng += myGPS.longitude;
		d = distance_yards(curLL.lat, curLL.lng, refLL.lat, refLL.lng);
		cout << curLL.lat <<"\t" << curLL.lng <<"\t" << refLL.lat <<"\t" << refLL.lng << endl;
		updateYardage(d);
		oldvGPGGAsz = nowvGPGGAsz;
	}
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
//  updateDistanceFromMarker(str, currentRefMarker);
  updateDistanceFromMarkerUTM(str, currentRefMarker);
  
}
#endif


int main(int argc, char **argv) {
#if USEGPS
    if (isgpsup() == false) {
    	cout << "No GPS found" << endl;
    	return 0;
    }
#endif
    win = new Fl_Window(10, 40, 480, 800, "NGC Golf");
    hv = new HoleView(0,50,300,700,0);
    win->end();
    my_input = new Fl_Input(10,10,274,30,"");

	setupKeypad(win);
    win->resizable(win);
    win->show();
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
