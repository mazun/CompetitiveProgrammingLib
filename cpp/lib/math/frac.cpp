using std::swap;
using std::ostream;
using std::abs;

template<typename T>
T gcd(T a, T b){
  if(a>b) swap(a,b);
  if(a==0) return b;
  return gcd(a,b%a);
}

template<typename T>
class frac{
public:
  T n;
  T d;
  frac(T i){n=i;d=1;}
  frac(T i,T j){
    assert(j!=0);
    T g=gcd(abs(i),abs(j));
    n=i/g;d=j/g;
    if(n==0) d=1;
    if(d<0){
      d*=-1;
      n*=-1;
    }
  }
  frac(){n=0;d=1;};
  frac operator + (const frac &a) const{
    return frac(n*a.d+d*a.n, d*a.d);
  }
  frac operator - (const frac &a) const{
    return frac(n*a.d-d*a.n, d*a.d);
  }
  frac operator - () const{
    return frac(-n,d);
  }
  frac operator * (const frac &a) const{
    return frac(n*a.n, d*a.d);
  }
  frac operator / (const frac &a) const{
    return frac(n*a.d, d*a.n);
  }
  bool operator == (const frac &a) const{
    return n==a.n && d==a.d;
  }
  bool operator < (const frac &a) const{
    return n*a.d-d*a.n < (T)0;
  }
  bool operator > (const frac &a) const{
    return n*a.d-d*a.n > (T)0;
  }
};
template<typename T>
ostream &operator << (ostream &o, const frac<T> &a){
  o << a.n << "/" << a.d;
  return o;
}
