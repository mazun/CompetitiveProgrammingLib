template<typename C, typename C::value_type low, typename C::value_type high, int bit = 32>
class PalindromeTree{
  const static int m = high - low + 1;
  const static int b = (m * bit + 31) / 32;

  typedef typename C::value_type T;

  struct node{
    int next_[b];
    int len;
    int sufflink;

    int next(int i){
      const int bs = i * bit;
      const int be = i * bit + bit;

      const int ys = bs / 32;
      const int sc = min(bit, 32 - (bs % 32));
      const int ye = be / 32;
      const int ec = bit - sc;

      int ret = 0;
      ret |= (next_[ys] >> (bs % 32)) & ((1ll << sc) - 1);
      if(ec != 0) ret |= (next_[ye] & ((1ll << ec) - 1)) << sc;

      return ret;
    }

    void next(int i, int v){
      const int bs = i * bit;
      const int be = i * bit + bit;

      const int ys = bs / 32;
      const int sc = min(bit, 32 - (bs % 32));
      const int ye = be / 32;
      const int ec = bit - sc;

      next_[ys] &= ~(((1ll << sc) - 1) << (bs % 32));
      next_[ys] |= (v & ((1ll << sc) - 1)) << (bs % 32);

      if(ec != 0) next_[ye] &= ~((1ll << ec) - 1);
      if(ec != 0) next_[ye] |= (v >> sc) & ((1ll << ec) - 1);
    }
  };

  const C s;
  int len;
  int num;

  void initTree(){
    num = 2; suff = 2;
    tree[1].len = -1; tree[1].sufflink = 1;
    tree[2].len = 0; tree[2].sufflink = 1;
  }

public:
  node *tree;
  int suff;

  bool addLetter(int pos){
    int cur = suff;
    int curLen = 0;
    const int let = s[pos] - low;

    while(true){
      curLen = tree[cur].len;
      if(pos - 1 - curLen >= 0 && s[pos - 1 - curLen] == s[pos]) break;
      cur = tree[cur].sufflink;
    }

    if(tree[cur].next(let)){
      suff = tree[cur].next(let);
      return false;
    }

    num++;

    suff = num;
    tree[num].len = tree[cur].len + 2;
    tree[cur].next(let, num);

    if(tree[num].len == 1){
      tree[num].sufflink = 2;
      return true;
    }

    while(true){
      cur = tree[cur].sufflink;
      curLen = tree[cur].len;
      if(pos - 1 - curLen >= 0 && s[pos - 1 - curLen] == s[pos]){
	tree[num].sufflink = tree[cur].next(let);
	break;
      }
    }

    return true;
  }

  PalindromeTree(const C &s)
    : s(s), len(s.size()), tree(new node[s.size() + 3]){
    initTree();
  }

  void build(){
    for(int i = 0; i < len; i++){
      addLetter(i);
    }
  }

  static long long countSamePalindrome(C &&s, C &&t, const C &sp){
    long long ans = 0;
    const int ss = s.size();
    const C sum = s + sp + t;
    s = t = "";
    PalindromeTree tree(sum);

    vector<long long> scnt(sum.size() + 3);
    vector<long long> tcnt(sum.size() + 3);

    for(int i = 0; i < (int)sum.size(); i++){
      tree.addLetter(i);

      int pos = tree.suff;
      const node &nd = tree.tree[pos];
      if(i - nd.len + 1 < ss){
	scnt[pos]++;
      }else if(i - nd.len + 1 >= (int)(ss + sp.size())){
	tcnt[pos]++;
      }
    }

    for(int i = 0; i < 2; i++){
      vector<long long> &v = i == 0 ? scnt : tcnt;

      for(int j = (int)v.size() - 1; j >= 3; j--){
	const int suff = tree.tree[j].sufflink;
	if(suff >= 3){
	  v[suff] += v[j];
	}
      }
    }

    for(int i = 3; i < (int)scnt.size(); i++){
      ans += scnt[i] * tcnt[i];
    }

    return ans;
  }
};
