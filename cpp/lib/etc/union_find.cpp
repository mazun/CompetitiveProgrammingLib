class UnionFind{
private:
  mutable vector<int> id;

  int getId(int i) const{
    if(i == id[i]) return i;
    return id[i] = getId(id[i]);
  }
public:
  UnionFind(int size = 0){ init(size); }
  ~UnionFind(){}
  void init(int size){
    id = vector<int>(size);
    for(int i = 0; i < size; i++)
      id[i] = i;
  }
  void unite(int i, int j){
    int next = min( getId(i), getId(j) );
    id[getId(i)] = id[getId(j)] = next;
  }
  int operator [](int i) const{ return getId(i); }
  int count() const{
    set<int> s;
    for(int i = 0; i < (int)id.size(); i++)
      s.insert(getId(i));
    return s.size();
  }
};
