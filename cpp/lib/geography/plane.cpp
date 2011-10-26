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

//線分
struct S{
  P p1;
  P p2;
  S(P p,P q) : p1(p), p2(q) {}
};

/* p0, p1, p2が
 * 反時計回り:  1
 * 時計回り  : -1
 *
 * ３点が直線上にある場合
 * p0がp2とp1の間にある: -1
 * p2がp0とp1の間にある:  0
 * p1がp0とp2の間にある:  1
 */
int ccw(P p0, P p1, P p2){
  P d1 = p1-p0;
  P d2 = p2-p0;
  double dx1 = d1.real(), dx2 = d2.real();
  double dy1 = d1.imag(), dy2 = d2.imag();

  if(dx1*dy2 > dy1*dx2) return  1;//反時計回り
  if(dx1*dy2 < dy1*dx2) return -1;//時計回り
  if((dx1*dx2 < 0) || (dy1*dy2 < 0)) return -1;
  if((dx1*dx1+dy1*dy1) < (dx2*dx2+dy2*dy2)) return 1;
  return 0;
}

bool intersect(const S &s1, const S &s2){
  return ((ccw(s1.p1, s1.p2, s2.p1)
	   *ccw(s1.p1, s1.p2, s2.p2)) <= 0)
    &&((ccw(s2.p1, s2.p2, s1.p1)
	*ccw(s2.p1, s2.p2, s1.p2)) <= 0);
}

/* N角形pの中にtがあるかどうか */
bool inside(P t, P *p, int N){
  int count = 0, j = 0;
  S lt(t, P(DBL_MAX,t.imag()));  

  P pj = p[N-1];
  for(int i=1; i<=N; i++){
    S lp(p[i-1],p[i-1]);
    if(ccw(lt.p1, lt.p2, p[i-1]) != 0){
      if(i == j+1){
	lp.p2 = pj;
	if(intersect(lp,lt)) count++;
      }else if(ccw(lt.p1, lt.p2, p[i-1])*ccw(lt.p1, lt.p2, pj) < 0)
	count++;
      j = i;
      if(j == N) pj = p[0];
      else pj = p[j-1];
    }
  }
  return count & 1 == 1;
}

struct cmpTheta{
  const P base;
  cmpTheta(P p) : base(p) {}

  bool operator () (const P &p1, const P &p2) const{
    P ang1 = (p1 - base) / abs(p1 - base);
    P ang2 = (p2 - base) / abs(p2 - base);
    return (ang1 / ang2).imag() < 0;
  }
};

#define PP(p, i, n) (p[((i)==-1 ? (n)-1 : (i))])

/*
 * 凸閉包を求める
 * p[]の先頭のM要素が答え
 */
int grahamscan(P *p, int N){
  int min, M, i;
  for(min=0, i=1; i<=N; i++)
    if(p[i].imag() < p[min].imag())
      min=i;

  for(i=1; i<=N; i++)
    if(p[i].imag() == p[min].imag())
      if(p[i].real() > p[min].real())
	min = i;

  swap(p[min], p[0]);

  sort(p+1, p+N, cmpTheta(p[0]));

  for(M=2, i=3; i<=N; i++){
    while(ccw(PP(p,M,N),PP(p,M-1,N),PP(p,i,N)) >= 0) M--;
    M++; swap(p[i], p[M]);
  }

  return M;
}


/*
 * 2Dtree
 */
class Rect{
public:
  P lu;
  P rd;
  Rect(P a, P b){
    double lux,luy,rdx,rdy;
    lux = std::min(a.real(),b.real());
    luy = std::min(a.imag(),b.imag());
    rdx = std::max(a.real(),b.real());
    rdy = std::max(a.imag(),b.imag());
    lu = P(lux,luy);
    rd = P(rdx,rdy);
  }
};

bool insiderect(P p, const Rect &range){
  return
    p.real() >= range.lu.real() &&
    p.real() <= range.rd.real() &&
    p.imag() >= range.lu.imag() &&
    p.imag() <= range.rd.imag();
}

class Tree2D{
  struct node{
    P p;
    node *l;
    node *r;
  };

  node *z, *head;
  P dammy;

  int searchr(node *t, Rect range, int d){
    int t1, t2, tx1, tx2, ty1, ty2, count=0;
    if(t==z) return 0;
    tx1 = range.lu.real() < t->p.real(); tx2 = t->p.real() <= range.rd.real();
    ty1 = range.lu.imag() < t->p.imag(); ty2 = t->p.imag() <= range.rd.imag();
    t1 = d ? tx1 : ty1; t2 = d ? tx2 : ty2;
    if(t1) count += searchr(t->l, range, !d);
    if(insiderect(t->p, range)) count++;
    if(t2) count += searchr(t->r, range, !d);
    return count;
  }
  void deleteSub(node *n){
    if(n->l != z) deleteSub(n->l);
    if(n->r != z) deleteSub(n->r);
    delete n;
  }
public:
  Tree2D(){
    head = new node;
    head->p = P(-1e10,-1e10);
    head->l = head->r = z;
  }
  ~Tree2D(){
    deleteSub(head);
  }
  void insert(P p){
    node *f, *t;
    int d, td;
    for(d=0, t=head; t!=z; d!=d){
      td = d ? (p.real() < t->p.real()) : (p.imag() < t->p.imag());
      f = t; t = td ? t->l : t->r;
    }
    t = new node; t->p = p; t->l = z; t->r = z;
    if(td) f->l = t; else f->r = t;
  }
  /*
   * rangeに含まれる点の数を数える
   */
  int search(Rect range){
    if(!head) return 0;
    return searchr(head->r, range, 1);
  }
};
