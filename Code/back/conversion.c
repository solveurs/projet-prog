#include "../headers/conversion.h"


/**
 * \fn void lambert93(double * x, double * y)
 * \brief conversion de coordonnée lambert93 vers GPS long/lat
 * \param x X en coord de Lambert convertie en longitude
 * \param y Y en coord de Lambert convertie en latitude
 */
void lambert93(double * x, double * y)
{
     double n       = 0.7256077650;
     double c       = 11754255.426;
     double Xs      = 700000.0;
     double Ys      = 12655612.050;
     double l0      = 0.0524;
     double e       = 0.08248325676;
     double eps     = 0.0001;

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

int main()
{
     //double x=1029705.0830, y=272723.8490;
     double x=655413, y=6664791;
     lambert93(&x,&y);

     printf("Ouh lala ça marche ??? %lf°N %lf°E",x, y);

     return 0;
}
