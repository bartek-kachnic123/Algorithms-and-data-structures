#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert>

template<typename T>
class Poly {
    T *factors; // factors of x from [x^0, x^1 to x^n]

    public:
        // constructors
        Poly();
        Poly(T.. args);
        Poly(T factors[]);
        // destructor
        ~Poly();

        Poly(Poly& polynomial);
        Poly(Poly&& polynomial);
        
        // methods
        T Horner();
        void clear();
        bool is_zero();

        // operators 2 args
        Poly operator+(const Poly& polynomial);
        Poly operator-(const Poly& polynomial);
        Poly& operator*(const Poly& polynomial);
        bool operator==(const Poly& polynomial);
        bool operator!=(const Poly& polynomial);
        Poly& operator=(const Poly& polynomial);
        Poly& operator=(Poly&& polynomial);

        // operators 1 args
        T& operator[]();

        // friend operators
        friend std::ostream& operator<<(std::ostream& os, Poly& polynomial);

};

#endif