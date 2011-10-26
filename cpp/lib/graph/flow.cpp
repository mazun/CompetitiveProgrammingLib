typedef vector<vector<int> > G;

int flow(G &g, int s, int d){
  int n = g.size();
  int ans = 0;

  while(true){
    vector<int> prevs(n,-1);
    queue<int> q;
    bool ok = false;
    
    prevs[s]=n;
    q.push(s);
    while(!q.empty()){
      int now = q.front();
      q.pop();
      if(now == d){
        ok = true;
        break;
      }
      for(int i=0;i<n;i++){
        if(g[now][i]>0){
          if(prevs[i]==-1){
            prevs[i]=now;
            q.push(i);
          }
        }
      }
    }

    if(!ok) return ans;

    int f = INT_MAX;
    int pos = d;
    while(pos != s){
      int pos2 = prevs[pos];
      f = min(f,g[pos2][pos]);
      pos = pos2;
    }
    pos = d;
    while(pos != s){
      int pos2 = prevs[pos];
      g[pos2][pos]-=f;
      g[pos][pos2]+=f;
      pos = pos2;
    }
    ans += f;
  }
}
