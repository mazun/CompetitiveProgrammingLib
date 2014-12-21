template<typename Data, typename Func>
class SegmentTree{
  int n;
  std::vector<Data> data;
  Func f;
  Data d;

  void update(int a, int b, int k, int l, int r, const Data &v){
    if(r <= a || b <= l) return;
    if(a <= l && r <= b) data[k] = f(data[k], v);
    else{
      update(a, b, k * 2 + 1, l, (l + r) / 2, v);
      update(a, b, k * 2 + 2, (l + r) / 2, r, v);
    }
  }

public:
  SegmentTree(int nn, Func f, Data d) : f(f), d(d){
    n = 1;
    while(n < nn) n *= 2;
    data = std::vector<Data>(2 * n, d);
  }

  void update(int a, int b, const Data &v){
    update(a, b, 0, 0, n, v);
  }

  Data query(int k){
    k += n - 1;
    Data ret = data[k];
    while(k > 0){
      k = (k - 1) / 2;
      ret = f(ret, data[k]);
    }
    return ret;
  }
};

template<typename Data, typename Func> SegmentTree<Data, Func>
segtree(int numberOfElements, Data defaultValue, Func mergeFunc){
  return SegmentTree<Data, Func>(numberOfElements, mergeFunc, defaultValue);
}
