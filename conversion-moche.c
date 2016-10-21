#include <stdio.h>
#include <math.h>

void lambert93(float *x, float *y){
      float n =  0.7256077650;
      float c =  11754255.426;
      float Xs = 700000.0;
      float Ys = 12655612.050;
      float l0 = 0.0;                    //longitude en radian de Paris (2°20'14.025" E) par rapport à Greenwich
      float e = 0.08248325676;           //e du NTF (on le change après pour passer en WGS)
      float eps = 0.00001;     // précision
      /***********************************************************
      *  coordonnées dans la projection de Lambert 2 à convertir *
      ************************************************************/
      float X = *x;
      float Y = *y;
      /*
       * Conversion Lambert 2 -> NTF géographique : ALG0004
       */
        float R = sqrt(((X - Xs) * (X - Xs)) + ((Y - Ys) * (Y - Ys)));
        float g = atan((X - Xs) / (Ys - Y));
        float l = l0 + (g / n);
        float L = -(1 / n) * log(abs(R / c));
        float phi0 = 2 * atan(exp(L)) - M_PI_2;
        float phiprec = phi0;
        float phii = 2 * atan((pow(((1 + e * sin(phiprec)) / (1 - e * sin(phiprec))), e / 2.0) * exp(L))) - M_PI_2;
        while (!(abs(phii - phiprec) < eps)) {
                phiprec = phii;
                phii = 2 * atan((pow(((1 + e * sin(phiprec)) / (1 - e * sin(phiprec))), e / 2.0) * exp(L))) - M_PI_2;
        }
        float phi = phii;
    /*
     * Conversion NTF géogra$phique -> NTF cartésien : ALG0009
     */
    float a = 6378249.2;
    float h = 100;         // En mètres
    float N = a / (pow((1 - (e * e) * (sin(phi) * sin(phi))), 0.5));
    float X_cart = (N + h) * cos(phi) * cos(l);
    float Y_cart = (N + h) * cos(phi) * sin(l);
    float Z_cart = ((N * (1 - (e * e))) + h) * sin(phi);
    /*
     * Conversion NTF cartésien -> WGS84 cartésien : ALG0013
     */
    // Il s'agit d'une simple translation
    float XWGS84 = X_cart - 168;
    float YWGS84 = Y_cart - 60;
    float ZWGS84 = Z_cart + 320;
    /*
     * Conversion WGS84 cartésien -> WGS84 géogra$phique : ALG0012
     */
    
    float l840 = 0.04079234433;    // 0.04079234433 pour passer dans un référentiel par rapport au méridien
    // de Greenwich, sinon mettre 0
    
    e = 0.08181919106;              // On change e pour le mettre dans le système WGS84 au lieu de NTF
    a = 6378137.0;
    float P = sqrt((XWGS84 * XWGS84) + (YWGS84 * YWGS84));
    float l84 = l840 + atan(YWGS84 / XWGS84);
    float phi840 = atan(ZWGS84 / (P * (1 - ((a * e * e))
                                / sqrt((XWGS84 * XWGS84) + (YWGS84 * YWGS84) + (ZWGS84 * ZWGS84)))));
    float phi84prec = phi840;
    float phi84i = atan((ZWGS84 / P) / (1 - ((a * e * e * cos(phi84prec))
            / (P * sqrt(1 - e * e * (sin(phi84prec) * sin(phi84prec)))))));
    while (!(abs(phi84i - phi84prec) < eps))
    {
        phi84prec = phi84i;
        phi84i = atan((ZWGS84 / P) / (1 - ((a * e * e * cos(phi84prec))
                / (P * sqrt(1 - ((e * e) * (sin(phi84prec) * sin(phi84prec))))))));
    }
    float phi84 = phi84i;
    float tab[1];
    tab[0]=phi84 * 180.0 / M_PI;
    tab[1]=l84 * 180.0 / M_PI;
}
