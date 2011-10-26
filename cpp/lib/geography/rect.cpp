#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>

using namespace std;

class Point{
public:
  long double x;
  long double y;

  Point(long double x,long double y){
    this->x=x;this->y=y;
  }
  Point(){
  }
};

class Line{
public:
  //ax+by+c=0
  long double a;
  long double b;
  long double c;

  Line(Point p1,Point p2){
    this->a=p1.y-p2.y;
    this->b=p2.x-p1.x;
    this->c=p1.x*p2.y-p1.y*p2.x;
  }
};

#define DOUBLE(a) ((a)*(a))

long double dist(Line l,Point p){
  return abs(l.a*p.x+l.b*p.y+l.c)/sqrt(DOUBLE(l.a)+DOUBLE(l.b));
}
long double dist(Point p1,Point p2){
  return sqrt(DOUBLE(p1.x-p2.x)+DOUBLE(p1.y-p2.y));
}

class Rect{
public:
  Point a;
  Point b;
  Point c;
  Point d;

  /*
   *  a------b
   *  |      |
   *  |      |
   *  c------d
   */

  Rect(Point a,Point b,Point c,Point d){
    this->a=a;this->b=b;this->c=c;this->d=d;
    
    if(
       a.x > b.x ||
       a.y < c.y ||
       b.y < d.y ||
       c.x > d.x
       )
      throw "exception\n";
  }

  long double size(){
    Line ad=Line(a,d);
    long double teihen=dist(a,d);
    long double takasa1,takasa2;
    takasa1=dist(ad,b);
    takasa2=dist(ad,c);
    return teihen*(takasa1+takasa2)/2.0;
  }
};

Point crossPoint(const Line &l1,const Line &l2){
  long double a1,a2,b1,b2,c1,c2;
  a1=l1.a;b1=l1.b;c1=-l1.c;
  a2=l2.a;b2=l2.b;c2=-l2.c;
  long double x,y;
  long double delta=a1*b2-b1*a2;
  x=( b2*c1-b1*c2)/delta;
  y=(-a2*c1+a1*c2)/delta;
  return Point(x,y);
}
