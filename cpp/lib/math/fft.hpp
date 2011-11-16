// sizeof v must be 2 ^ n
template<class T>
void fft_core(vector<complex<T> > &v, bool rev = false){
  const int n = v.size();

  for(int i = 0; i < n; i++){
    int k = 0;
    int b = (n >> 1);
    int a = 1;

    while(b >= a){
      if(b & i) k |= a;
      if(a & i) k |= b;
      b >>= 1;
      a <<= 1;
    }

    if(i < k) swap(v[i], v[k]);
  }

  int m = 2;

  while(m <= n){
    double arg = -2.0 * M_PI / m;
    complex<T> w(cos(arg), sin(arg));
    if(rev) w = 1.0 / w;

    for(int i = 0; i < n; i += m){
      complex<T> ww(1.0);

      for(int j = 0; j < m / 2; j++){
	int a = i + j;
	int b = i + j + m / 2;
	complex<T> t = ww * v[b];

	v[b] = v[a] - t;
	v[a] = v[a] + t;

	ww *= w;
      }
    }
    m *= 2;
  }

  if(rev){
    double s = (double)n;
    for(int i = 0; i < n; i++)
      v[i] /= s;
  }
}

template<class T> inline void  fft(vector<T> &v){ fft_core(v); }
template<class T> inline void ifft(vector<T> &v){ fft_core(v, true); }
