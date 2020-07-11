//
// Created by danaa on 6/28/2020.
//
#ifndef HW3_MATRIX_H
#define HW3_MATRIX_H
#include "Auxiliaries.h"
#include <iostream>
#include <string>

namespace mtm {
    template<class T>
    class Matrix {
        int col;
        int row;
        T** element;
    public:

        class AccessIllegalElement : public std::exception{
        public:
            char const *what() const noexcept override;
        };
        /**
         * this class defines a type od exception that is responsible for alarming whenever a user is accessing
         * an element out of the matrix boarders.
         */

        class IllegalInitialization: public std::exception {
        public:
            char const *what() const noexcept override;
        };
        /**
         * this class defines a type od exception that is responsible for alarming whenever a user is initializing
         * the matrix with illegal initialization, i.e. zero rows or cols.
         */

        class DimensionMismatch : public std::exception {
            std::string err;
        public:
            explicit DimensionMismatch(int row1 , int col1 , int row2, int col2);

            ~DimensionMismatch();

            char const *what() const noexcept override;
        };
        /**
         * this class defines a type od exception that is responsible for alarming whenever a user is summing
         * or reducing two matrices of unmatched rows or cols.
         */

        explicit Matrix(const Dimensions &dims, T data = T());

        /**
         * a constructor that creates a matrix and initializes it what a certain value.
         * @param dims : the row and col of the matrix
         * @param data : the initial value that each element of the matrix gets.
         */

        ~Matrix();

        /**
         * destructor of the matrix that deletes every element of it and frees it.
         * @param matrix
         */

        Matrix(const Matrix<T> &matrix);

        /**
         * copy constructor which copies a matrix into other
         * @param other : the other matrix that gets copied
         */

        Matrix<T> operator=(const Matrix<T> &other);

        /**
         * operator = : responsible for placing a matrix into the one used
         * @param other : the other matrix
         * @return : a pointer to this
         */

        static Matrix Diagonal(int size, T data = T());

        /**
         * creates a diagonal matrix based on a certain value
         * @param size : the length of the row and col of the matrix
         * @return : the diagonal matrix created
         */

        int height() const;

        /**
         * @param : matrix
         * @return the height of the matrix - the number of rows
         */

        int width() const;

        /**
      * @param : matrix
      * @return the width of the matrix - the number of cols
      */

        int size() const;

        /**
      * @param : matrix
      * @return the numbers of elements in the matrix
      */

        Matrix<T> transpose();

        /**
         * transposes a given matrix
         * @param matrix
         * @return the flipped matrix
         */

        Matrix<T> operator+(const Matrix<T> &matrix) const;

        /**
         * operator + : sums two matrices
         * @return : the sum result
         */

        Matrix<T> operator-() const;

        /**
         * @param matrix
         * @return the negative form of the matrix
         */

        Matrix<T> operator-(const Matrix<T> &matrix) const;

        /**
         * operator - that reduces two matrices
         * @return the reduction result
         */


        Matrix<T>& operator+=(T object);
        /**
         * operator += adds to the current matrix a certain object
         * @param object
         * @return the sum result
         */


        T &operator()(const int row, const int col);
        /**
         * operator () with allowance to change the element
         * @param row : the row index
         * @param col : the col index
         * @return the element in the requested place
         */

        T operator()(const int row, const int col) const;
        /**
         * operator () that doesn't change the element
         * @param row : the row index
         * @param col : the col index
         * @return the element in the requested place
         */

        //boolean operators: compares the matrix with a specific object and returns a matrix in which each element
        //represent the result of the comparison (if true or false)
        Matrix<bool> operator<(T object) const;

        Matrix<bool> operator>(T object) const;

        Matrix<bool> operator<=(T object) const;

        Matrix<bool> operator>=(T object)const;

        Matrix<bool> operator==(T object) const;

        Matrix<bool> operator!=(T object)const;

        // a class intended for an iterators that runs throught the elements of the matrix
        class iterator {
            Matrix<T> *matrix;
            int row;
            int col;

            friend class Matrix;

            iterator(Matrix<T> *matrix, int row, int col) : matrix(matrix), row(row), col(col) {}
            /**
             * constructor for the iterator
             */

        public:
            iterator(const iterator &iter);

            /**
             * a copy constructor for the iterator
             */

            ~iterator()= default;
            /**
             * a default destructor for the iterator
             */

            iterator operator=(const iterator &other);
            /**
            * operator =
            * @param other
            * @return the iterator placement of other
            */

            T &operator*() const;
            /**
             * a pointer of the current iterator
             * @return the value of that iterator
             */

            iterator operator++(int);
            /**
            * operator ++ that increases the index of that iterator by one
            * @return the next iterator (++ first)
            */

            iterator &operator++();
            /**
            * operator ++ that increases the index of that iterator by one
            * @return the next iterator
            */

