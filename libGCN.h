#include <math.h>
#include <float.h>
#include <stdio.h>
const double pi = M_PI;
 const int er_km = 6378 ;
const double esp= DBL_EPSILON ;
/********************* BASIC FUNC *************************/
// ALL THE LATER FORMULAS ARE FOR RADIANS


double RAD2DEG(double RAD);
double DEG2RAD (double DEG);
double RAD2KM (double RAD);
double KM2RAD (double KM);

typedef struct CRD {
    double LAT, LNG;
} CRD ; // CRD or coordinates LAT latitude and LNG longitude

CRD INIT_CRD_DEG( double LAT, double LNG); // CRD from lat and lng as decimal deg

CRD INIT_CRD_RAD( double LAT, double LNG);// CRD from lat and lng as radians

CRD GET_CRD_LNG_STR_END(double LNG,
                        CRD    START,
                        CRD    END);//CRD G

void SHOW_CRD_DEG (CRD crd); // prints CRD in DEG

void SHOW_CRD_RAD (CRD crd); // prints CRD in RAD

typedef struct {
    CRD START;
    CRD END;
    double CRS;
    double DST;
} RTE;

double GET_DIST(CRD START, CRD END);

double GET_CRS(CRD START, CRD END,double DST);

RTE INIT_RTE_STR_END(CRD START, CRD END);

CRD CRD_ON_CRS_BY_DST(CRD START, double CRS, double DST);

RTE INIT_RTE_STR_CRS_DST(CRD START, double CRS, double DST );

CRD LON_RTE_GET_LAT(double LNG, RTE rte);