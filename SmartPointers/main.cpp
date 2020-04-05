/*** Bartlomiej Stepek ***/
#include <iostream>
#include <algorithm>
#include <memory>
#include "Matrix.h"
#include "String.h"
#include "PairOfMatrices.h"

int main()
{
    /* main to classes Matrix and PairOfMatrices */
    
    Matrix m1;
    Matrix m2(3,4);
    Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
    std::cout << m2(1,1) << std::endl;  // 0
    std::cout << m3(2,2) << std::endl;  // 23
    std::cout << m3;
    m2(1,1) = 3;

    std::cout << "Copy semantics \n";
    Matrix m4 = m2;
    m4 = m3;

    std::cout << "Move semantics \n";
    Matrix m7 = std::move(m2);
    m4 = -m3;

    std::cout << "Copy elision \n";
    Matrix m6 = -m4;
    Matrix * pm = new Matrix(-m4);
    std::cout << m6(2,1) << std::endl; // 32

    Matrix m10({{1,2},{4,4}}),  m20(4,5);
    PairOfMatrices p1 {m10, std::move(m20)};
    //PairOfMatrices p20 = p10;   // ERROR!
    PairOfMatrices p3 = std::move(p1);
    Matrix a = p3.left, b=p3.right;
    PairOfMatrices p4{a,b};
    //p1 = p4;  // ERROR!
    p1 = std::move(p4);

    /* main to the class String */
    
    String s("hi");
    String t;
    const String r = s; // no copy
    String i = s+t; // no copy
    s[0] = 'l'; // copy
    s[1] = 'l'; // no copy
    i = r+s; // copy elision
    std::cout << r << " " << i << std::endl; // hi hill (no copy)
    std::cout << r[0] << std::endl; // l (no copy)

    return 0;
}
