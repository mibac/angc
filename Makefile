CXXFLAGS = -g -std=c++11 -Wall -I/home/pi/projects/FLTK-master -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/home/pi/projects/FLTK-master/jpeg -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT
LDFLAGS = /home/pi/projects/FLTK-master/lib/libfltk_gl.a -lGLU -lGL /home/pi/projects/FLTK-master/lib/libfltk.a -lXrender -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lgps

all: aNGCApp

aNGCApp: markGps.o C2UTM.o CExitBtn.o CHoleButton.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o  CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg.o CScores.o CScoreStats.o globals.o
	g++ -o aNGCApp markGps.o C2UTM.o CExitBtn.o CHoleButton.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg.o CScores.o CScoreStats.o globals.o $(LDFLAGS)

markGps.o: markGps.cpp C2UTM.cpp CExitBtn.cpp CHoleButton.cpp CHolesPopup.cpp CLatLng.cpp  Course.cpp gps.cpp HoleView.cpp CClubPopup.cpp CScoreBtn.cpp CScoreDlg.cpp CScores.cpp CScoreStats.cpp globals.cpp
	g++ -c $<  $(CXXFLAGS)

C2UTM.o: C2UTM.cpp C2UTM.h
	g++ -c $< $(CXXFLAGS)

CLatLng.o: CLatLng.cpp CLatLng.h gps.cpp C2UTM.cpp utils.h globals.cpp
	g++ -c $<  $(CXXFLAGS)

CExitBtn.o: CExitBtn.cpp CExitBtn.h CLatLng.cpp CHoleButton.cpp CClubBtn.cpp globals.cpp
	g++ -c $<  $(CXXFLAGS)

CHoleButton.o: CHoleButton.cpp CHoleButton.h CHolesPopup.cpp CLatLng.cpp
	g++ -c $<  $(CXXFLAGS)

CHolesPopup.o: CHolesPopup.cpp CHolesPopup.h
	g++ -c $<  $(CXXFLAGS)

Course.o: Course.cpp Course.h C2UTM.cpp
	g++ -c $<  $(CXXFLAGS)

gps.o: gps.cpp gps.h
	g++ -c $<  $(CXXFLAGS)

HoleView.o: HoleView.cpp HoleView.h Course.cpp globals.cpp
	g++ -c $<  $(CXXFLAGS)

CClubPopup.o: CClubPopup.cpp CClubPopup.h
		g++ -c $<  $(CXXFLAGS)

CClubBtn.o: CClubBtn.cpp CClubBtn.h CClubPopup.cpp CLatLng.cpp
			g++ -c $<  $(CXXFLAGS)

CScoreDlg.o: CScoreDlg.cpp CScoreDlg.h CScoreStats.cpp globals.cpp
			g++ -c $<  $(CXXFLAGS)

CScoreBtn.o: CScoreBtn.cpp CScoreBtn.h CScoreDlg.cpp
			g++ -c $<  $(CXXFLAGS)

CScores.o: CScores.cpp CScores.h globals.cpp
			g++ -c $<  $(CXXFLAGS)

CScoresStats.o: CScoresStats.cpp CScoresStats.h CScores.cpp
			g++ -c $<  $(CXXFLAGS)

globals.o: globals.cpp globals.h
	g++ -c $<  $(CXXFLAGS)

clean:
	rm *.o
