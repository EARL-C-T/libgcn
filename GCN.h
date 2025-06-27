#ifndef GCN_H
#define GCN_H
#include <math.h>
typedef struct coordinates {
  double LAT; // lattitude
  double LNG; // longitude
} CRD;        // coordinates
double distance(CRD a, CRD b); // distance between two coordinates DST_ab
double bearing(CRD a, CRD b, double DST_ab);// bearing between two coordinates BRG
CRD crd_brg_dst(CRD a, double BRG, double DST); // returns coordinates of point b when given point a ,bearing , distance to point b
int crd_brg_crd_brg(CRD a, double BRG_ac, CRD b, double BRG_bc, CRD *c); // coordinates c where brg crd a brg crd b meat supply a pointer to c and
  // return 0 upon success 7 if ambiguous 6 if infinit intersections

CRD crd_btween_a_b(CRD a, CRD b,
                   double f);//f is the fractoin of distance traveled where a =0 and b=1 
double xtd(double DST_ax, double BRG_ax, double BRG_ab);// the cross. track distance off course from a to b when at x I'm
double atd(double DST_ax, double XTD);

#endif 
