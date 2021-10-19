//
//  main.cpp
//  Eight Queens
//
//  Created by Jorge Alejandro Ricaurte on 10/18/21.
//

#include <iostream>
#include <vector>
#include <exception>

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
    int next_row_to_be_filled(){
        return current_row;
    };
    int place_next_queen_at_column(int n){
        if (n<0 || n>=rows.size()) {
            throw OutOfBounds();
        }
        else{
            rows.at(current_row) = n;
            current_row++;
        }
        return 0;
    };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
