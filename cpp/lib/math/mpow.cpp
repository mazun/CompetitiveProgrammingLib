ll mpow(ll b, ll e){
  ll ret = 1;
  while(e){
    if(e & 1) ret = (ret * b) % mod;
    b = (b * b) % mod;
    e /= 2;
  }
  return ret;
}
