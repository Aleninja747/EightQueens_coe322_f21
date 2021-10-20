//
//  main.cpp
//  Eight Queens
//
//  Created by Jorge Alejandro Ricaurte on 10/18/21.
//

#include <iostream>
#include <vector>
#include <exception>
using std::cin;
using std::cout;
using std::endl;
#include <iomanip>
using std::fixed;
using std::setprecision;
#include <chrono>
#include <optional>
using std::optional;

#ifndef NQUEENS
#define NQUEENS 8
#endif

using std::vector;

struct OutOfBounds : public std::exception
{
    const char * what () const throw ()
    {
        return "The index inserted is out of bounds.";
    }
};

class board {
private:
    vector<int> rows;
    int current_row = 0;
public:
    board(int n) : rows(vector<int>(n,-1)){}
    board(vector<int> row_input) : rows(row_input) {}
    
    int next_row_to_be_filled(){
        return current_row;
    };
    
    void place_next_queen_at_column(int n){
        if (n<0 || n>=rows.size()) {
            throw OutOfBounds();
        }
        else{
            rows.at(current_row) = n;
            current_row++;
        }
    };
    bool filled(){
        for (int i=0; i<rows.size(); i++) {
            if (rows.at(i)==-1) {
                return false;
            }
        }
        return true;
    };
    bool feasible(){
        if (current_row<2) {
            return true;
        }
        vector<int> column_count(rows.size(),0);
        for (int i=0; i<rows.size(); i++) {
            column_count.at(rows.at(i))++;
            if (column_count.at(rows.at(i))>1) {
                return false;
            }
            for (int j=i+1; i<rows.size(); j++) {
                if (rows.at(j)==(j-i)+rows.at(i)) {
                    return false;
                }
            }
        }
        for (int i=0; i<rows.size(); i++) {
            for (int j=i-1; j>=0; j--) {
                if (rows.at(j)==rows.at(i)-(i-j)) {
                    return false;
                }
            }
        }
        return true;
    };
};

#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"

TEST_CASE( "empty board" ) {
  const int n=10;
  board empty(n);
  REQUIRE( empty.next_row_to_be_filled()==0 );
}

TEST_CASE( "bounds test" ) {
  const int n=10;
  board empty(n);
  REQUIRE_THROWS( empty.place_next_queen_at_column(-1) );
  REQUIRE_THROWS( empty.place_next_queen_at_column(n) );
  REQUIRE_NOTHROW( empty.place_next_queen_at_column(0) );
  REQUIRE( empty.next_row_to_be_filled()==1 );
}

TEST_CASE( "feasibility test" ) {
  const int n=10;
  board empty(n);
  REQUIRE( empty.feasible() );

  board one = empty;
  one.place_next_queen_at_column(0);
  REQUIRE( one.next_row_to_be_filled()==1 );
  REQUIRE( one.feasible() );
}

TEST_CASE( "collision test" ) {
  const int n=10;
  board empty(n);
  board one = empty;
  one.place_next_queen_at_column(0);
  board collide = one;
  collide.place_next_queen_at_column(0);
  REQUIRE( not collide.feasible() );
}

TEST_CASE( "final test" ) {
  board five( {0,3,1,4,2} );
  REQUIRE( five.feasible() );
  REQUIRE( five.filled() );
}

TEST_CASE( "generate one and two" ) {
  const int n=10;
  board empty(n);

  // loop over all possibilities first queen
  auto firstcol = GENERATE_COPY( range(1,n) );
  board place_one = empty;
  REQUIRE_NOTHROW( place_one.place_next_queen_at_column(firstcol) );
  REQUIRE( place_one.feasible() );

  // loop over all possbilities second queen
  auto secondcol = GENERATE_COPY( range(1,n) );
  board place_two = place_one;
  REQUIRE_NOTHROW( place_two.place_next_queen_at_column(secondcol) );
  if (secondcol<firstcol-1 or secondcol>firstcol+1) {
    REQUIRE( place_two.feasible() );
  } else {
    REQUIRE( not place_two.feasible() );
  }
}
