template<class T>
class IdGenerator{
  std::map<T,int> _m;

public:
  IdGenerator(){}

  int getId(const T &v){
    if(_m.find(v) == _m.end()){
      int next = _m.size();
      return _m[v] = next;
    }
    return _m[v];
  }

  int size() const{
    return _m.size();
  }
};
