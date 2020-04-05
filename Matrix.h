/*** Bartlomiej Stepek ***/

class Matrix{

protected:
    size_t numberOfRows;
    size_t numberOfCols;
    double *data;

public:

    Matrix()
        :   numberOfCols(0), numberOfRows(0), data(nullptr) {}

    Matrix(size_t rows, size_t cols)
        :   numberOfRows(rows), numberOfCols(cols),
            data(new double[rows*cols])
        {
            std::fill_n(data, rows*cols, 0.0);
            std::cout << " constructor of " << rows << "x" << cols << " matrix\n";
        }

    Matrix(std::initializer_list <std::initializer_list <double> > list) {
        numberOfRows = list.size();
        size_t maxSize = 0;
        for(const auto & row : list)
            maxSize = std::max(maxSize, row.size());

        numberOfCols = maxSize;
        data = new double[numberOfCols * numberOfRows];
        double *p = data;
        for(auto row : list){
            double* copyEnd = std::copy(row.begin(), row.end(), p);
            std::fill(copyEnd, p + numberOfCols, 0.0);
            p += numberOfCols;
        }
        std::cout << " constructor of " << list.size() << "x" << maxSize << " matrix from initializer_list\n";
    }

    double operator()(size_t row, size_t col) const {
        return data[(row-1) * numberOfCols + col-1];
    }

    double& operator()(size_t row, size_t col) {
        return data[(row-1) * numberOfCols + col-1];
    }

    friend std::ostream& operator << (std::ostream& out, const Matrix & m){
        for(size_t i=1; i <= m.numberOfRows; i++){
            out << "{";
            for(size_t j=1; j <= m.numberOfCols; ++j){
                out << m(i,j);
                if(j != m.numberOfCols)
                    out << ", ";
            }
            out << "}\n";
        }
        return out;
    }

    Matrix(const Matrix & m)
        :   numberOfRows(m.numberOfRows),
            numberOfCols(m.numberOfCols),
            data(new double[numberOfCols*numberOfRows])
        {
            std::copy_n(m.data,numberOfCols*numberOfRows,data);
            std::cout << " copy constructor\n";
        }

    Matrix& operator = (const Matrix& m){
        if(&m == this) return *this;
        numberOfRows = m.numberOfRows;
        numberOfCols = m.numberOfCols;
        delete[] data;
        data = new double[m.numberOfCols*m.numberOfRows];
        std::copy(m.data, m.data+numberOfCols*numberOfRows, data);
        std::cout << " copy assignment operator\n";
        return *this;
    }

    Matrix(Matrix && m)
        :   numberOfRows (std::move(m.numberOfRows)),
            numberOfCols (std::move(m.numberOfCols))
        {
            std::cout << " move constructor\n";
            this->data = m.data;
            m.data = nullptr;
        }

    Matrix& operator = (Matrix&& m){
        if(&m == this) return *this;
        numberOfRows = std::move(m.numberOfRows);
        numberOfCols = std::move(m.numberOfCols);
        delete[] data;
        data = new double[m.numberOfCols*m.numberOfRows];
        data = std::move(m.data);
        m.data = nullptr;
        std::cout << " move assignment operator\n";
        return *this;
    }

    Matrix operator -() {
        Matrix new_matrix(numberOfRows, numberOfCols);
        for(size_t i = 0; i < numberOfRows*numberOfCols; ++i)
            if(data[i] != 0)
                new_matrix.data[i] = -data[i];

        return new_matrix;
    }

    ~Matrix() {
        delete[] data;
    }
};