            bool operator==(const iterator &i) const;
            /**
             * checks if two iterators are the same
             * @param i : iterator
             * @return true if yes, else false
             */

            bool operator!=(const iterator &i) const;
            /**
            * checks if two iterators are not the same
            * @param i : iterator
            * @return true if yes, else false
            */
        };

        iterator begin();
        /**
        * @return a pointer to the start of the matrix
        */

        iterator end();
        /**
        * @return a pointer to the end of the matrix
         */

        // a class for a const iterator which is basically the same as the usual iterator but the only change is that
        // it doesn't allow any change to the element of the matrix
        class const_iterator {
            const Matrix<T> *matrix;
            int c_row;
            int c_col;

            friend class Matrix<T>;

            const_iterator(const Matrix<T> *matrix, const int c_row, const int c_col) : matrix(matrix), c_row(c_row),
                                                                                        c_col(c_col) {}
        public:

            const_iterator(const const_iterator &const_iter);

            ~const_iterator()= default;

            T operator*() const;

            const_iterator operator++(int);

            const_iterator &operator++();

            bool operator==(const const_iterator &i) const;

            bool operator!=(const const_iterator &i) const;

            iterator operator=(const const_iterator &);

        };

        const_iterator begin() const;

        const_iterator end() const;

        template<class functor>
        Matrix apply(functor obj) const;

    };
    template <class T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat);

    template<class T>
    Matrix<T> operator+(T data, const Matrix<T>& matrix);

    template<class T>
    Matrix<T> operator+(const Matrix<T>& matrix, T data);

    template<class T>
    bool all(Matrix<T> matrix);

    template<class T>
    bool any(Matrix<T> matrix);
}

template<class T>
char const *mtm::Matrix<T>::IllegalInitialization::what()  const noexcept{
    {
        return "Mtm matrix error: Illegal initialization values";
    }
}

template<class T>
char const *mtm::Matrix<T>::Matrix::AccessIllegalElement::what()  const noexcept{
    return "Mtm matrix error: An attempt to access an illegal element";
}

template<class T>
mtm::Matrix<T>::DimensionMismatch::DimensionMismatch(int row1, int col1, int row2 , int col2) {
    err = "Mtm matrix error: Dimension mismatch: (" + std::to_string(row1) + ","
                    + std::to_string(col1) + ") (" + std::to_string(row2) + ","
                    + std::to_string(col2) + ")";
}

template<class T>
mtm::Matrix<T>::DimensionMismatch::~DimensionMismatch() = default;

template<class T>
char const *mtm::Matrix<T>::DimensionMismatch::what() const noexcept{
    return err.c_str();
}

template<class T>
mtm::Matrix<T>::Matrix(const mtm::Dimensions &dims, T data) {
    if (dims.getCol() <= 0 || dims.getRow() <= 0) {
        throw IllegalInitialization();
    }
    row = dims.getRow();
    col = dims.getCol();
    element= new T*[dims.getRow()];
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        element[i] = new T[col];
    }
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            element[i][j] = data;
        }
    }

}

template<class T>
mtm::Matrix<T>::~Matrix() {
    int i = 0;
    for (i = 0; i <row; i++) {
        delete[] element[i];
    }
    delete[] element;

}

