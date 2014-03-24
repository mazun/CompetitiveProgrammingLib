template<typename T>
class Partial2DSum{
private:
  vector<vector<T> > dp;

  Partial2DSum(const vector<vector<T> > &d){
    const int h = d.size();
    const int w = d[0].size();
    dp = vector<vector<T> >(h, vector<T>(w));

    REP(i,h) REP(j,w){
      T t = d[i][j];
      if(i != 0) t += dp[i - 1][j];
      if(j != 0) t += dp[i][j - 1];
      if(i != 0 && j != 0) t -= dp[i - 1][j - 1];
      dp[i][j] = t;
    }
  }

  template<int w, int h>
  Partial2DSum(const T (&d)[h][w]){
    dp = vector<vector<T> >(h, vector<T>(w));

    REP(i,h) REP(j,w){
      T t = d[i][j];
      if(i != 0) t += dp[i - 1][j];
      if(j != 0) t += dp[i][j - 1];
      if(i != 0 && j != 0) t -= dp[i - 1][j - 1];
      dp[i][j] = t;
    }
  }

public:
  static Partial2DSum build(const vector<vector<T> > &d){
    return Partial2DSum(d);
  }

  template<int w, int h>
  static Partial2DSum build(const T (&d)[h][w]){
    return Partial2DSum(d);
  }

  T query(int xs, int ys, int xe, int ye) const{
    int t = dp[ye][xe];
    if(ys != 0) t -= dp[ys - 1][xe];
    if(xs != 0) t -= dp[ye][xs - 1];
    if(ys != 0 && xs != 0) t += dp[ys - 1][xs - 1];
    return t;
  }
};

typedef Partial2DSum<int> IPartial2DSum;

