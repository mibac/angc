CXXFLAGS = -g -std=c++11 -Wall -I/home/pi/projects/FLTK-master -I/usr/include/cairo -I/usr/include/glib-2.0 -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/home/pi/projects/FLTK-master/jpeg -I/usr/lib/arm-linux-gnueabihf/glib-2.0/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -D_THREAD_SAFE -D_REENTRANT
LDFLAGS = /home/pi/projects/FLTK-master/lib/libfltk_gl.a -lGLU -lGL /home/pi/projects/FLTK-master/lib/libfltk.a -lXrender -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11 -lgps

all: aNGCApp

aNGCApp: markGps.o C2UTM.o CExitBtn.o CHoleButton.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o  CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg.o CScores.o CScoreStats.o globals.o CYellowBtn.o
	g++ -o aNGCApp markGps.o C2UTM.o CExitBtn.o CHoleButton.o CHolesPopup.o CLatLng.o Course.o  gps.o HoleView.o CClubPopup.o CClubBtn.o CScoreBtn.o CScoreDlg.o CScores.o CScoreStats.o globals.o CYellowBtn.o $(LDFLAGS)

markGps.o: markGps.cpp C2UTM.h CExitBtn.h CHoleButton.h CHolesPopup.h CLatLng.h  Course.h gps.h HoleView.h CClubPopup.h CScoreBtn.h CScoreDlg.h CScores.h CScoreStats.h globals.h CYellowBtn.h
	g++ -c $<  $(CXXFLAGS)

C2UTM.o: C2UTM.cpp C2UTM.h
	g++ -c $< $(CXXFLAGS)

CLatLng.o: CLatLng.cpp CLatLng.h gps.h C2UTM.h utils.h globals.h
	g++ -c $<  $(CXXFLAGS)

CExitBtn.o: CExitBtn.cpp CExitBtn.h CLatLng.h CHoleButton.h CClubBtn.h globals.h CScoreStats.h
	g++ -c $<  $(CXXFLAGS)

CHoleButton.o: CHoleButton.cpp CHoleButton.h CHolesPopup.h CLatLng.h globals.h
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

CScoreDlg.o: CScoreDlg.cpp CScoreDlg.h CScoreStats.h globals.h
			g++ -c $<  $(CXXFLAGS)

CScoreBtn.o: CScoreBtn.cpp CScoreBtn.h CScoreDlg.h
			g++ -c $<  $(CXXFLAGS)

CScores.o: CScores.cpp CScores.h globals.h
			g++ -c $<  $(CXXFLAGS)

CScoresStats.o: CScoresStats.cpp CScoresStats.h CScores.h
			g++ -c $<  $(CXXFLAGS)

CYellowBtn.o: CYellowBtn.cpp 	CYellowBtn.h globals.h

globals.o: globals.cpp globals.h
	g++ -c $<  $(CXXFLAGS)

clean:
	rm *.o
