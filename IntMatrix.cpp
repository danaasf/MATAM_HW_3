//
// Created by danaa on 6/24/2020.
//
#include <iostream>
#include "IntMatrix.h"

mtm::IntMatrix::IntMatrix(const mtm::Dimensions &dims, int data):
    row(dims.getRow()), col(dims.getCol()), element(new int *[dims.getRow()]) {
    int i=0,j=0;
    for (i=0 ; i<row ; i++) {
        element[i]= new int[col];
    }
    for (i=0; i<row; i++){
        for (j=0; j<col; j++){
            element[i][j]=data;
        }
    }
}

mtm::IntMatrix::~IntMatrix() {
    int i=0;
    for (i=0; i < this->height(); i++)
    {
        delete[] element[i];
    }
    delete[] element;
}

mtm::IntMatrix::IntMatrix(const IntMatrix& matrix): row(matrix.height()), col(matrix.width()), element(new int *[matrix.height()]){
    int i=0,j=0;
    for (i=0 ; i<row ; i++ ) {
        element[i]= new int[col];
    }
    for (i=0 ; i< row ; i++){
        for (j=0 ; j< col ; j++){
            element[i][j]=matrix.element[i][j];
        }
    }
}

mtm::IntMatrix mtm::IntMatrix::operator=(const IntMatrix& matrix){
    if (this== &matrix)
    {
        return *this;
    }
    int i=0;
    for (i=0 ; i<row ; i++){
        delete[] element[i];
    }
    delete[] element;
    row=matrix.row;
    col=matrix.col;
    element=new int *[row];
    for (i=0 ; i< matrix.row ; i++) {
        element[i]= new int[col];
    }
    int j=0;
    for (int i=0; i<row; i++){
        for (j=0 ; j<col ; j++){
            element[i][j]=matrix.element[i][j];
        }
    }
    return *this;
}
 mtm::IntMatrix mtm::IntMatrix::Identity(const int dim) {
    mtm::Dimensions dims(dim,dim);
    mtm::IntMatrix matrix(dims);
    int i=0, j=0;
    for (i=0 ; i< dim ; i++){
        for (j=0 ; j<dim ; j++){
            matrix.element[i][i]=1;
        }
    }
    return matrix;
}

int mtm::IntMatrix::height() const {
    return this->row;
}

int mtm::IntMatrix::width() const {
    return this->col;
}
int mtm::IntMatrix::size() const{
    return (this->row)*(this->col);
}

