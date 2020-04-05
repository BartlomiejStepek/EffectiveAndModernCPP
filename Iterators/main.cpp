/*** Bartlomiej Stepek ***/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <numeric>
#include "Range.h"
#include "MatrixIterator.h"

int main() {

    /* main to the class Range */

    auto r1 = Range<int>(1, 9, 2);
    for(auto x : r1)
        std::cout << x <<" ";  // 1 3 5 7
    std::cout << "\n";
    for(auto x : r1)
        std::cout << "--";
    std::cout << "\n";

    Range<double> r2(1, 9, 1.5);
    auto it = r2.begin();
    while(it != r2.end()){
        std::cout << *it++ << " ";
    }
    std::cout << "\n------------\n";

    for( auto x : Range<int>(1, 5))
        std::cout << x << ", ";  // 1, 2, 3, 4,
    std::cout << "\n------------\n";

    for( auto x : Range<int>(7) )
        std::cout << x << " ";  // 0 1 2 3 4 5 6
    std::cout << "\n------------\n";

    auto r3 = make_range(-4.0, 3.5, 1.2);
    for(auto x : r3)
        std::cout << x << " ";
    std::cout << "\n------------\n";

    for(auto x: make_range(6))
        std::cout << x << " ";
    std::cout << "\n------------\n";

    /* main to the class MatrixIterator */

    using DMatrix = Matrix<double, 3, 4>;
    DMatrix m({{1,  2,  3,  4},  // constructor from
               { 5,  6,  7,  8},  // initialization_list
               { 9, 10, 11, 12}});
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Matrix m\n";
    for(DMatrix::iterator it = m.begin(); it != m.end(); ++it)
        std::cout << std::setw(6) << *it << " ";

    std::cout << std::endl;
    auto sum = std::accumulate(m.begin(), m.end(), 0.0);
    std::cout << "sum of all elements = " << sum << std::endl;

    auto prod = std::inner_product(m.row_begin(1), m.row_end(1), m.row_begin(2), 0.0);
    std::cout << "inner product of 1st and 2nd row = " << prod << std::endl;

    for(DMatrix::col_iterator it = m.col_begin(3); it != m.col_end(3); ++it)
        std::cout << std::setw(6) << *it << " ";
    std::cout << std::endl;

    auto prod2 = std::inner_product(m.col_begin(1), m.col_end(1), m.col_begin(3), 0.0);
    std::cout << "inner product of 1st and 3rd column = " << prod2 << std::endl;

    Matrix< std::vector<int>, 2, 3 > mv = {
            { {1, 2}, {1,4,5},      {1, 2, 3, 4}},
            { {1},    {1, 4, 2, 3}, {5, 4}}
    };
    std::cout << "sizes of vectors in second row"  << std::endl;
    for(auto it = mv.row_begin(2); it != mv.row_end(2); ++it){
        std::cout << it->size() << std::endl;
    }

    return 0;

}
