CXXFLAGS = -g \
	-std=c++11 \
	-Wall \
	-I/home/pi/projects/FLTK-master \
	-I/usr/include/cairo \
	-I/usr/include/glib-2.0 \
	-I/usr/lib/arm-linux-gnueabihf/glib-2.0/include \
	-I/usr/include/pixman-1 \
	-I/usr/include/freetype2 \
	-I/usr/include/libpng12 \
	-I/home/pi/projects/FLTK-master/jpeg \
	-I/usr/lib/arm-linux-gnueabihf/glib-2.0/include \
	-D_LARGEFILE_SOURCE \
	-D_LARGEFILE64_SOURCE \
	-D_FILE_OFFSET_BITS=64 \
	-D_THREAD_SAFE \
	-D_REENTRANT

LDFLAGS = -lGLU \
	-lGL \
	-lXrender \
	-lXfixes \
	-lXext \
	-lXft \
	-lfontconfig \
	-lpthread \
	-ldl \
	-lm \
	-lX11 \
	-lgps \
	-lfltk_images \
	/home/pi/projects/FLTK-master/lib/libfltk_gl.a \
	/home/pi/projects/FLTK-master/lib/libfltk.a

all: aNGCApp

aNGCApp: markGps.o \
C2UTM.o \
CExitBtn.o \
CHoleBtn.o \
CHolesPopup.o \
CLatLng.o \
Course.o \
gps.o \
HoleView.o \
CScoreDlg2.o \
globals.o \
CTimeDisplay.o \
CGPStime.o \
CScorecard.o \
CScorecardDlg.o \
CFrontBackBtn.o \
CClubDlg.o \
CClubcard.o \
dout.o \
CHistoryDlg.o \
Fl_Image_Button.o
	g++ -o aNGCApp \
		markGps.o \
		C2UTM.o \
		CExitBtn.o \
		CHoleBtn.o \
		CHolesPopup.o \
		CLatLng.o \
		Course.o \
		gps.o \
		HoleView.o \
		CScoreDlg2.o \
		globals.o \
		CTimeDisplay.o \
		CGPStime.o \
		CScorecard.o \
		CScorecardDlg.o \
		CFrontBackBtn.o \
		CClubDlg.o \
		CClubcard.o \
		dout.o \
		CHistoryDlg.o \
		Fl_Image_Button.o \
		$(LDFLAGS)

markGps.o: markGps.cpp \
C2UTM.h \
CExitBtn.h \
CHoleBtn.h \
CHolesPopup.h \
CLatLng.h \
Course.h \
gps.h \
HoleView.h \
CScoreDlg2.h \
globals.h \
CTimeDisplay.h \
CGPStime.h \
CScorecard.h \
CScorecardDlg.h \
CClubDlg.h \
CClubcard.h \
dout.h \
CHistoryDlg.h \
Fl_Image_Button.h
	g++ -c $<  $(CXXFLAGS)

C2UTM.o: C2UTM.cpp C2UTM.h
	g++ -c $< $(CXXFLAGS)

CLatLng.o: CLatLng.cpp CLatLng.h gps.h C2UTM.h globals.h
	g++ -c $<  $(CXXFLAGS)

CExitBtn.o: CExitBtn.cpp CExitBtn.h CLatLng.h CHoleBtn.h globals.h
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

CScoreDlg2.o: CScoreDlg2.cpp CScoreDlg2.h globals.h  CScorecard.h  CClubcard.h
			g++ -c $<  $(CXXFLAGS)

CTimeDisplay.o: CTimeDisplay.cpp 	CTimeDisplay.h globals.h CGPStime.h CHoleBtn.h
	g++ -c $<  $(CXXFLAGS)

globals.o: globals.cpp globals.h
	g++ -c $<  $(CXXFLAGS)

CGPStime.o: CGPStime.cpp CGPStime.h
	g++ -c $<  $(CXXFLAGS)

CScorecard.o: CScorecard.cpp CScorecard.h globals.h CFrontBackBtn.h
	g++ -c $<  $(CXXFLAGS)

CScorecardDlg.o: CScorecardDlg.cpp CScorecardDlg.h CScorecard.h
	g++ -c $<  $(CXXFLAGS)

CFrontBackBtn.o: CFrontBackBtn.cpp CFrontBackBtn.h globals.h
	g++ -c $<  $(CXXFLAGS)

CClubDlg.o: CClubDlg.cpp CClubDlg.h globals.h
	g++ -c $<  $(CXXFLAGS)

CClubcard.o: CClubcard.cpp CClubcard.h globals.h Fl_Image_Button.h
	g++ -c $<  $(CXXFLAGS)

dout.o: dout.cpp dout.h
	g++ -c $<  $(CXXFLAGS)

CHistoryDlg.o: CHistoryDlg.cpp CHistoryDlg.h
	g++ -c $<  $(CXXFLAGS)

Fl_Image_Button.o: Fl_Image_Button.cpp Fl_Image_Button.h
	g++ -c $<  $(CXXFLAGS)

clean:
	rm *.o