mtm::IntMatrix mtm::IntMatrix::transpose() const {
    mtm::Dimensions dims(this->col,this->row);
    mtm::IntMatrix matrix(dims);
    int i=0,j=0;
    for (i=0; i<dims.getRow() ; i++){
        for (j=0; j< dims.getCol() ; j++){
            matrix.element[i][j]=this->element[j][i];
        }
    }
    return matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator+ (const IntMatrix& matrix) const {
    Dimensions dims(matrix.row,matrix.col);
    IntMatrix result(dims);
    int i=0,j=0;
    for (i=0; i<this->row; i++){
        for (j=0 ; j< this->col ; j++)
        {
            result.element[i][j]=matrix.element[i][j]+this->element[i][j];
        }
    }
    return result;
}

mtm::IntMatrix mtm::IntMatrix::operator- () const {
    mtm::Dimensions dims(this->row,this->col);
    mtm::IntMatrix negative(dims);
    int i=0,j=0;
    for(i=0; i< this->row ; i++){
        for (j=0 ; j <this->col ; j++){
            negative.element[i][j]=-(this->element[i][j]);
        }
    }
    return negative;
}

mtm::IntMatrix mtm::IntMatrix::operator- (const IntMatrix& matrix ) const {
    mtm::Dimensions dims(this->row,this->col);
    mtm::IntMatrix result(dims);
    int i=0,j=0;
    for(i=0; i< this->row ; i++){
        for (j=0 ; j <this->col ; j++){
            result.element[i][j]= element[i][j]+ -(matrix.element[i][j]);
        }
    }
    return result;
}
mtm::IntMatrix& mtm::IntMatrix::operator+=(const int argument){
    int i=0,j=0;
    for(i=0 ; i< row;i++){
        for (j=0 ; j<col ; j++)
        {
            element[i][j]=element[i][j]+argument;
        }
    }
    return *this;
}


mtm::IntMatrix mtm::operator+( int argument , mtm::IntMatrix matrix ) {
    int i=0,j=0;
    for (i=0 ; i<matrix.height() ;i++) {
        for (j=0 ; j<matrix.width() ; j++){
            matrix(i,j)+=argument;
        }
    }
    return matrix;
}

mtm::IntMatrix mtm::operator+( mtm::IntMatrix matrix, int argument ) {
    int i=0,j=0;
    for (i=0 ; i<matrix.height() ;i++) {
        for (j=0 ; j<matrix.width() ; j++){
            matrix(i,j)+=argument;
        }
    }
    return matrix;
}


std::ostream &mtm::operator<< (std::ostream& os, const mtm::IntMatrix &matrix) {
    mtm::Dimensions dims(matrix.height(),matrix.width());
    int *matrix_val=new int[matrix.size()];
    int i=0,j=0,k=0;
    for (i=0 ; i<matrix.height() ; i++){
        for (j=0; j< matrix.width() ; j++){
            matrix_val[k]=matrix(i,j);
            k++;
        }
    }
    os << mtm::printMatrix(matrix_val,dims);
    delete[] matrix_val;
    return os;
}

int &mtm::IntMatrix::operator()(const int row ,const int col){
        return this->element[row][col];
}


const int mtm::IntMatrix::operator()(const int row , const int col)const {
        return this->element[row][col];
}

mtm::IntMatrix mtm::IntMatrix::operator< (const int argument) {
    Dimensions dims(this->row,this->col);
    IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]< argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator> (const int argument) {
    Dimensions dims(this->row,this->col);
    IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]> argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}
mtm::IntMatrix mtm::IntMatrix::operator<= (const int argument) {
    Dimensions dims(this->row,this->col);
    IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]<= argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator>= (const int argument) {
    Dimensions dims(this->row,this->col);
    IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]>= argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}

mtm::IntMatrix mtm::IntMatrix::operator== (const int argument) {
    mtm::Dimensions dims(this->row,this->col);
    mtm::IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]== argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}


mtm::IntMatrix mtm::IntMatrix::operator!= (const int argument) {
    Dimensions dims(this->row,this->col);
    IntMatrix matrix (dims);
    int i=0,j=0;
    for(i=0; i<this->row ; i++){
        for(j=0; j<this->col ; j++){
            if (this->element[i][j]!= argument){
                matrix.element[i][j]=1;
            }
        }
    }
    return matrix;
}

mtm::IntMatrix::iterator mtm::IntMatrix::begin() {
   return mtm::IntMatrix::iterator(this,0,0);
}

mtm::IntMatrix::iterator mtm::IntMatrix::end() {
    mtm::IntMatrix::iterator last(this,(*this).height(),0);
    return last;
}

bool mtm::IntMatrix::iterator::operator==(const mtm::IntMatrix::iterator &i) const {
    if (i.row== this->row && i.col== this->col) {
        return true;
    }
    return false;
}

bool mtm::IntMatrix::iterator::operator!=(const mtm::IntMatrix::iterator &i) const {
    if (i.row!= this->row || i.col!=this->col) {
        return true;
    }
    return false;
}

mtm::IntMatrix::iterator mtm::IntMatrix::iterator::operator++(int) {
    mtm::IntMatrix::iterator iter(this->matrix,this->row,this->col);
    if (this->col >= (*matrix).width()-1){
        this->row++;
        this->col =0;
    }
    else {
        this-> col++;
    }
    return iter;
}
mtm::IntMatrix::iterator& mtm::IntMatrix::iterator::operator++() {
    if (this->col >= (*matrix).width()-1){
        this->row++;
        this->col=0;
    }
    else {
        this->col++;
    }
    return *this;
}

