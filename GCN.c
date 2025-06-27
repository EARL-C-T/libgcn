#include "GCN.h"
const double pi =M_PI;
double distance(CRD a, CRD b) {
  return 2*asin(sqrt(pow(sin((a.LAT-b.LAT)/2),2)+cos(a.LAT)*cos(b.LAT)*pow(sin((a.LNG-b.LNG)/2),2)));
} // distance between two coordinates DST
double bearing(CRD a, CRD b, double DST_ab) {
  if (cos(a.LAT) == 0) {
    if (a.LAT > 0) {
      return pi;
    } // start n pole
    else {
      return 2 * pi; // start s pole
    }
  } else if (sin(a.LNG - b.LNG) < 0) {
    return acos((sin(b.LAT) - sin(a.LAT) * cos(DST_ab)) /
                (sin(DST_ab) * cos(a.LAT)));
  } else {
    return 2 * pi - acos((sin(b.LAT) - sin(a.LAT) * cos(DST_ab) /
                                           (sin(DST_ab) * cos(a.LAT))));
  }
} // bearing between two coordinates BRG
CRD crd_brg_dst(CRD a, double BRG, double DST) {
  CRD b;
  double dlon;
  b.LAT = asin(sin(a.LAT) * cos(DST) + cos(a.LAT) * sin(DST) * cos(BRG));
  dlon = atan2(sin(BRG) * sin(DST) * cos(a.LAT),
               cos(DST) - sin(a.LAT) * sin(b.LAT));
  if (cos(a.LAT) == 0) {
    b.LNG = a.LNG;
  } else {
    b.LNG = fmod(a.LNG - dlon + pi, 2 * pi) - pi;
  }
  return b;
} // coordinates of point b when given point a ,bearing , distance to point b
int crd_brg_crd_brg(CRD a, double BRG_ac, CRD b, double BRG_bc, CRD *c) {
  double DST_ab = distance(a, b);
  double BRG_ba = bearing(b, a, DST_ab);
  double BRG_ab = bearing(a, b, DST_ab);
  double ANG_1 = fmod(BRG_ac - BRG_ba + 2 * pi, 2 * pi);
  double ANG_2 = fmod(BRG_bc - BRG_ab + 2 * pi, 2 * pi);
  if (sin(ANG_1) == 0 && sin(ANG_2) == 0) {
    return 6;
  } else if (sin(ANG_1) * sin(ANG_2) < 0) {
    return 7;
  } else {
    ANG_1 = fabs(ANG_1);
    ANG_2 = fabs(ANG_2);
    double ANG_3 =
        acos(-cos(ANG_1) * cos(ANG_2) + sin(ANG_1) * sin(ANG_2) * cos(DST_ab));
    double DST_ac = atan2(sin(ANG_1) * sin(ANG_2) * sin(DST_ab),
                          cos(ANG_2) + cos(ANG_1) * cos(ANG_3));
    CRD C = crd_brg_dst(a, BRG_ac, DST_ac);
    *c = C;
    return 0;
  }
} // coordinates c where brg crd a brg crd b meat supply a pointer to c and
  // return 0 upon success 7 if ambiguous 6 if infinit intersections

CRD crd_btween_a_b(CRD a, CRD b,
                   double f) { // f is fraction of the distance where 0 is a and
                               // 1 is b or dst_ac/dst_ab
  double DST_ab = distance(a, b);
  double A = sin((1 - f) * DST_ab) / sin(DST_ab);
  double B = sin(f * DST_ab) / sin(DST_ab);
  double x = A * cos(a.LAT) * cos(a.LNG) + B * cos(b.LAT) * cos(b.LNG);
  double y = A * cos(a.LAT) * sin(a.LNG) + B * cos(b.LAT) * sin(b.LNG);
  double z = A * sin(a.LAT) + B * sin(b.LAT);
  CRD c;
  c.LAT = atan2(z, sqrt(pow(x, 2) + pow(y, 2)));
  c.LNG = atan2(y, x);
  return c;
}
double xtd(double DST_ax, double BRG_ax, double BRG_ab) {
  return asin(sin(DST_ax) * sin(BRG_ax - BRG_ab));
} // the cross. track distance given dst a x brg a x and brg a c 
double atd(double DST_ax, double XTD) { return acos(cos(DST_ax) / cos(XTD)); }

