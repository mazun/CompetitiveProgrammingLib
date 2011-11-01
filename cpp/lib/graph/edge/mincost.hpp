// Thank for "Programming contest challenge book" !
#include <queue>
#include <climits>

template<class E>
int minCostFlow(Graph<E> &graph, int s, int t, int f, bool negative = false){
  typedef pair<int, int> P;
  typename Graph<E>::G &g = graph.getRowGraph();
  int n = g.size();
  int res = 0;
  vector<int> h(n, 0);
  vector<int> prevv(n);
  vector<int> preve(n);
  const int inf = 10000000;

  if(negative){
    vector<int> dist(n, inf);
    dist[s] = 0;
    
    bool update = true;
    
    while(update){
      update = false;
      for(int v = 0; v < n; v++){
	if(dist[v] == inf) continue;
	for(int i = 0; i < (int)g[v].size(); i++){
	  E &e = g[v][i];
	  if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
	    dist[e.to]  = dist[v] + e.cost;
	    prevv[e.to] = v;
	    preve[e.to] = i;
	    update      = true;
	  }
	}
      }
    }

    for(int i = 0; i < n; i++)
      h[i] = dist[i];
  }

  while(f > 0){
    priority_queue<P, vector<P>, greater<P> > que;
    vector<int> dist(n, inf);
    dist[s] = 0;
    que.push(P(0, s));

    while(!que.empty()){
      P p   = que.top(); que.pop();
      int v = p.second;
      if(dist[v] < p.first) continue;
      for(int i = 0; i < (int)g[v].size(); i++){
	E &e = g[v][i];

	if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
	  dist[e.to]  = dist[v] + e.cost + h[v] - h[e.to];
	  prevv[e.to] = v;
	  preve[e.to] = i;
	  que.push(P(dist[e.to], e.to));
	}
      }
    }
    if(dist[t] == inf){
      return -1;
    }

    for(int v = 0; v < n; v++) h[v] += dist[v];

    int d = f;
    for(int v = t; v != s; v = prevv[v]){
      d = min(d, g[prevv[v]][preve[v]].cap);
    }

    f   -= d;
    res += d * h[t];

    for(int v = t; v != s; v = prevv[v]){
      E &e = g[prevv[v]][preve[v]];
      e.cap -= d;
      g[v][e.rev].cap += d;
    }
  }
  return res;
}

template<class E>
int minCostFlowDebug(Graph<E> &graph, int s, int t, int f){
  typename Graph<E>::G &g = graph.getRowGraph();
  int n = g.size();
  int res = 0;
  vector<int> prevv(n);
  vector<int> preve(n);
  const int inf = 200000000;
  
  while(f > 0){
    vector<int> dist(n, inf);
    dist[s] = 0;
    
    bool update = true;
    
    while(update){
      update = false;
      for(int v = 0; v < n; v++){
	if(dist[v] == inf) continue;
	for(int i = 0; i < (int)g[v].size(); i++){
	  E &e = g[v][i];
	  if(e.cap > 0 && dist[e.to] > dist[v] + e.cost){
	    dist[e.to]  = dist[v] + e.cost;
	    prevv[e.to] = v;
	    preve[e.to] = i;
	    update      = true;
	  }
	}
      }
    }
    
    if(dist[t] == inf){
      return -1;
    }
    
    int d = f;
    for(int v = t; v != s; v = prevv[v]){
      d = min(d, g[prevv[v]][preve[v]].cap);
    }
    
    f   -= d;
    res += d * dist[t];
    
    for(int v = t; v != s; v = prevv[v]){
      E &e = g[prevv[v]][preve[v]];
      e.cap           -= d;
      g[v][e.rev].cap += d;
    }
  }
  return res;
}

