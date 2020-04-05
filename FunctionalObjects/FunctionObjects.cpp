/*** Bartlomiej Stepek ***/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

class Printer {

    std::ostream& function;
    std::string a1, a2;

public:

    Printer(std::ostream& out, std::string a1_, std::string a2_) :
        function(out), a1(a1_), a2(a2_) {}

    auto operator()(auto x) const {
        function << a1 << x << a2;
        return &function;
    }

};

int main(){

    Printer print(std::cout,  "[ ", " ] " );   // creates unary functor
                                                      //that takes argument x of any type
                                                      // and prints [ x ]
    print("hello");    // [ hello ]
    std::vector<int> v = {1, 2, 3, 4};
    std::for_each(v.begin(), v.end(), print);  // [ 1 ] [ 2 ] [ 3 ] [ 4 ]
    std::ofstream file("myFile.txt");
    Printer filePrinter(file, "- ", "\n");
    filePrinter(5);
    filePrinter("My text");
    return 0;
}