template<class T>
mtm::Matrix<T>::Matrix(const mtm::Matrix<T> &matrix) {
    row=matrix.row;
    col=matrix.col;
    element=new T*[row];
    int i = 0, j = 0;
    for (i=0; i < matrix.height(); i++) {
        element[i] = new T[col];
    }
    for (i=0; i< matrix.height() ; i++){
        for (j=0; j <matrix.width(); j++) {
            element[i][j] = matrix.element[i][j];
        }
    }
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::operator=(const mtm::Matrix<T>& other) {
    if (this== &other)
    {
        return *this;
    }
    int i=0;
    for (i=0 ; i<row ; i++){
        delete[] element[i];
    }
    delete[] element;
    row=other.row;
    col=other.col;
    element=new T*[row];
    for (i=0 ; i< row ; i++) {
        element[i]=new T[col];
    }
    int j=0;
    for (int i=0; i<row; i++){
        for (j=0 ; j<col ; j++){
            element[i][j]=other.element[i][j];
        }
    }
    return  *this;
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::Diagonal(int size, T data) {
    Dimensions dims(size,size);
    if (size <= 0) {
        throw IllegalInitialization();
    }
    Matrix<T> diagonal(dims,data);
    int i=0, j=0;
    for (i=0; i <size; i++) {
        for (j=0; j <size; j++) {
            if (i != j) {
                diagonal.element[i][j] = T();
            } else {
                diagonal.element[i][j]= data;
            }
        }
    }
    return diagonal;
}

template<class T>
int mtm::Matrix<T>::height() const {
    return row;
}

template<class T>
int mtm::Matrix<T>::width() const {
    return col;
}

template<class T>
int mtm::Matrix<T>::size() const {
    return row * col;
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::transpose() {
    Dimensions dims(col,row);
    Matrix matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < dims.getRow(); i++) {
        for (j = 0; j < dims.getCol(); j++) {
            matrix.element[i][j] = element[j][i];
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::operator+(const mtm::Matrix<T> &matrix) const{
    if (row != matrix.height() || col != matrix.width()) {
        throw DimensionMismatch(row,col,matrix.height(),matrix.width());
    }
    Dimensions dims(matrix.height(), matrix.width());
    Matrix<T> sum(dims);
    int i = 0, j = 0;
    for (i=0; i < matrix.height(); i++) {
        for (j=0; j < matrix.width(); j++) {
            sum.element[i][j] = element[i][j] + matrix.element[i][j];
        }
    }
    return sum;
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::operator-() const {
    Dimensions dims(this->row, this->col);
    Matrix negative(dims);
    int i = 0, j = 0;
    for (i = 0; i < this->row; i++) {
        for (j = 0; j < this->col; j++) {
            negative.element[i][j] = -(this->element[i][j]);
        }
    }
    return negative;
}

template<class T>
mtm::Matrix<T> mtm::Matrix<T>::operator-(const mtm::Matrix<T> &matrix) const {
    if (this->row != matrix.height() || this->col != matrix.width()) {
        throw DimensionMismatch(row,col,matrix.height(),matrix.width());
    }
    Dimensions dims(this->row, this->col);
    Matrix result(dims);
    int i = 0, j = 0;
    for (i = 0; i < this->row; i++) {
        for (j = 0; j < this->col; j++) {
            result(i,j) = element[i][j]-matrix(i,j) ;
        }
    }
    return result;
}

template<class T>
mtm::Matrix<T> &mtm::Matrix<T>::operator+=(T object) {
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            element[i][j] += object;
        }
    }
    return *this;
}

template<class T>
T & mtm::Matrix<T>::operator()(const int row, const int col) {
    if (row<0 || col< 0 || row >=this->height() || col>=this->width()) {
        throw AccessIllegalElement();
    }
    return element[row][col];
}

template<class T>
T mtm::Matrix<T>::operator()(const int row, const int col) const {
    if(row<0 || col< 0 || row >=this->height() || col>=this->width()){
        throw AccessIllegalElement();
    }
    return element[row][col];
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<(T object) const{
    Dimensions dims(row,col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] < object) {
                matrix(i,j) = true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>(T object) const{
    Dimensions dims(row,col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] > object) {
                matrix(i,j) = true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator<=( T object)const {
    Dimensions dims(row, col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] <= object) {
                matrix(i,j) = true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator>=(T object)const  {
    Dimensions dims(row,col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] >= object) {
                matrix(i,j) = true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator==( T object)const {
    Dimensions dims(row, col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] == object) {
                matrix(i,j)= true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template<class T>
mtm::Matrix<bool> mtm::Matrix<T>::operator!=( T object)const {
    Dimensions dims(row,col);
    Matrix<bool> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (element[i][j] != object) {
                matrix(i,j)= true;
            }
            else {
                matrix(i,j)=false;
            }
        }
    }
    return matrix;
}

template <class T>
std::ostream& mtm::operator<<(std::ostream &os, const mtm::Matrix<T>& mat) {
    return mtm::printMatrix(os,mat.begin(),mat.end(),mat.width());
}

template<class T>
bool mtm::all(mtm::Matrix<T> matrix) {
    int i = 0, j = 0;
    for (i = 0; i < matrix.height(); i++) {
        for (j = 0; j < matrix.width(); j++) {
            if (!matrix(i,j)) {
                return false;
            }
        }
    }
    return true;
}

template<class T>
bool mtm::any(Matrix<T> matrix) {
    int i=0,j=0;
    for (i = 0; i <matrix.height(); i++) {
        for (j = 0; j < matrix.width(); j++) {
            if (matrix(i,j)) {
                return true;
            }
        }
    }
    return false;
}

template<class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::begin() {
    iterator iter(this,0,0);
    return iter;
}

template<class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::end() {
    iterator last(this, (*this).height(), 0);
    return last;
}

template<class T>
typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::begin() const{
    const_iterator c_iter(this,0,0);
    return c_iter;
}

template<class T>
typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::end() const{
    const_iterator last(this, (*this).height(), 0);
    return last;
}

template<class T>
template<class functor>
mtm::Matrix<T> mtm::Matrix<T>::apply(functor obj) const {
    Dimensions dims(this->height(), this->width());
    Matrix<T> matrix(dims);
    int i = 0, j = 0;
    for (i = 0; i < this->height(); i++) {
        for (j = 0; j < this->width(); j++) {
            matrix(i, j) = obj((*this)(i, j));
        }
    }
    return matrix;
}


template<class T>
mtm::Matrix<T>::iterator::iterator(const mtm::Matrix<T>::iterator &iter) {
    this->matrix = iter.matrix;
    this->row = iter.row;
    this->col = iter.col;
}

template<class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::iterator::operator=(const mtm::Matrix<T>::iterator &other) {
    if(&other != this) {
        delete this;
        this->matrix = other.matrix;
        this->row = other.row;
        this->col = other.col;
    }
    return *this;
}

template<class T>
T &mtm::Matrix<T>::iterator::operator*() const {
    if(row<0 || col<0 || row>=matrix->height() || col>=matrix->width()){
        throw AccessIllegalElement();
    }
    return (*matrix)(row, col);
}

template<class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::iterator::operator++(int) {
    iterator iter(this->matrix, this->row, this->col);
    if (this->col >= (*matrix).width() - 1) {
        this->row++;
        this->col = 0;
    } else {
        this->col++;
    }
    return iter;
}

template<class T>
typename mtm::Matrix<T>::iterator &mtm::Matrix<T>::iterator::operator++() {
    if (this->col >= (*matrix).width() - 1) {
        this->row++;
        this->col = 0;
    } else {
        this->col++;
    }
    return *this;
}

template<class T>
bool mtm::Matrix<T>::iterator::operator==(const mtm::Matrix<T>::iterator &i) const {
    if (i.row == this->row && i.col == this->col) {
        return true;
    }
    return false;
}

template<class T>
bool mtm::Matrix<T>::iterator::operator!=(const mtm::Matrix<T>::iterator &i) const {
    if (i.row != this->row || i.col != this->col) {
        return true;
    }
    return false;
}


template<class T>
mtm::Matrix<T>::const_iterator::const_iterator(const mtm::Matrix<T>::const_iterator &const_iter) {
    this->matrix = const_iter.matrix;
    this->c_row = const_iter.c_row;
    this->c_col = const_iter.c_col;
}

template<class T>
T mtm::Matrix<T>::const_iterator::operator*() const {
    if (c_row < 0 || c_col < 0 || c_row >= matrix->height() || c_col>=matrix->width()) {
        throw AccessIllegalElement();
    }
    return (*matrix)(c_row, c_col);

}

template<class T>
typename mtm::Matrix<T>::const_iterator mtm::Matrix<T>::const_iterator::operator++(int) {
    Matrix::const_iterator iter(this->matrix, c_row, c_col);
    if (c_col >= (*matrix).width() - 1) {
        c_row++;
        c_col = 0;
    } else {
        c_col++;
    }
    return iter;
}

template<class T>
typename mtm::Matrix<T>::const_iterator &mtm::Matrix<T>::const_iterator::operator++() {
    if (c_col >= (*matrix).width() - 1) {
        c_row++;
        c_col = 0;
    } else {
        c_col++;
    }
    return *this;
}

template<class T>
bool mtm::Matrix<T>::const_iterator::operator==(const mtm::Matrix<T>::const_iterator &i) const {
    if (i.c_col == this->c_col && i.c_row == this->c_row) {
        return true;
    }
    return false;
}

template<class T>
bool mtm::Matrix<T>::const_iterator::operator!=(const mtm::Matrix<T>::const_iterator &i) const {
    if (i.c_col != this->c_col || i.c_row != this->c_row) {
        return true;
    }
    return false;
}

template<class T>
typename mtm::Matrix<T>::iterator mtm::Matrix<T>::const_iterator::operator=(const mtm::Matrix<T>::const_iterator &other) {
    if(&other != this) {
        delete this;
        this->matrix = other.matrix;
        this->c_row = other.c_row;
        this->c_col = other.c_col;
    }
    return *this;
}

template<class T>
mtm::Matrix<T> mtm::operator+(T data, const mtm::Matrix<T> &matrix) {
    mtm::Dimensions dims(matrix.height(),matrix.width());
    mtm::Matrix<T> sum(dims);
    int i=0,j=0;
    for (i=0; i<matrix.height(); i++) {
        for (j=0; j<matrix.width();j++) {
            sum(i,j) = data + matrix(i,j);
        }
    }
    return sum;
}

template<class T>
mtm::Matrix<T> mtm::operator+(const mtm::Matrix<T> &matrix, T data) {
    mtm::Dimensions dims(matrix.height(),matrix.width());
    mtm::Matrix<T> sum(dims);
    int i=0,j=0;
    for (i=0;i <matrix.height() ; i++) {
        for (j=0; j< matrix.width() ; j++) {
            sum(i,j)=matrix(i,j) + data;
        }
    }
    return sum;
}

#endif //HW3_MATRIX_H
