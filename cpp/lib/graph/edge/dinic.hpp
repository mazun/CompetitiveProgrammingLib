// Thank for "Programming contest challenge book" !
#include <queue>
#include <climits>

template<class E>
class Dinic{
  typedef typename Graph<E>::G G;
  G &g;
  std::size_t n; // size of graph

  std::vector<int> level;
  std::vector<int> iter;

  // other utilities

  // search length of shortest path from s
  void bfs(int s){
    std::queue<int> que;
    level = std::vector<int>(n, -1);

    level[s] = 0;
    que.push(s);

    while(!que.empty()){
      int v = que.front(); que.pop();
      for(int i = 0; i < (int)g[v].size(); i++){
	E &e = g[v][i];
	if(e.cap > 0 && level[e.to] < 0){
	  level[e.to] = level[v] + 1;
	  que.push(e.to);
	}
      }
    }
  }

  // search path
  int dfs(int v, int t, int f){
    if(v == t) return f;
    for(int &i = iter[v]; i < (int)g[v].size(); i++){
      E &e = g[v][i];
      if(e.cap > 0 && level[v] < level[e.to]){
	int d = dfs(e.to, t, min(f, e.cap));
	if(d > 0){
	  e.cap -= d;
	  g[e.to][e.rev].cap += d;
	  return d;
	}
      }
    }
    return 0;
  }

public:
  Dinic(Graph<E> &graph) : g(graph.getRowGraph()){
    n = g.size();
  }

  // Max flow of the flow from s to t.
  int solve(int s, int t){
    int flow = 0;
    while(true){
      int f;
      bfs(s);
      if(level[t] < 0) return flow;
      iter  = std::vector<int>(n, 0);
      while((f = dfs(s, t, INT_MAX)) > 0){
	flow += f;
      }
    }
  }
};

template<class E>
int dinic(Graph<E> &g, int s, int d){
  return Dinic<E>(g).solve(s, d);
}
