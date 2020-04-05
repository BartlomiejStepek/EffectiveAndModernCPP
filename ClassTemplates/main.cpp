/*** Bartlomiej Stepek ***/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "staticMatrix.h"
#include "dynamicMatrix.h"

template <typename M>
void printMatrix(const M & m, int width = 10){
	for(int i = 1; i <= m.numberOfRows(); ++i){
		for(int j = 1; j <= m.numberOfColumns(); ++j){
			if(j != 1)
				std::cout << " ";
			std::cout << std::setw(width) <<  m(i,j) ;
		}
		std::cout << std::endl;
	}
}

template <int N, int M>
using SMatrix = Matrix<double, N, M>;

using DMatrix = Matrix<double, 0, 0>;

int main(){


    std::cout << std::fixed << std::setprecision(2);

    using KMatrix = Matrix<double, 3, 4>;
	KMatrix m0{}; // Matrix filled with zeroes
	printMatrix(m0);

	KMatrix m1({{1,  2,  3,  4},  // constructor from
		       { 5,  6,  7,  8},  // initialization_list
		       { 9, 10, 11, 12}});
	printMatrix(m1);
	KMatrix m2 = m1;              // copy constructor
	m2(2,1) = -5;  m2(3,2) = -20; // mutable access
	KMatrix m3 = m1 + m2;         // matrix sum (with equal sizes)
	// auto mm = m1 * m2; // compilation ERROR
	printMatrix(m3);

	Matrix<double, 4, 2> m4({
		{1.2, 1},
		{21, 2},
		{34, 2},
		{2, 32}});
	auto m5 = m1 * m4;    // matrix multiplication
	// auto mm = m1 + m4;   // compilation ERROR
	printMatrix(m5);

	DMatrix m00(2,3);
	printMatrix(m00);

	DMatrix m10({{1,  2,  3,  4},  // constructor from
		       { 5,  6,  7,  8},  // initialization_list
		       { 9, 10, 11, 12}});
	printMatrix(m10);

	DMatrix m20 = m10;              // copy constructor
	m20(2,1) = -5;  m20(3,2) = -20; // mutable access
	printMatrix(m20);

	DMatrix m30 = m10 + m20;         // matrix sum (with equal sizes)
    printMatrix(m30);

    try {
        auto mm0 = m10 * m20; // ERROR: exception
    } catch(MatrixException & e){
	    std::cout << " Exception : " << e.what() << std::endl;
	}

	DMatrix m40({
		{1.2, 1},
		{21, 2},
		{34, 2},
		{2, 32}});
	DMatrix m50 = m10 * m40;    // matrix multiplication
    printMatrix(m50);

    try {
        auto mm0 = m10 + m40;   // ERROR: exception
    } catch(MatrixException & e){
        std::cout << " Exception : " << e.what() << std::endl;
    }

	DMatrix m11({{1,  2,  3},  // dynamic matrix from
		       { 5,  6,  7},  // initialization_list
		       { 9, 10, 11}});
	printMatrix(m11);

	SMatrix<3,3> m21 = { {1, -1, 0},  // static matrix
                        {2, -2, 1},
                        {4, -4, 2}};
	printMatrix(m21);

	auto m31 = (SMatrix<3,3>)(m11);  // conversion from dynamic to static
    printMatrix(m31);
    auto m41 = m11 + m21 + m11;
    printMatrix(m41);

    auto m4d = static_cast<DMatrix>(m41);
    printMatrix(m4d);

    auto m51 = m31 * m11 * m21;
    printMatrix(m51);

    DMatrix m61({{4}});
    try {
        auto mm1 = m21 * m61; // ERROR: exception
    } catch(MatrixException & e){
	    std::cout << "Exception : " << e.what() << std::endl;
	}

    try {
        auto mm1 = m21 + m61;   // ERROR: exception
    } catch(MatrixException & e){
        std::cout << "Exception : " << e.what() << std::endl;
    }

	DMatrix m12({{1,  2,  3,  4},  // constructor from
		       { 5,  6,  7,  8},  // initialization_list
		       { 9, 10, 11, 12}});
	printMatrix(m12);

	DMatrix m22 = transpose(m12);              // copy constructor
	printMatrix(m22);

	SMatrix<4,2> m32({
		{1.2, 1},
		{21, 2},
		{34, 2},
		{2, 32}});
    printMatrix(m32);

	SMatrix<2,4> m42 = transpose(m32);
    printMatrix(m42);

	return 0;
}
