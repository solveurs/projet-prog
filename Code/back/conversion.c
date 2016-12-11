/**
 @file conversion.c
 
 @brief fonctions de conversion diverses
 */
#include "../headers/conversion.h"



/**
 conversion de lambert 93 aux coord GPS

 @param x un pointeur sur coord x lambert --> lat GPS
 @param y un pointeur sur coord y lambert --> long GPS
 */
void lambert93ToGPS(double * x, double * y)
{
     double n       = 0.7256077650;
	 double c		= 11753572;
     double Xs      = 700000.0;
     double Ys      = 12655612.050;
     double l0      = 0.05235987;
     double e       = 0.08248325676;
     double eps     = 0.00001;

     double X = *x;
     double Y = *y;

     double R = sqrt(((X - Xs) * (X - Xs)) + ((Y - Ys) * (Y - Ys)));
     double g = atan((X - Xs) / (Ys - Y));
     double l = l0 + (g / n);
     double L = -(1 / n) * log(fabs(R / c));
     double phi0 = 2 * atan(exp(L)) - M_PI_2;
     double phiprec = phi0;
     double phii = 2 * atan((pow(((1 + e * sin(phiprec)) / (1 - e * sin(phiprec))), e / 2.0) * exp(L))) - M_PI_2;
     while (!(fabs(phii - phiprec) < eps)) {
          phiprec = phii;
          phii = 2 * atan((pow(((1 + e * sin(phiprec)) / (1 - e * sin(phiprec))), e / 2.0) * exp(L))) - M_PI_2;
     }
     double phi = phii;

     *x = l * 180.0 / M_PI;
     *y = phi * 180.0 / M_PI;
}

/**
 convertie une date (en ms depuis 1970) en date lisible

 @param parDate date en ms depuis 1970

 @return une struct tm * avec la date
 */
struct tm * timestampToReadable(const long parDate)
{
	const time_t varT = parDate;
	return localtime(&varT);
}

/**
 convertie une date (en ms depuis 1970) en chaine de caractère

 @param parDate date en ms depuis 1970

 @return une chaine de caractère avec la date formatée.
 */
char * timestampToString(const long parDate)
{
	char * buf;
	buf = (char*)calloc(100,sizeof(char));
	strftime(buf, 100, "%Y-%m-%d %H:%M:%S", timestampToReadable(parDate));
	return buf;
}
