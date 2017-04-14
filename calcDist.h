// http://adamchukpa.mcgill.ca/web_ssm/web_GPS.html
// http://adamchukpa.mcgill.ca/web_ssm/web_GPS_ex.html

#ifndef CALC_DISTANCE_H
#define CALC_DISTANCE_H

double convert_longitude(double lng);
double convert_latitude(double lat);
double distance_meters(double lat1, double lng1, double lat2, double lng2,
                       bool print = false);
double distance_yards(double lat1, double lng1, double lat2, double lng2,
                      bool print = false);
double distance_feet(double lat1, double lng1, double lat2, double lng2,
                     bool print = false);
void print_variables();
void print_distance(double lat1, double lng1, double lat2, double lng2);

#endif
