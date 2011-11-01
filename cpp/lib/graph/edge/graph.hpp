#include <vector>

struct Edge{
  int cap; // capacity
  int to;
  int rev; // reverse edge id

  Edge(){}
  Edge(int c, int t, int r) :
    cap(c), to(t), rev(r){}
};

struct CostEdge : public Edge{
  int cost;
  CostEdge() : Edge() {}
  CostEdge(int c, int t, int cs, int r) :
    Edge(c, t, r), cost(cs){}
};
  
template<class E> // Edge type
class Graph{
public:
  typedef std::vector<std::vector<E> > G;

private:
  G g;

public:
  Graph(int n) : g(G(n)) {}

  void addEdge(int from, int to, int cap){
    g[from].push_back(E(cap, to, g[to].size()));
    g[to].push_back(E(0, from, g[from].size() - 1));
  }

  void addEdge(int from, int to, int cap, int cost){
    g[from].push_back(E(cap, to, cost, g[to].size()));
    g[to].push_back(E(0, from, -cost, g[from].size() - 1));
  }

  G &getRowGraph(){
    return g;
  }
};
