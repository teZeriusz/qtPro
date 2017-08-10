#include <iostream>
#include <cinttypes>
#include <vector>

using namespace std;

class Fred {
    int i;
public:
    void test() {
        cout << "this: " << this;
    }
};

template<typename T>  // See section on templates for more
class Matrix {
public:
    Matrix(unsigned nrows, unsigned ncols);
    // Throws a BadSize object if either size is zero
    class BadSize { };
    // No need for any of The Big Three!
    // Access methods to get the (i,j) element:
    T&       operator() (unsigned i, unsigned j);        // Subscript operators often come in pairs
    const T& operator() (unsigned i, unsigned j) const;  // Subscript operators often come in pairs
    // These throw a BoundsViolation object if i or j is too big
    class BoundsViolation { };
    unsigned nrows() const;  // #rows in this matrix
    unsigned ncols() const;  // #columns in this matrix
private:
    std::vector<std::vector<T>> data_;
};

template<typename T>
inline unsigned Matrix<T>::nrows() const {
    return data_.size();
}

template<typename T>
inline unsigned Matrix<T>::ncols() const {
    return data_[0].size();
}

template<typename T>
inline T& Matrix<T>::operator() (unsigned row, unsigned col) {
  if (row >= nrows() || col >= ncols())
      throw BoundsViolation();
  return data_[row][col];
}

template<typename T>
inline const T& Matrix<T>::operator() (unsigned row, unsigned col) const {
  if (row >= nrows() || col >= ncols())
      throw BoundsViolation();
  return data_[row][col];
}

template<typename T>
//Matrix<T>::Matrix(unsigned nrows, unsigned ncols):data_ (nrows) {
//    if (nrows == 0 || ncols == 0)
//        throw BadSize();
//    for (unsigned i = 0; i < nrows; ++i)
//        data_[i].resize(ncols);

Matrix<T>::Matrix(unsigned nrows, unsigned ncols):data_ (nrows, std::vector<T>(ncols)) {
//    vector< vector<int> > vec(4, vector<int>(4));
}
//Matrix

void someFunction(Fred & f) {

}

auto createMatrix(uint32_t nrows = 10, uint32_t ncols = 20) {
    Fred matrix[nrows][ncols];

    return matrix;
}

Fred * createMatrix1(uint32_t nrows = 10, uint32_t ncols = 20) {
    Fred* matrix = new Fred[nrows * ncols];
    // Since we used a simple pointer above, we need to be VERY
    // careful to avoid skipping over the delete code.
    // That's why we catch all exceptions:
    try {
      // Here's how to access the (i,j) element:
        for (unsigned i = 0; i < nrows; ++i) {
            for (unsigned j = 0; j < ncols; ++j) {
                someFunction( matrix[i*ncols + j] );
            }
        }
    }
    catch (...) {
      delete[] matrix;
      throw;
    }
    //    delete[] matrix;
    return matrix;
}

Fred ** createMatrix2(unsigned nrows, unsigned ncols[])
{
    typedef Fred* FredPtr;
    // There will not be a leak if the following throws an exception:
    FredPtr* matrix = new FredPtr[nrows];
    // Set each element to null in case there is an exception later.
    // (See comments at the top of the try block for rationale.)
    for (unsigned i = 0; i < nrows; ++i)
        matrix[i] = nullptr;

    // Since we used a simple pointer above, we need to be
    // VERY careful to avoid skipping over the delete code.
    // That's why we catch all exceptions:
    try {
    // Next we populate the array.  If one of these throws, all
    // the allocated elements will be deleted (see catch below).
        for (unsigned i = 0; i < nrows; ++i)
            matrix[i] = new Fred[ ncols[i] ];

    // Here's how to access the (i,j) element:
        for (unsigned i = 0; i < nrows; ++i) {
            for (unsigned j = 0; j < ncols[i]; ++j) {
                someFunction( matrix[i][j] );
            }
        }
    // ...code that fiddles with the matrix...
    }
    catch (...) {
    // Make sure to do the delete when an exception is thrown:
    // Note that some of these matrix[...] pointers might be
    // null, but that's okay since it's legal to delete null.
        for (unsigned i = nrows; i > 0; --i)
            delete[] matrix[i-1];
        delete[] matrix;
        throw;    // Re-throw the current exception
    }
    // Make sure to do the delete at the end of the function too.
    // Note that deletion is the opposite order of allocation:
//    for (unsigned i = nrows; i > 0; --i)
//        delete[] matrix[i-1];
//    delete[] matrix;
    return matrix;
}

int main() {
    Fred* p;
    void* tmp = operator new(sizeof(Fred));
    cout << "Jeden ptr:" << tmp << endl;
    try {
        new(tmp) Fred();  // Placement new
        cout << "Dwa 1" << endl;
        p = (Fred*)tmp;   // The pointer is assigned only if the ctor succeeds
        cout << "Dwa 2 p:" << p << " tmp:" << tmp << " this: ";
        p->test();
        cout << endl;
    }
    catch (...) {
        operator delete(tmp);  // Deallocate the memory
        cout << "Trzy 1" << endl;
        throw;                 // Re-throw the exception
        cout << "Trzy 2" << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
