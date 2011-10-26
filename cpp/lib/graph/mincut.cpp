// Graph: matrix
typedef vector< vector<int> > Graph;

int minCut(Graph &g){
  int n = g.size();
  vector<int> V(n);
  for(int i=0; i<n; i++)
    V[i] = i;

  int cut = INT_MAX;
  for(int m=n; m>1; m--){
    vector<int> ws(m);
    int u,v,w;

    for(int k=0; k<m; k++){
      u = v;
      v = max_element(ws.begin(), ws.end()) - ws.begin();
      w = ws[v]; ws[v] = -1;
      for(int i=0; i<m; i++)
        if(ws[i] >= 0)
          ws[i] += g[V[v]][V[i]];
    }

    for(int i=0; i<m; i++){
      g[V[i]][V[u]] += g[V[i]][V[v]];
      g[V[u]][V[i]] += g[V[v]][V[i]];
    }

    V.erase(V.begin()+v);
    cut = min(cut, w);
  }
  return cut;
}
