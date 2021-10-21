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
    
    board(int n, vector<int> partial) : rows(partial){
        current_row =int(rows.size());
        for (int i=int(rows.size()); i<n; i++) {
            rows.push_back(-1);
        }
    }
    
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
                if (column_count.at(rows.at(i))>1) {
                    return false;
                }
            }
            // test to see if number of queens in current column is greater than 1
            
            // test for forward diagonals
            for (int j=i+1; j<rows.size(); j++) {
                if (rows.at(j)==(j-i)+rows.at(i)) {
                    if (rows.at(i)!=-1 && rows.at(j)!=-1) {
                        return false;
                    }
                }
            }
            // test for backwards diagonals
            if (i<rows.size()-1) {
                for (int j=i+1; j<rows.size(); j++) {
                    if (rows.at(j)>=0) {
                        if (rows.at(j)==rows.at(i)-(j-i)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    };
    optional<board> place_queens(){
        for (int i=0; i<rows.size(); i++) {
            board next = *this;
            next.place_next_queen_at_column(i);
            if (next.feasible()&& !next.filled()) {
                return next.place_queens();
            }
            if (next.filled() && next.feasible()) {
                return next;
            }
        }
        return {};
    };
};

int main(){
    board almost( 5, {0,2,4} );
    auto solution = almost.place_queens();
    cout << solution.has_value() <<endl;
    
    board empty(4);
    auto solution2 = empty.place_queens();
    cout << solution2.has_value() <<endl;
}
