/*** Bartlomiej Stepek ***/
#pragma once

template <typename T>
class Matrix <T, 0, 0> {

    size_t columns = 0, rows = 0;
public:

    T* array;

    size_t numberOfRows() const { return rows; }
    size_t numberOfColumns() const { return columns; }

    Matrix(Uninitialized, size_t rows_ = 0, size_t columns_ = 0) : rows(rows_), columns(columns_) {
        array = new T[rows * columns];
        std::cout <<  "constructor of uninitialized dynamic " << rows << "x" << columns << " matrix" <<  std::endl;
    }

    Matrix() {
        for(int i = 0; i < rows*columns; i++)
            array[i] = T();
        std::cout << "constructor of dynamic " << rows << "x" << columns << " matrix" << std::endl;
    }

    Matrix(size_t rows_, size_t columns_) :
            rows(rows_), columns(columns_), array(new T[rows*columns]) {
            std::fill_n(array, rows*columns, T());
            std::cout << "constructor of dynamic " << rows << "x" << columns << " matrix\n";
    }

    Matrix(std::initializer_list <std::initializer_list <T> > list) {
        rows = list.size();
        size_t maxSize = 0;
        for(const auto & row : list)
            maxSize = std::max(maxSize, row.size());
        columns = maxSize;
        array = new T[columns * rows];
        T *p = array;
        for(auto row : list){
            T* copyEnd = std::copy(row.begin(), row.end(), p);
            std::fill(copyEnd, p + columns, T());
            p += columns;
        }
        std::cout << "constructor of dynamic " << rows << "x" << columns << " matrix from initializer_list\n";
    }

    Matrix(const Matrix & m) : rows(m.rows), columns(m.columns), array(new T[rows*columns]) {
        std::copy_n(m.array,rows*columns,array);
        std::cout << "copy constructor of dynamic matrix\n";
    }

    Matrix(Matrix && m): rows(m.rows), columns(m.columns) {
        std::cout << "move constructor of dynamic matrix\n";
        array = m.array;
        m.array = nullptr;
    }

    T operator()(size_t row, size_t col) const {
        return array[(row-1) * columns + col-1];
    }

    T& operator()(size_t row, size_t col) {
        return array[(row-1) * columns + col-1];
    }

    Matrix operator +(const Matrix & b) const {
        if(rows != b.rows || columns != b.columns)
            throw MatrixException("+");
        Matrix result(rows, columns);
        for(int i = 0; i < columns*rows; i++)
            result.array[i] = array[i] + b.array[i];
        return std::move(result);
    }

    friend Matrix operator *(const Matrix& a, const Matrix& b){
        if(a.columns != b.rows || a.rows == 0 || a.columns == 0 || b.rows == 0 || b.columns == 0)
            throw MatrixException("*");
        Uninitialized x;
        Matrix result(x, a.rows, b.columns);
        for(int i = 1; i <= a.rows; i++) {
            for(int j = 1; j <= b.columns; j++) {
                result(i,j) = 0;
                for(int z = 1; z <= a.columns; z++)
                    result(i,j) += a(i,z) * b(z,j);
            }
        }
        return result;
    }

    Matrix operator -() {
        Uninitialized x;
        Matrix new_matrix(x,numberOfRows(),numberOfColumns());
        for(size_t i = 0; i < numberOfRows()*numberOfColumns(); ++i)
            if(array[i] != 0)
                new_matrix.array[i] = -array[i];
        return new_matrix;
    }

    template <int N, int M>
    explicit operator Matrix <T,N,M>() {
        Matrix<T,N,M> new_matrix;

        for(size_t i = 0; i < N*M; ++i) {
            new_matrix.array[i] = array[i];
        }

        std::cout << "conversion from dynamic to static matrix" << std::endl;
        return new_matrix;
    }
};

template <typename T, int N, int M, int A, int B, int X, int Y>
Matrix <T, N, M> product (const Matrix<T, A, B>&a, const Matrix <T, X,Y>&b) {
        Matrix <T,N,M> result(Uninitialized {}, a.numberOfRows(), b.numberOfColumns());
        for(int i = 1; i <= a.numberOfRows(); i++) {
            for(int j = 1; j <= b.numberOfColumns(); j++) {
                result(i,j) = 0;
                for(int z = 1; z <= a.numberOfColumns(); z++){
                    result(i,j) += a(i,z) * b(z,j);
                }
            }
        }
    return result;
}

template <typename T, int R, int U>
Matrix<T,0,0> operator* (const Matrix<T,0,0>&a, const Matrix<T,R,U>&b) {
    if(a.numberOfColumns() != b.numberOfRows() ||
       a.numberOfRows() == 0 || a.numberOfColumns() == 0
       || b.numberOfRows() == 0 || b.numberOfColumns() == 0)
        throw MatrixException("*");
    return product<T,0,0> (a,b);
}

template <typename T, int R, int U>
Matrix<T,0,0> operator* (const Matrix<T,R,U>&a, const Matrix<T,0,0>&b) {
    if(a.numberOfColumns() != b.numberOfRows() ||
       a.numberOfRows() == 0 || a.numberOfColumns() == 0
       || b.numberOfRows() == 0 || b.numberOfColumns() == 0)
        throw MatrixException("*");
    return product<T,0,0> (a,b);
}

template <typename T>
Matrix <T,0,0> transpose (const Matrix <T,0,0>&a) {
    Matrix<T,0,0> result (Uninitialized{}, a.numberOfColumns(), a.numberOfRows());
    for(int i = 1; i <= a.numberOfRows(); i++) {
        for(int j = 1; j <= a.numberOfColumns(); j++)
            result (j,i) = a(i,j);
    }
    return result;
}
