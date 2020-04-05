/*** Bartlomiej Stepek ***/
#pragma once

class MatrixException : public std::runtime_error {
    std::string x;
public:

    MatrixException(std::string x_) : std::runtime_error(""), x(x_)  {}
    std::string what() {
        std::string message = "Incompatible dimensions in operator " + x;
        return message;
    }
};

class Uninitialized{};

template <typename T, int N, int M>
class Matrix {

    size_t rows = N, columns = M;

public:

    T array [N*M];

    size_t numberOfRows() const { return rows; }
    size_t numberOfColumns() const { return columns; }

    Matrix(Uninitialized, size_t rows = N, size_t columns = M) {
        std::cout <<  "constructor of static uninitialized matrix" << std::endl;
    }

    Matrix() {
        for(int i = 0; i < rows*columns; i++)
            array[i] = T();
        std::cout << "constructor of static " << rows << "x" << columns << " matrix" << std::endl;
    }

    Matrix(const Matrix & m){
        std::copy_n(m.array,columns*rows,array);
        std::cout << "copy constructor of static matrix\n";
    }

    Matrix(std::initializer_list <std::initializer_list <T> > list) {
        T *p = array;
        for(auto row : list){
            T* copyEnd = std::copy(row.begin(), row.end(), p);
            std::fill(copyEnd, p + columns, T());
            p += columns;
        }
        std::cout << "constructor of static " << rows << "x" << columns << " matrix from initializer_list\n";
    }

    T operator()(size_t row, size_t col) const {
        return array[(row-1) * columns + col-1];
    }

    T& operator()(size_t row, size_t col) {
        return array[(row-1) * columns + col-1];
    }

    Matrix operator+ (const Matrix <T,N,M> &b) {
        Uninitialized x;
        Matrix result(x,N,M);
        for(int i = 0; i < N*M; i++)
            result.array[i] = array[i] + b.array[i];
        return result;
    }

    template <int K>
    friend Matrix <T,N,K> operator*(const Matrix<T,N,M> &a, const Matrix<T,M,K> &b) {
        Uninitialized x;
        Matrix<T,N,K> result(x);
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= K; j++) {
                result(i,j) = T();
                for(int z = 1; z <= M; z++) {
                    result(i,j) += a(i,z) * b(z,j);
                }
            }
        }
        return result;
    }

    Matrix operator -() {
        Uninitialized x;
        Matrix<T,N,M> new_matrix(x);
        for(size_t i = 0; i < numberOfRows()*numberOfColumns(); ++i)
            if(array[i] != 0)
                new_matrix.array[i] = -array[i];
        return new_matrix;
    }

    explicit operator Matrix<T,0,0> () {
        Matrix<T,0,0> new_matrix(N,M);

        for(size_t i = 0; i < N*M; ++i) {
            new_matrix.array[i] = array[i];
        }

        std::cout << "conversion from static to dynamic matrix" << std::endl;
        return new_matrix;
    }
};

template <typename T, int N, int M, int A, int B, int X, int Y>
Matrix <T, N, M> sum (const Matrix<T, A, B>&a, const Matrix <T, X,Y>&b) {
        Matrix <T,N,M> result;
        for(int i = 1; i <= a.numberOfRows(); i++) {
            for(int j = 1; j <= b.numberOfColumns(); j++) {
                result(i,j) = T();
                result(i,j) = a(i,j) + b(i,j);
            }
        }
        return result;
}

template <typename T, int R, int U>
Matrix<T,R,U> operator+ (const Matrix<T,0,0>&a, const Matrix<T,R,U>&b) {
    if(a.numberOfRows() != b.numberOfRows() || a.numberOfColumns() != b.numberOfColumns())
        throw MatrixException("+");
    return sum<T,R,U> (a,b);
}

template <typename T, int R, int U>
Matrix<T,R,U> operator+ (const Matrix<T,R,U>&a, const Matrix<T,0,0>&b) {
    if(a.numberOfRows() != b.numberOfRows() || a.numberOfColumns() != b.numberOfColumns())
        throw MatrixException("+");
    return sum<T,R,U> (a,b);
}

template <typename T, int R, int U>
Matrix <T,R,U> transpose (const Matrix <T,U,R>&a) {
    Matrix<T,R,U> result (Uninitialized{}, a.numberOfRows(), a.numberOfColumns());
    for(int i = 1; i <= a.numberOfRows(); i++) {
        for(int j = 1; j <= a.numberOfColumns(); j++)
            result (j,i) = a(i,j);
    }
    return result;
}
