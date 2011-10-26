template<int m>
class Prime{
  std::vector<bool> p;
  std::vector<int> ps;
public:
  Prime(){
    p = std::vector<bool>(m,true);
    assert(m>1);
    p[0]=p[1]=false;
    for(int i=4;i<m;i+=2)
      p[i]=false;
    ps.push_back(2);
    for(int i=3;i<m;i+=2){
      if(p[i]){
        ps.push_back(i);
        for(int j=i+i;j<m;j+=i)
          p[j]=false;
      }
    }
  }

  bool isPrime(int n){
    assert(m>n);
    return p[n];
  }

  int operator [] (int n){
    if(n<ps.size()) return ps[n];
    else return 0;
  }

  int size(){
    return ps.size();
  }
};
