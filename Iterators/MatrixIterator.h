/*** Bartlomiej Stepek ***/
template <typename T, int N, int M>
class Matrix {
    size_t rows = N, columns = M;
    T array [N*M];

public:
    size_t numberOfRows() const { return rows; }
    size_t numberOfColumns() const { return columns; }

    Matrix() {
        for(int i = 0; i < rows*columns; i++)
            array[i] = T();
    }
    Matrix(size_t r, size_t c) : rows(r), columns(c) {

        for(int i = 0; i < r*c; i++)
            array[i] = T();
    }
    Matrix(const Matrix & m){
        std::copy_n(m.array,columns*rows,array);
    }
    Matrix(std::initializer_list <std::initializer_list <T> > list) {
        T *p = array;
        for(auto row : list){
            T* copyEnd = std::copy(row.begin(), row.end(), p);
            std::fill(copyEnd, p + columns, T());
            p += columns;
        }
    }
    T operator()(size_t row, size_t col) const {
        return array[(row-1) * columns + col-1];
    }
    T& operator()(size_t row, size_t col) {
        return array[(row-1) * columns + col-1];
    }
    class iterator;
    friend class iterator;
    class row_iterator;
    friend class row_iterator;
    class col_iterator;
    friend class col_iterator;

    class iterator {
        Matrix& m;
        T* p;
    public:
        iterator(Matrix& m_) : m(m_) {
            p = &m(1,1);
        }
        const iterator& operator++() {
            p += 1;
            return *this;
        }
        iterator operator++(int){
            iterator it(*this);
            p += 1;
            return it;
        }
        T operator*() const {
            return *p;
        }
        T* operator->() const{
            return p;
        }
        bool operator != (const iterator& a) {
            return *p != *a.p;
        }
        bool operator == (const iterator& a) {
            return *p == *a.p;
        }
        bool operator < (const iterator& it) const{
            return *p < *it.p;
        }
        friend class Matrix;
    };

    class row_iterator {
        Matrix& m;
        size_t row;
        T* p;
    public:
        row_iterator(Matrix& m_, size_t row_) : m(m_), row(row_) {
            p = &m(row,1);
        }
        const row_iterator& operator++() {
            p += 1;
            return *this;
        }
        row_iterator operator++(int){
            row_iterator it(*this);
            p += 1;
            return it;
        }
        T operator*() const {
            return *p;
        }
        T* operator->() const{
            return p;
        }
        bool operator != (const row_iterator& a) {
            return *p != *a.p;
        }
        bool operator == (const row_iterator& a) {
            return *p == *a.p;
        }
        bool operator < (const row_iterator& it) const{
            return *p < *it.p;
        }
        friend class Matrix;
    };

    class col_iterator {
        Matrix& m;
        size_t col;
        T* p;
    public:
        col_iterator(Matrix& m_, size_t col_) : m(m_), col(col_) {
            p = &m(1,col);
        }
        const col_iterator& operator++() {
            p += m.columns;
            return *this;
        }
        col_iterator operator++(int){
            col_iterator it(*this);
            p += m.columns;
            return it;
        }
        T operator*() const {
            return *p;
        }
        T* operator->() const{
            return p;
        }
        bool operator != (const col_iterator& a) {
            return *p != *a.p;
        }
        bool operator == (const col_iterator& a) {
            return *p == *a.p;
        }
        bool operator < (const col_iterator& it) const{
            return *p < *it.p;
        }
        friend class Matrix;
    };

    iterator begin(){
        return iterator(*this);
    }
    iterator end(){
        iterator it(*this);
        it.p += columns*rows;
        return it;
    }
    row_iterator row_begin (size_t a) {
        row_iterator it(*this, a);
        return it;
    }
    row_iterator row_end (size_t a) {
        row_iterator it(*this, a);
        it.p += columns;
        return it;
    }
    col_iterator col_begin (size_t a) {
        col_iterator it(*this, a);
        return it;
    }
    col_iterator col_end (size_t a) {
        col_iterator it(*this, a);
        it.p += rows*columns;
        return it;
    }
};
