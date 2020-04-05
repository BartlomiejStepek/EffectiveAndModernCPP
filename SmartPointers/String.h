/*** Bartlomiej Stepek ***/

class String{

    std::shared_ptr<std::string> p;
public:

    // creates an empty string
    String(size_t size = 0) : p(new std::string(size, ' ' )) {}

    // copy C-string
    String(const char* str) : p(new std::string(str)) {}

    //no copy
    String(const String & str) : p(str.p) {}

    // no copy
    String operator=(const String & str) {
        p = str.p;
        return *this;
    }

    // makes a copy of a string if it has more than one reference.
    char & operator[](int i) {
        if(!this -> p.unique()){
            String c;
            *c.p = *p;
            *this = c;
        }
        return (*p)[i];
    }

    // no copy
    char operator[](int i) const {
        return (*p)[i];
    }

    // concatenation creates a new string only if both strings are non empty
    friend String operator+(String a, String b) {
        if((*a.p).compare(" ") != 0 && (*b.p).compare(" ") != 0) {
            std::string str = *a.p + *b.p;
            String c;
            *c.p = str;
            return c;
        }
    }

    // no copy
    friend std::ostream & operator << (std::ostream & out, String s) {
        out << *s.p;
        return out;
    }
};
