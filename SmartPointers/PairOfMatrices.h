/*** Bartlomiej Stepek ***/

class PairOfMatrices {

public:
    Matrix left, right;
    PairOfMatrices(Matrix m1, Matrix m2)
    : left(m1), right(m2) {}
    PairOfMatrices& operator= (PairOfMatrices&& ) = default;
    PairOfMatrices& operator= (PairOfMatrices& ) = delete;
    PairOfMatrices(PairOfMatrices&& ) = default;
    PairOfMatrices(PairOfMatrices& ) = delete;
};
