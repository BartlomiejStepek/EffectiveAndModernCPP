/*** Bartlomiej Stepek ***/

class MatrixWithLabel : public Matrix {

    std::string label = "A";

public:
    using Matrix::Matrix;

    MatrixWithLabel(std::string label_, size_t numberOfRows, size_t numberOfCols) :
        Matrix(numberOfRows, numberOfCols), label(label_) {}

    MatrixWithLabel(std::string label_, std::initializer_list<std::initializer_list <double> > list) :
        Matrix(list), label(label_) {}

    void setLabel(std::string label_) {
        label = label;
    }

    std::string getLabel() const {
        return label;
    }

    MatrixWithLabel(const MatrixWithLabel & m) : Matrix(m), label(m.label) {
        std::cout << "copy constructor in MatrixWithLabel\n";
    }

    MatrixWithLabel(MatrixWithLabel && m) = default;

    MatrixWithLabel& operator = (MatrixWithLabel&& m) = default;
};
