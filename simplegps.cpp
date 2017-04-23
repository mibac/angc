/* 
 g++ simplegps.cpp -o simplegps -g -std=c++11 -lgps
*/
#include <iostream>
#include <string>
#include <unistd.h>
#include "libgpsmm.h"

using namespace std;

#define WAITING_TIME 5000000
#define RETRY_TIME 5
#define ONE_SECOND 1000000

int main(void)
{
    for(;;){
        //For version 3.7
        gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

        if (gps_rec.stream(WATCH_ENABLE|WATCH_NMEA) == NULL) {
            cout << "No GPSD running. Retry to connect in " << RETRY_TIME << " seconds." << endl;
            usleep(RETRY_TIME * ONE_SECOND);
            continue;    // It will try to connect to gpsd again
        }

        const char* buffer = NULL;
        string str;

        for (;;) {
            struct gps_data_t* newdata;

            if (!gps_rec.waiting(WAITING_TIME))
                continue;

            if ((newdata = gps_rec.read()) == NULL) {
                cerr << "Read error.\n";
                break;
            } else {
                buffer = gps_rec.data();
				str = buffer;
                // We print the NMEA sentences!
//                cout << "***********" << endl;

                size_t found = str.find("GPGGA");
  				if (found != string::npos)
                	cout << str << endl;            
				
                // usleep(1000000);
            }
        }
    }
}
