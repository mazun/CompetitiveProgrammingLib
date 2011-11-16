#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum{
  BINARY_OPERATOR = 0,
  UNARY_OPERATOR  = 1,
  VALUE           = 2
};

struct Tree{
  int type;

  // Identifier, Value or Operator
  string s;

  struct Tree *left;
  struct Tree *right;

  Tree(int t, const string &v, Tree *l = NULL, Tree *r = NULL) 
    : type(t), s(v), left(l), right(r) {}

  Tree(int t, char v, Tree *l = NULL, Tree *r = NULL) 
    : type(t), left(l), right(r) {
    stringstream ss; ss << v;
    s = ss.str();
  }

  ~Tree(){
    delete left; delete right;
  }

  void debug(){
    cout << "(";
    switch(type){
    case BINARY_OPERATOR:
      left->debug();
      cout << s;
      right->debug();
      break;
    case UNARY_OPERATOR:
      cout << s;
      left->debug();
      break;
    case VALUE:
      cout << s;
      break;
    }
    cout << ")";
  }
};

struct Parser{
  const string bop1;
  const string bop2;
  const string uop;

  Parser(const string &b1 = "+-",
	 const string &b2 = "*/",
	 const string &u = "-")
    : bop1(b1), bop2(b2), uop(u) {}

  typedef pair<Tree *, const char *> P;

  P parseExpr(const char *p) const{
    P r = parseTerm(p);
    while( *r.second != '\0' && bop1.find(*r.second) != string::npos ){
      char op   = *r.second;
      Tree *tmp = r.first;
      r = parseTerm(r.second + 1);
      r.first = new Tree(BINARY_OPERATOR, op, tmp, r.first);
    }
    return r;
  }

  P parseTerm(const char *p) const{
    P r = parseFact(p);
    while( *r.second != '\0' && bop2.find(*r.second) != string::npos ){
      char op   = *r.second;
      Tree *tmp = r.first;
      r = parseFact(r.second + 1);
      r.first = new Tree(BINARY_OPERATOR, op, tmp, r.first);
    }
    return r;
  }

  P parseFact(const char *p) const{
    if(uop.find(*p) != string::npos){
      P r = parseFact(p + 1);
      return P(new Tree(UNARY_OPERATOR, *p, r.first), r.second);
    }else if(*p == '('){
      P r = parseExpr(p + 1);
      if(*r.second != ')') throw make_pair("fact1", p);
      return P(r.first, r.second + 1);
    }else{
      // identifier or value
      stringstream ss;
      while(*p != '\0' &&
	    bop1.find(*p) == string::npos &&
	    bop2.find(*p) == string::npos &&
	    uop.find(*p)  == string::npos &&
	    *p != '(' && *p != ')'){
	ss << *p++;
      }
      if(ss.str().size() == 0) throw make_pair("fact2", p);
      return P(new Tree(VALUE, ss.str()), p);
    }
  }

  Tree *parse(const string &str) const{
    return parseExpr(str.c_str()).first;
  }
};

// Sample Evaluater
template<typename T>
struct Evaluater{
  typedef T result;

  Evaluater(){}

  // Binary Operator
  T operator()(const T &lhs, char op, const T &rhs) const{
    switch(op){
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    default:
      throw "Unknown Binary Operator";
    }
  }

  // Unary Operator
  T operator()(char op, const T &rhs) const{
    return - rhs;
  }

  // Value
  T operator()(const string &str) const{
    stringstream ss;
    T val;
    ss << str;
    ss >> val;
    return val;
  }
};

template<typename E>
typename E::result eval(Tree *p, const E &e){
  switch(p->type){
  case BINARY_OPERATOR:
    return e(eval(p->left, e), p->s[0], eval(p->right, e));
  case UNARY_OPERATOR:
    return e(p->s[0], eval(p->left, e));
  case VALUE:
    return e(p->s);
  default:
    throw "Evaluater error";
  }
}

