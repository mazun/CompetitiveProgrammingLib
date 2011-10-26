#include<complex>

#define EPS 1e-10

using std::complex;
typedef complex<double> P; /* 点 */

static inline bool eq(const P &a, const P &b){
  return abs(a-b) < EPS;
}
/* 内積 */
static inline double inp(const P &a, const P &b){
  return (conj(a)*b).real();
}
/* 外積 */
static inline double outp(const P &a, const P &b){
  return (conj(a)*b).imag();
}

class Line{
public:
  P p; /* position */
  P d; /* direction */
  Line(){}
  Line(P pos, P dir){p=pos; d=dir/abs(dir);}
};

/* 点と方向から */
Line LineDirect(P pos, P dir){
  return Line(pos, dir);
}
/* 2点から */
Line LinePos(P p1, P p2){
  return Line(p1, p2-p1);
}

/* 2つの直線の交点 */
P crossPoint(const Line &l1, const Line &l2){
  double num = outp(l2.d, l2.p-l1.p);
  double denom = outp(l2.d, l1.d);
  return P(l1.p + l1.d * num/denom);
}

/* 点と直線の距離 */
double dist(const Line &l, const P &p){
  return std::abs(outp(l.d, p-l.p) / abs(l.d));
}
