class Matching{
  typedef vector<vector<int> > G;

  vector<bool> visited;

  const G &g; //g[i][j] = k <==> i is connected to k
  int n;      //number of node
  int m;      //number of left node

  bool augment(int left) {
    if (left < 0)
      return true;
    if (visited[left])
      return false;
    visited[left] = true;
    REP(i, g[left].size()) {
      int right = g[left][i];
      if (augment(matching[right])) {
        matching[right] = left;
        return true;
      }
    }
    return false;
  }

public:
  vector<int> matching;

  explicit Matching(const G &graph, int mm)
    : g(graph), m(mm){
    n = graph.size();
  }

  int solve() {
    int matches = 0;
    matching = vector<int>(n,-1);
    visited  = vector<bool>(n);
    REP(left, m) {
      visited.assign(n, false);
      if (augment(left))
        matches++;
    }
    return matches;
  }
};
