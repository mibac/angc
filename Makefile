CXXFLAGS = -g -std=c++11 -Wall -I/home/pi/projects/FLTK-master -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/home/pi/projects/FLTK-master/jpeg -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT
LDFLAGS = /home/pi/projects/FLTK-master/lib/libfltk_gl.a -lGLU -lGL /home/pi/projects/FLTK-master/lib/libfltk.a -lXrender -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lgps

all: aNGCApp

aNGCApp: markGps.o C2UTM.o CExitBtn.o CHoleBtn.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o  CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg2.o  globals.o CYellowBtn.o CGPStime.o CScorecard.o CScorecardDlg.o
	g++ -o aNGCApp markGps.o C2UTM.o CExitBtn.o CHoleBtn.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg2.o  globals.o CYellowBtn.o CGPStime.o  CScorecard.o CScorecardDlg.o $(LDFLAGS)
markGps.o: markGps.cpp C2UTM.h CExitBtn.h CHoleBtn.h CHolesPopup.h CLatLng.h  Course.h gps.h HoleView.h CClubPopup.h CScoreBtn.h CScoreDlg2.h  globals.h CYellowBtn.h CGPStime.h  CScorecard.h CScorecardDlg.h
	g++ -c $<  $(CXXFLAGS)

C2UTM.o: C2UTM.cpp C2UTM.h
	g++ -c $< $(CXXFLAGS)

CLatLng.o: CLatLng.cpp CLatLng.h gps.h C2UTM.h globals.h
	g++ -c $<  $(CXXFLAGS)

CExitBtn.o: CExitBtn.cpp CExitBtn.h CLatLng.h CHoleBtn.h CClubBtn.h globals.h
	g++ -c $<  $(CXXFLAGS)

CHoleBtn.o: CHoleBtn.cpp CHoleBtn.h CHolesPopup.h CLatLng.h globals.h
	g++ -c $<  $(CXXFLAGS)

CHolesPopup.o: CHolesPopup.cpp CHolesPopup.h
	g++ -c $<  $(CXXFLAGS)

Course.o: Course.cpp Course.h C2UTM.h
	g++ -c $<  $(CXXFLAGS)

gps.o: gps.cpp gps.h
	g++ -c $<  $(CXXFLAGS)

HoleView.o: HoleView.cpp HoleView.h Course.h globals.h
	g++ -c $<  $(CXXFLAGS)

CClubPopup.o: CClubPopup.cpp CClubPopup.h
		g++ -c $<  $(CXXFLAGS)

CClubBtn.o: CClubBtn.cpp CClubBtn.h CClubPopup.h CLatLng.h
			g++ -c $<  $(CXXFLAGS)

CScoreDlg2.o: CScoreDlg2.cpp CScoreDlg2.h globals.h  CScorecard.h
			g++ -c $<  $(CXXFLAGS)

CScoreBtn.o: CScoreBtn.cpp CScoreBtn.h CScoreDlg2.h
			g++ -c $<  $(CXXFLAGS)

CYellowBtn.o: CYellowBtn.cpp 	CYellowBtn.h globals.h CGPStime.h CHoleBtn.h
	g++ -c $<  $(CXXFLAGS)

globals.o: globals.cpp globals.h
	g++ -c $<  $(CXXFLAGS)

CGPStime.o: CGPStime.cpp CGPStime.h
	g++ -c $<  $(CXXFLAGS)

CScorecard.o: CScorecard.cpp CScorecard.h globals.h
	g++ -c $<  $(CXXFLAGS)

CScorecardDlg.o: CScorecardDlg.cpp CScorecardDlg.h CScorecard.h
	g++ -c $<  $(CXXFLAGS)

clean:
	rm *.o
