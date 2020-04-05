/*** Bartlomiej Stepek ***/
#include <iostream>
#include <algorithm>
#include "Matrix.h"
#include "MatrixWithLabel.h"

int main(){

	Matrix m1;
	Matrix m2(3,4);
	Matrix m3({{1,2,3},{32, 23, 22},{3,234,23,44}});
	std::cout << m2(1,1) << std::endl;  // 0
	std::cout << m3(2,2) << std::endl;  // 23
	std::cout << m3;

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

	std::cout << "Inheritance \n";
	MatrixWithLabel l0("B", 3, 4);
	MatrixWithLabel l1({{1,2},{4,5}});
	l1.setLabel("A");
	MatrixWithLabel l2 = l1;
	MatrixWithLabel l3 = std::move(l1);
	std::cout << l2.getLabel() << " " << l3.getLabel() << std::endl;
	std::cout << l1.getLabel() << std::endl;

	return 0;
}
