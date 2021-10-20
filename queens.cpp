//
//  main.cpp
//  Eight Queens
//
//  Created by Jorge Alejandro Ricaurte on 10/18/21.
//

#include <iostream>
#include <vector>
#include <exception>
#include <optional>
using std::optional;
using std::cin;
using std::cout;
using std::endl;


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
        vector<int> column_count(rows.size(),0);
        for (int i=0; i<rows.size(); i++) {
            // Count amount of queens in each column.
            if (rows.at(i)!=-1){
                column_count.at(rows.at(i))++;
            }
            // test to see if number of queens in current column is greater than 1
            if (column_count.at(rows.at(i))>1) {
                return false;
            }
            // test for forward diagonals
            for (int j=i+1; j<rows.size(); j++) {
                if (rows.at(j)==(j-i)+rows.at(i)) {
                    return false;
                }
            }
            // test for backwards diagonals
            for (int j=i-1; j>=0; j--) {
                if (rows.at(j)==rows.at(i)-(i-j)) {
                    return false;
                }
            }
        }
        return true;
    };
    
};

int main(){
    board five( {1,0,3,4,2} );
    const int n=10;
    board empty(n);
    cout<<"Final Test: "<<five.feasible()<<endl;
    
    board one = empty;
    one.place_next_queen_at_column(0);
    board collide = one;
    collide.place_next_queen_at_column(0);
    cout<< collide.feasible()<<endl;
}
