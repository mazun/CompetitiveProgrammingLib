template<class T>
T gcd(T a, T b){
  if(a > b){ T tmp = b; b = a; a = b; }
  if(a == 0) return b;
  return gcd(a, b % a);
}
