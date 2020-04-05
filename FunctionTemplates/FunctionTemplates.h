template <typename T>
T sqr(T x) {
    return x*x;
}

template <>
std::string sqr(std::string x) {
    return x+x;
}

template <int N>
int mod (int x) {
    return x%N;
}

template <>
int mod <0> (int x) {
    return -x;
}

template <typename Container>
void print(const Container &v) {
    for(auto el : v)
        std::cout << el << " ";
    std::cout << std::endl;
}

template <typename C, typename F>
C apply (const C& c, F f) {

    C result;
    for(auto el : c)
        result.push_back(f(el));

    return result;
}

template <typename T>
int compare(T a, T b) {
    if(a < b)
        return 1;
    else if(a > b)
        return -1;
    else
        return 0;
}

template <typename T>
int compare (T* a, T* b) {
    if(*a < *b)
        return 1;
    else if(*a > *b)
        return -1;
    else
        return 0;
}

template <>
int compare (const char* a, const char* b) {
    int k = -1;
    while(true) {
        k++;
        if(a[k] == '\0' && b[k] == '\0')
            return 0;
        else if(a[k] == '\0')
            return 1;
        else if(b[k] == '\0')
            return -1;

        if(a[k] > b[k]) return -1;
        else if(a[k] < b[k]) return 1;
    }
}

template <typename T, T (*f)(T), int N>
void process(T array[]) {
    for(int i = 0; i < N; i++)
        array[i] = f(array[i]);
}

template < template <typename, typename> typename OutContainer, typename T, typename Alloc,
            template <typename, typename> typename InContainer, typename Predicate>
OutContainer <T,Alloc> selectIf (InContainer<T,Alloc> c, Predicate p) {

    OutContainer <T, Alloc> container;
    for(auto el : c) {
        if(p(el))
            container.push_back(el);
    }
    return container;
}

bool biggerThan5(int x){
    return x>5;
}
