#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert>
#include <array>

template<typename T>
class Poly {
    T *factors; // factors of x from [x^0, x^1 to x^n]
    int size;

    public:
        // constructors
        Poly();
        Poly(T factors[], int _size);

        // destructor
        ~Poly();

        Poly(Poly& polynomial);
        Poly(Poly&& polynomial);
        
        // methods
        T Horner(T x);
        void clear();
        bool is_zero();

        // operators 2 args
        Poly<T> operator+(const Poly<T>& poly);
        Poly<T> operator-(const Poly<T>& poly);
        Poly<T>& operator*(const Poly<T>& poly);
        bool operator==(const Poly<T>& poly);
        bool operator!=(const Poly<T>& poly);
        Poly<T>& operator=(const Poly<T>& poly);
        Poly<T>& operator=(Poly<T>&& poly);

        // operators 1 args
        T& operator[](int index);

        // friend operators
        friend std::ostream& operator<<(std::ostream& os, const Poly<T>& poly) {
            os << poly.factors[0];
            for (int i = 1; i < poly.size; ++i){
                if (poly.factors[i] <= 0) {
                     os << poly.factors[i] << "x^" << i;
                    }
                else {
                    os << '+' << poly.factors[i] << "x^" << i;
                    }
            }

             return os;
        }

};

template<typename T>
Poly<T>::Poly() :
            size(1)
            
{
    factors = new T[size];
    assert(factors!=nullptr);

    factors[0] = T();
}

template<typename T>
Poly<T>::Poly(T factors[], int _size) :
            size(_size)          
{
    if (size == 0) {
        Poly();
    }
    else {
        this->factors = new T[size];
        assert(this->factors!=nullptr);
        std::copy(factors, factors+size, this->factors);
    }
}

template<typename T> // maybe other type for x?
T Poly<T>::Horner(T x) {

    T result = factors[0];
    for (int i = 1; i < size; ++i) {
        result = result * x + factors[i];
    }

    return result;
}

template<typename T>
Poly<T>::~Poly() {
    clear();
}

template<typename T>
void Poly<T>::clear() {
    delete []factors;
    factors = nullptr;
}

template<typename T>
bool Poly<T>::is_zero() {
    return (size == 1) ? true : false;
}

template<typename T>
T& Poly<T>::operator[](int index) {
    assert(-1 < index < size);
    return factors[index];
}

#endif