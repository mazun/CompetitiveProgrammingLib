class Tree{
public:
  vector<vector<int> > next;
  vector<vector<int> > prev2;
  vector<int> depth;
  int root;

  Tree(const vector<vector<int> > &next,
       const vector<vector<int> > &prev2,
       const vector<int> depth,
       const int root) :
    next(next), prev2(prev2),
    depth(depth), root(root){
  }

  int lca(int a, int b) const{
    if(depth[a] > depth[b]) swap(a, b);
    int ddiff = depth[b] - depth[a];

    int dmax = prev2[0].size();
    REP(i,dmax){
      if(ddiff & (1 << i)) b = prev2[b][i];
    }

    if(a == b) return a;

    for(int i = dmax - 1; i >= 0; i--){
      if(prev2[a][i] != prev2[b][i]){
	a = prev2[a][i];
	b = prev2[b][i];
      }
    }

    return prev2[a][0];
  }
};

// g must be tree structure
Tree fromGraph(const vector<vector<int> > &g, int root = 0){
  const int n = g.size();
  vector<vector<int> > next(n);
  vector<vector<int> > prev2(n);
  vector<int> depth(n, -1);

  queue<pair<int, int> > q;

  q.push(make_pair(root, -1));
  depth[root] = 0;
  prev2[root].push_back(root);

  while(q.size()){
    const pair<int, int> d = q.front(); q.pop();
    const int now  = d.first;
    const int prev = d.second;

    REP(i,g[now].size()){
      int next = g[now][i];
      if(next != prev){
	q.push(make_pair(next, now));
	depth[next] = depth[now] + 1;
	prev2[next].push_back(now);
      }
    }
  }

  bool flag = true;
  while(flag){
    const int last = prev2[root].size() - 1;
    flag = false;

    REP(i,n){
      int data = prev2[prev2[i][last]][last];
      prev2[i].push_back(data);
      flag |= data != 0;
    }
  }

  return Tree(next, prev2, depth, root);
}
