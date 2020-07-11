//
// Created by danaa on 6/21/2020.
//

#ifndef HW3_INTMATRIX_H
#define HW3_INTMATRIX_H
#include "Auxiliaries.h"

#include <iostream>

namespace mtm {
    class IntMatrix {
        int row;
        int col;
        int **element;
    public:
        IntMatrix(const Dimensions &dims, int data = 0) ;

        ~IntMatrix();

        IntMatrix(const IntMatrix &matrix);

        IntMatrix operator=(const IntMatrix &matrix);

        static IntMatrix Identity(const int dim);

        int height() const;

        int width() const;

        int size() const;

        IntMatrix transpose()const;

        IntMatrix operator+(const IntMatrix &matrix) const;

        IntMatrix operator-() const;

        IntMatrix operator-(const IntMatrix &matrix) const;

        IntMatrix& operator+=(const int argument);

        friend std::ostream &operator<< (std::ostream& os, const mtm::IntMatrix &matrix);

        int &operator()(int row, const int col);

        const int operator()(const int row, const int col) const;

        IntMatrix operator<(const int argument);

        IntMatrix operator>(const int argument);

        IntMatrix operator<=(const int argument);

        IntMatrix operator>=(const int argument);

        IntMatrix operator==(const int argument) ;

        IntMatrix operator!=(const int argument);

        class iterator {
            IntMatrix *matrix;
            int row;
            int col;
            friend class IntMatrix;
            iterator (IntMatrix *matrix, int row , int col);
        public:
            iterator(const iterator &iter);

            iterator operator=(const iterator &other);

             int &operator*() const;

            iterator operator++(int);

            iterator &operator++();

            bool operator==(const iterator &i) const;

            bool operator!=(const iterator &i) const;

        };

        iterator begin();

        iterator end() ;

        class const_iterator {
            const IntMatrix *matrix;
            int c_row;
            int c_col;
            friend class IntMatrix;
            const_iterator(const IntMatrix *matrix, const int c_row , const int c_col);
        public:

            const_iterator(const const_iterator& const_iter);

             int operator*() const;

            const_iterator operator++(int);

            const_iterator &operator++();

            bool operator==(const const_iterator &i) const;

            bool operator!=(const const_iterator &i) const;

            const_iterator operator=(const const_iterator &other);

        };
        const_iterator begin() const;

        const_iterator end() const;

    };


    IntMatrix operator+(int argument, IntMatrix matrix);

    IntMatrix operator+ (IntMatrix matrix, int argument);

    std::ostream &operator<<(std::ostream &os, const IntMatrix &matrix);

    bool all(IntMatrix matrix);

    bool any(IntMatrix matrix);

}

#endif //HW3_INTMATRIX_H
