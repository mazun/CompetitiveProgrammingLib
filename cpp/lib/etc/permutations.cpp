// [s, e]: must be sorted
// n is 0-based
// Iterator must be Random Iterator
template<class Iterator>
bool nth_permutation(Iterator s, Iterator e, int n){
  int len = e - s;
  const int flimit = 20;
  int fact[flimit]; fact[0] = 1;

  n++; // to 1-based

  if(len < flimit - 1 && fact[len] < n)
    return false;

  for(int i = 0; i < flimit - 1; i++){
    long long f = (long long)fact[i] * (i + 1);
    if(f <= INT_MAX){
      fact[i + 1] = f;
    }else{
      fact[i + 1] = fact[i];
    }
  }

  for(int i = 0; i < len; i++){
    int rest = len - i - 1;
    if(rest >= flimit || fact[rest] >= n)
      continue;

    int j = 0;
    while(n - fact[rest] > 0){ n -= fact[rest]; j++; }
    std::swap(*(s + i), *(s + i + j));
    std::sort(s + i + 1, e);
  }

  return true;
}
