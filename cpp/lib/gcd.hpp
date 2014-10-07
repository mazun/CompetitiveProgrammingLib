template<class T>
T gcd(T a, T b){
  if(a > b) swap(a, b);
  if(a == 0) return b;
  return gcd(b % a, a);
}
