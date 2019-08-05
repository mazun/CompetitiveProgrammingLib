// TEST ALL LIBRARIES
#include <iostream>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

template<class T>
bool vecEqual(T a, T b){
  if(a.size() != b.size()) return false;
  for(int i = 0; i < (int)a.size(); i++)
    if(a[i] != b[i]) return false;
  return true;
}

// Test permutations.cpp
#include <algorithm>
#include "etc/permutations.cpp"

BOOST_AUTO_TEST_CASE( permutations_test ){
  std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
  std::vector<int> correct = v;

  for(int i = 1; ; i++){
    std::vector<int> tmp = v;

    bool b1 = std::next_permutation(correct.begin(), correct.end());
    bool b2 = nth_permutation(tmp.begin(), tmp.end(), i);

    BOOST_CHECK_EQUAL(b1, b2);
    if(b1){
      break;
    }else{
      BOOST_CHECK( vecEqual(correct, tmp) );
    }
  }
}

// Test primes
#include <cassert>
#include "prime.h"
BOOST_AUTO_TEST_CASE( primes ){
  Prime<100> p;

  BOOST_CHECK( p.isPrime(3) );
  BOOST_CHECK( p.isPrime(5) );
  BOOST_CHECK( p.isPrime(13) );

  BOOST_CHECK( !p.isPrime(4) );
  BOOST_CHECK( !p.isPrime(15) );
  BOOST_CHECK( !p.isPrime(65) );

  BOOST_CHECK_EQUAL( p[0], 2 );
  BOOST_CHECK_EQUAL( p[1], 3 );
  BOOST_CHECK_EQUAL( p[2], 5 );
  BOOST_CHECK_EQUAL( p[3], 7 );
  BOOST_CHECK_EQUAL( p[4], 11 );
  BOOST_CHECK_EQUAL( p[5], 13 );
  BOOST_CHECK_EQUAL( p[6], 17 );
}

#include "string/ssearch.cpp"
#include <cstring>

bool ok_str(const char *p, const char *a){
  const int  r1 = kmpsearch(p, a);
  const int  r2 = rksearch(p, a);
  const char *s = strstr(a, p);
  const int  r3 = s ? static_cast<int>(s - a) : -1;

  return r1 == r2 && r2 == r3;
}

BOOST_AUTO_TEST_CASE( ssearch ){
  BOOST_CHECK( ok_str("ab"     , "cdabew") );
  BOOST_CHECK( ok_str("myon"   , "I love myonmyon") );
  BOOST_CHECK( ok_str("world"  , "Hello, world.") );
  BOOST_CHECK( ok_str("star"   , "lucky star") );
  BOOST_CHECK( ok_str("nothing", "everything") );
}

#include <cstdlib>
#include "etc/sum.hpp"

int g[10][10];
int gg[10][10][10][10];

bool checksum(void){
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      g[i][j] = rand() % 100;
    }
  }

  sum(g, gg, 10, 10);

  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      for(int k = 0; k < 10; k++){
	for(int l = 0; l < 10; l++){
	  int tmp = 0;

	  for(int y = i; y <= k; y++){
	    for(int x = j; x <= l; x++){
	      tmp += g[y][x];
	    }
	  }

	  if(tmp != gg[i][j][k][l]){
	    std::cout << gg[i][j][k][l] << "!=" << tmp << std::endl;
	    std::cout << "(" << i << "," << j << "," << k << "," << l << ")" << std::endl;
	    return false;
	  }
	}
      }
    }
  }
  return true;
}

BOOST_AUTO_TEST_CASE( sum_test ){
  for(int i = 0; i < 10; i++){
    BOOST_CHECK(checksum());
  }
}

#include "etc/segtree.hpp"

BOOST_AUTO_TEST_CASE( segtree1 ){
  const int n = 10;
  auto s1 = segtree(n, 0, [](int a, int b){ return a + b; });
  BOOST_CHECK_EQUAL(s1.query(0, n), 0);
  s1.update(5, 1);
  BOOST_CHECK_EQUAL(s1.query(0, n), 1);
  BOOST_CHECK_EQUAL(s1.query(5, 6), 1);
  BOOST_CHECK_EQUAL(s1.query(0, 5), 0);
  BOOST_CHECK_EQUAL(s1.query(6, n), 0);
}
