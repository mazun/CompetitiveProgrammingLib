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
