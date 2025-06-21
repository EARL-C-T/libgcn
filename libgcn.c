#include <stdio.h>
#include <math.h>
#include <float.h>


const double pi = M_PI;
const int er_km = 6378;
const double esp = DBL_EPSILON;

/********************* BASIC FUNC *************************/
// ALL THE LATER FORMULAS ARE FOR RADIANS


double RAD2DEG(double rad)
{
    return rad * 180 / pi;
}
double DEG2RAD(double deg)
{
    return deg * pi / 180;
}
double RAD2KM (double rad)
{
    return rad * er_km;
}
double KM2RAD (double km)
{
  return er_km / km;

}

typedef struct CRD {
    double LAT, LNG;
} CRD;
CRD INIT_CRD_DEG( double LAT, double LNG)
{
  CRD crd= {
    .LAT = DEG2RAD(LAT),
    .LNG = DEG2RAD(LNG)
  };
    return crd;
}

CRD INIT_CRD_RAD( double LAT, double LNG)
{
    CRD crd ={
    .LAT = LAT,
    .LNG = LNG
    };
    return crd;
}

CRD GET_CRD_LNG_STR_END(double LNG,
                        CRD    START,
                        CRD    END)
{
    
    double lng1 = START.LNG;
    
    double lng2 = END.LNG;
    
    if (sin(lng1 - lng2) != 0) {
		double lat1 = START.LAT;
		double lat2 = END.LAT;
		double lng = LNG;
       double lat = atan((sin(lat1) * cos(lat2) * sin(lng - lng2) - sin(lat2) * cos(lat1) * sin(lng - lng1)) / (cos(lat1) * cos(lat2) * sin(lng1 - lng2)));
      return INIT_CRD_RAD(lat,lng);

    } else {
        return INIT_CRD_RAD(-0.0, 0.0);
    }
}

void SHOW_CRD_RAD(CRD crd){
  printf("[Latitude: %f , Longitude: %f ]\n",crd.LAT,crd.LNG);
}

void SHOW_CRD_DEG(CRD crd){
  printf("[Latitude: %f ,Longitude: %f ] \n",RAD2DEG(crd.LAT),RAD2DEG(crd.LNG));
}
typedef struct {
    CRD START;
    CRD END;
    double CRS;
    double DST;
} RTE;
/**********************SOME MORE FUNC**********************/


double GET_DST(CRD START, CRD END)
{
    double lat1 = START.LAT;
    double lng1 = START.LNG;
    double lat2 = END.LAT;
    double lng2 = END.LNG;
    return 2 * asin(sqrt(pow((sin((lat1 - lat2) / 2)), 2) + cos(lat1) * cos(lat2) * pow((sin((lng1 - lng2) / 2)), 2)));
}
double GET_CRS(CRD START, CRD END, double DST)
{
    double lat1 = START.LAT;
    double lng1 = START.LNG;
    double lat2 = END.LAT;
    double lng2 = END.LNG;
    double dst = DST;
    if (cosl(lat1) < esp) {
        if (lat1 > 0) {
            return pi;
        } else {
            return 2 * pi;
        }
    } else if (sin(lng2 - lng1) < 0) {
        return acos((sin(lat2) - sin(lat1) * cos(dst)) / (sin(dst) * cos(lat1)));
    } else {
        return 2 * pi - acos((sin(lat2) - sin(lat1) * cos(dst)) / (sin(dst) * cos(lat1)));
    }
}
RTE INIT_RTE_STR_END(CRD START, CRD END)
{
  RTE rte = {
    .START = START,
    .END = END,
    .DST = GET_DST(rte.START, rte.END),
    .CRS = GET_CRS(rte.START, rte.END, rte.DST)
  };
    return rte;
}
CRD CRD_ON_CRS_BY_DST(CRD START, double CRS, double DST)
{ // DST here is a distance along
    double lat1 = START.LAT; // crs not dist toendpoint
    double lng1 = START.LNG;
    double crs = CRS;
    double dst = DST;
    double LAT = asin(sin(lat1) * cos(dst) + cos(lat1) * sin(dst) * cos(crs));
    if (cos(LAT) == 0) {
        double LNG = lng1; // endpoints a pole

        return INIT_CRD_RAD(LAT,LNG);
    } else {
        double LNG = fmodf(lng1 - asin(sin(crs) * sin(dst) / cos(LAT)) + pi, 2 * pi) - pi;
        return INIT_CRD_RAD(LAT,LNG);
    }
}
RTE INIT_RTE_STR_CRS_DST(CRD START, double CRS, double DST ){
  RTE rte={
    .START =START,
    .CRS = CRS ,
    .DST =DST ,
    .END = CRD_ON_CRS_BY_DST(START, CRS, DST)
  };
return rte ;

}
/******************GETS LAT  OF WHERE  CRS PASS LNG ***********************************/
CRD LON_RTE_GET_LAT(double LNG, RTE rte)
{

        return GET_CRD_LNG_STR_END (LNG, rte.START,rte.END);

}
