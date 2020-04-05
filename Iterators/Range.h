/*** Bartlomiej Stepek ***/
template <typename T>

class Range {

    T start = 0, stop, step = 1;
public:
    Range(T b) : stop(b) {}
    Range(T a, T b) : start(a), stop(b) {}
    Range(T a, T b, T c) : start(a), stop(b), step(c) {}
    T getStep() { return step; }
    T getStart() { return start; }
    Range(const Range& a) : start(a.start), stop(stop), step(step) {std::cout << "GHERE";}
    class iterator;
    friend class iterator;
    class iterator {

        Range& r;
        T p;
    public:
        iterator(Range& r_) : r(r_) {
            p = r.getStart();
        }
        const iterator& operator++() {
            p += r.getStep();
            return *this;
        }
        iterator operator++(int){
            iterator it(*this);
            p += r.getStep();
            return it;
        }
        T operator*() const {
            return p;
        }
        T* operator->() const{
            return *p;
        }
        bool operator != (const iterator& a) {
            return p != a.p;
        }
        bool operator == (const iterator& a) {
            return p == a.p;
        }
        bool operator < (const iterator& it) const{
            return p<it.p;
        }
        friend class Range;
    };

    iterator begin(){
        return iterator(*this);
    }
    iterator end(){
        iterator it(*this);
        while(it.p < stop)
            ++it;
        return it;
    }
};

template <typename T>
Range<T> make_range(T a, T b, T c) {
    Range <T> r(a,b,c);
    return r;
}

template <typename T>
Range<T> make_range(T a, T b) {
    Range<T> r(a,b);
    return r;
}

template <typename T>
Range<T> make_range(T b) {
    Range<T> r(b);
    return r;
}
