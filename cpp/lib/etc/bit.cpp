class BIT{
  vector<int> bit;
public:
  BIT(int n) : bit(n + 1) {}
  void add(int idx, int val){
    idx++;
    while(idx < (int)bit.size()){
      bit[idx] += val;
      idx += idx & -idx;
    }
  }
  int sum(int i){
    int s = 0;
    i++;
    while(i > 0){
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }
};
