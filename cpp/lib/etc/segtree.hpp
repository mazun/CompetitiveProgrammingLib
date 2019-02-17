template<typename Data, typename Func>
class SegmentTree{
  int n;
  std::vector<Data> data;
  Func f;
  Data d;

  Data query(int a, int b, int k, int l, int r) const{
    if(r <= a || b <= l) return d;
    if(a <= l && r <= b) return data[k];
    else{
      const Data v1 = query(a, b, k * 2 + 1, l, (l + r) / 2);
      const Data v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return f(v1, v2);
    }
  }

public:
  SegmentTree(int nn, Func f, Data d) : f(f), d(d){
    n = 1;
    while(n < nn) n *= 2;
    data = std::vector<Data>(2 * n, d);
  }

  void update(int k, const Data &a){
    k += n - 1;
    data[k] = a;
    while(k > 0){
      k = (k - 1) / 2;
      data[k] = f(data[k * 2 + 1], data[k * 2 + 2]);
    }
  }

  // [a, b)
  Data query(int a, int b) const{
    return query(a, b, 0, 0, n);
  }
};

template<typename Data, typename Func> SegmentTree<Data, Func>
segtree(int numberOfElements, Data defaultValue, Func mergeFunc){
  return SegmentTree<Data, Func>(numberOfElements, mergeFunc, defaultValue);
}