mtm::IntMatrix::iterator mtm::IntMatrix::iterator::operator=(const mtm::IntMatrix::iterator &other) {
    if (this != &other) {
        delete this;
        this->matrix = (other.matrix);
        this->row = other.row;
        this->col = other.col;
    }
    return *this;
}

mtm::IntMatrix::iterator::iterator(const mtm::IntMatrix::iterator &iter) {
    this->matrix=iter.matrix;
    this->row=iter.row;
    this->col=iter.col;
}

int &mtm::IntMatrix::iterator::operator*() const  {
    return (*matrix)(row,col);
}

mtm::IntMatrix::iterator::iterator(mtm::IntMatrix *matrix, int row, int col) : matrix(matrix) , row(row) , col(col) {}

mtm::IntMatrix::const_iterator::const_iterator(const mtm::IntMatrix *matrix, const int c_row, const int c_col)  : matrix(matrix) , c_row(c_row) , c_col(c_col)  {}

mtm::IntMatrix::const_iterator mtm::IntMatrix::begin() const {
    return mtm::IntMatrix::const_iterator(this,0,0);
}

mtm::IntMatrix::const_iterator mtm::IntMatrix::end() const {
    return mtm::IntMatrix::const_iterator(this, (*this).height(), 0);

}

bool mtm::IntMatrix::const_iterator::operator==(const mtm::IntMatrix::const_iterator &i) const {
    if (i.c_col == this->c_col && i.c_row == this->c_row){
    return true;
    }
    return false;
}


bool mtm::IntMatrix::const_iterator::operator!=(const mtm::IntMatrix::const_iterator &i) const {
    if (i.c_col != this->c_col || i.c_row != this->c_row){
        return true;
    }
    return false;
}

int mtm::IntMatrix::const_iterator::operator*() const {
    return  (*matrix)(c_row, c_col);
}


bool mtm::all(mtm::IntMatrix matrix){
    int i=0,j=0;
    for (i=0 ; i< matrix.height() ; i++) {
        for (j=0 ; j<matrix.width() ;j++)
        {
            if (matrix(i,j)== 0) {
                return false;
            }
        }
    }
    return true;

}
bool mtm::any (mtm::IntMatrix matrix) {
    int i = 0, j = 0;
    for (i = 0; i < matrix.height(); i++) {

        for (j = 0; j < matrix.width(); j++) {

            if (matrix(i,j) != 0) {
                return true;
            }
        }
    }
    return false;
}


mtm::IntMatrix::const_iterator mtm::IntMatrix::const_iterator::operator++(int) {
    mtm::IntMatrix::const_iterator iter(this->matrix,c_row,c_col);
    if (c_col >= (*matrix).width()-1){
        c_row++;
        c_col =0;
    }
    else {
        c_col++;
    }
    return iter;
}
mtm::IntMatrix::const_iterator& mtm::IntMatrix::const_iterator::operator++() {
    if (c_col >= (*matrix).width()-1){
        c_row++;
        c_col=0;
    }
    else {
        c_col++;
    }
    return *this;
}

mtm::IntMatrix::const_iterator::const_iterator(const mtm::IntMatrix::const_iterator &const_iter) {
    this->matrix=const_iter.matrix;
    this->c_row=const_iter.c_row;
    this->c_col=const_iter.c_col;
}

mtm::IntMatrix::const_iterator mtm::IntMatrix::const_iterator::operator=(const mtm::IntMatrix::const_iterator &other) {
    if (this != &other) {
        delete this;
        this->matrix = (other.matrix);
        this->c_row = other.c_row;
        this->c_col = other.c_col;
    }
    return *this;
}


