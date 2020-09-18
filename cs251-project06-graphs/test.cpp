/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>

#include "minqueue.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("Test 02", "[Project07]")
{
  vector<int>  keys = { 123, 456, 789, 1234, 5678, 91011 };
  char  initialValue = '#';

  minqueue<int, char> queue(keys, initialValue);
           
  REQUIRE(!queue.empty());

  REQUIRE(queue.minfront() == 123);
  queue.minpop();
  REQUIRE(queue.minfront() == 456);
  queue.minpop();
  REQUIRE(queue.minfront() == 789);
  queue.minpop();
  REQUIRE(queue.minfront() == 1234);
  queue.minpop();
  REQUIRE(queue.minfront() == 5678);
  queue.minpop();
  REQUIRE(queue.minfront() == 91011);
  queue.minpop();

  REQUIRE(queue.empty());
}