template<typename Cost>
Cost prim(const vector<vector<pair<int, Cost> > > &g){
  typedef pair<Cost, pair<int, int> > data;
  priority_queue<data, vector<data>, greater<data> > pq;

  REP(i,g.size())
    REP(j,g[i].size())
      if(g[i][j].first < i)
	pq.push(data(g[i][j].second, make_pair(i, g[i][j].first)));

  UnionFind uf(g.size());

  Cost ret = 0;
  while(pq.size()){
    const data d = pq.top(); pq.pop();
    const Cost cost = d.first;
    const int a = d.second.first;
    const int b = d.second.second;
    if(uf[a] != uf[b]){
      uf.unite(a, b);
      ret += cost;
    }
  }

  return ret;
}
