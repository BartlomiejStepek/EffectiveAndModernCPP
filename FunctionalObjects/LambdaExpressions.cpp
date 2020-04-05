/*** Bartlomiej Stepek ***/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <cassert>
#include <numeric>
#include <cmath>
#include <type_traits>

void print(const std::vector<int> & v){
	for( auto x  : v) std::cout << x << " ";
	std::cout << std::endl;
}

int main(){
    std::vector<int> v = {256, 64, 16*3, 16*9, 16, 8*7, 9, 3, 1, 6, 2, 5};
    print(v);

    int center = 50;
	std::sort(v.begin(), v.end(),[&center](int a, int b) { return abs(center - a) < abs(center - b); } );
    print(v);

    auto sharkovsky = [](int a, int b) {
        int power_2_a = 0;
        int power_2_b = 0;
        int rest_a = 0;
        int rest_b = 0;
        while(a != 1) {
            if( a%2 == 0) {
                a /= 2;
                power_2_a++;
            } else {
                rest_a = a;
                a = 1;
            }
        }
        while(b != 1) {
            if( b%2 == 0) {
                b /= 2;
                power_2_b++;
            } else {
                rest_b = b;
                b = 1;
            }
        }

        if(rest_a == 0 && rest_b == 0)
            return power_2_a < power_2_b;

        else if(rest_a == 0) return true;
        else if(rest_b == 0) return false;
        else {
            if(power_2_a > power_2_b) return true;
            else if(power_2_a < power_2_b) return false;
            else {
                return rest_a > rest_b;
            }
        }
    };

    assert(sharkovsky(1,2));
    assert(sharkovsky(2,4));
    assert(sharkovsky(64,256));
    assert(sharkovsky(256,256*3));
    assert(sharkovsky(256*9,256*5));
    assert(sharkovsky(256*3,64*9));
    assert(!sharkovsky(1,1));
    assert(!sharkovsky(4,2));
    assert(!sharkovsky(256,64));
    assert(!sharkovsky(256*3,256));
    assert(!sharkovsky(256*5,256*9));
    assert(!sharkovsky(64*9,256*3));

    std::sort(v.begin(), v.end(), sharkovsky);
    print(v);

	srand(2019);
    int a = 0, b = 40;
    auto generator = [&a, &b]() {
        return a + rand() % (( b + 1 ) - a);
    };

    std::generate(v.begin(), v.end(), generator);
    print(v);

    a = 100, b = 200;
    std::generate(v.begin(), v.end(), generator);
    print(v);

    a = -10; b=10;
    const auto evenGenerator = [ a = static_cast<const int&>(a),b = static_cast<const int&>(b)](){
        return a + rand() % (( b + 1 ) - a);
    };
    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);

    v.resize(20);
    a = 0; b=100;
    std::generate(v.begin(), v.end(), evenGenerator);
    print(v);

    auto l1_norm = [](auto a){
        return accumulate(a.begin(), a.end(), 0.0,
            [](auto suma, auto a){ return abs(a) + suma; } );
    };
    std::cout << l1_norm(v) << std::endl;

    std::vector<double> m = { 1.4, 2.4, -2.4, -4.2, -43.3 };
    std::cout << l1_norm(m) << std::endl;

    std::list<double> l(m.begin(), m.end());

    std::cout << l1_norm(l) << std::endl;

    auto wielomian = [](auto a[], int n) {
        return [&a, &n](auto x) {
            auto suma = 0;
            for(int i=0; i<= n; i++)
                suma += pow(x, i)*a[i];
            return suma;
        };
    };

    double a_[] = {1, 2, 3, 4, 5};
    auto w1  = wielomian(a_, 4);
    std::cout << w1(1.0) << " " << w1(0.0) << " " << w1(2.0) << std::endl;
    auto w2  = wielomian(a_, 2);
    std::cout << w2(1.0) << " " << w2(0.0) << " " << w2(2.0) << std::endl;

    return 0;
}
