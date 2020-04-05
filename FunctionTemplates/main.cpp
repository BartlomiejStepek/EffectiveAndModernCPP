/*** Bartlomiej Stepek ***/
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "FunctionTemplates.h"

int main()
{
    std::cout << sqr(4) << std::endl; // 16
    std::cout << sqr(14.5) << std::endl; // 210.25
    std::cout << sqr(std::string("hey")) << std::endl; // heyhey

    std::cout << mod<5>(131) << std::endl; // 1
    std::cout << mod<7>(131) << std::endl; // 5
    std::cout << mod<0>(131) << std::endl; // -131

    std::vector<int> v = {1, 21, 34, 4, 15};
    print(v); // 1 21 34 4 15
    std::list<double> l = {1, 2.1, 3.2, 6.3};
    print(l); // 1 2.1 3.2 6.3

    auto w = apply(v, sqr<int>);
    auto w2 = apply(w, mod<5> );
    print(w2); // 1 1 1 1 0
    auto l2 = apply(l, sqr<double>);
    auto l3 = apply(l2, mod<5>);

    print(l3); // 1 4 0 4
    // function sin is overloaded, we need to cast it
    auto l4 = apply(l3, static_cast<double(*)(double)>(sin));
    print(l4); // 0.841471 -0.756802 0 -0.756802

    int a = 1, b=-6;
    float y = 1.0 + 1e20 - 1e20, x = 1.0;
    std::cout << compare(a,b) << " " << compare(b,a) << " " << compare(a,a) << std::endl;
    std::cout << compare(x,y) << " " << compare(y,x) << " " << compare(x,x) << std::endl;
    std::cout << compare(&a,&b) << " " << compare(&b,&a) << " " << compare(&a,&a) <<std::endl;
    std::cout << compare(&x,&y) << " " << compare(&y,&x) << " " << compare(&x,&x) <<std::endl;
    std::cout << compare("Alpha", "Alfa") <<std::endl;

    double a1[] = {1, 2, 3, 4};
    process<double, sin, 4> (a1);
    for( auto x: a1)
        std::cout << x << " "; // 0.841471 0.909297 0.14112 -0.756802
    std::cout << std::endl;

    std::vector<int> v1={1, 2, 13, 4, 5, 54};
    std::list<int> result = selectIf<std::list>(v1, biggerThan5);
    print(result);
}
