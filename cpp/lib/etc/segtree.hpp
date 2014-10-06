template<typename Data, typename Func>
class SegmentTree{
  int n;
  std::vector<Data> data;
  Func f;

  Data query(int a, int b, int k, int l, int r) const{
    if(r <= a || b <= l) return 0;
    if(a <= l && r <= b) return data[k];
    else{
      const int v1 = query(a, b, k * 2 + 1, l, (l + r) / 2);
      const int v2 = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return max(v1, v2);
    }
  }

public:
  SegmentTree(int nn, Func ff, Data d) : f(ff){
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

  Data query(int a, int b) const{
    return query(a, b, 0, 0, n);
  }
};


template<typename Data, typename Func> SegmentTree<Data, Func>
segtree(int n, Data d, Func f){
  return SegmentTree<Data, Func>(n, f, d);
}
