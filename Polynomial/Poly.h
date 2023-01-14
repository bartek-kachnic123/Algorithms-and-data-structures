#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <array>

template<typename T>
class Poly {
    T *factors; // factors of x from [x^n, x^(n-1)... x^0]
    int size;

    public:
        // constructors
        Poly();
        Poly(T factors[], int _size);

        // destructor
        ~Poly();

        Poly(const Poly& poly);
        Poly(Poly&& poly);
        
        // methods
        T Horner(T x);
        void clear();
        bool is_zero() const;

        // operators 2 args
        Poly<T> operator+(const Poly<T>& poly);
        Poly<T> operator-(const Poly<T>& poly);
        Poly<T>& operator*(const Poly<T>& poly);
        bool operator==(const Poly<T>& poly);
        bool operator!=(const Poly<T>& poly);
        Poly<T>& operator=(const Poly<T>& poly);
        Poly<T>& operator=(Poly<T>&& poly);

        // operators 1 args
        T& operator[](int index) const;

        // friend operators
        friend std::ostream& operator<<(std::ostream& os, const Poly<T>& poly) {

            if (poly.is_zero() || poly[0] != T(1))
                os << poly[0];

            int x_power = poly.size;
            for (int i = 1; i < poly.size; ++i){

                --x_power;
                if (poly[i] == T())
                    continue;

                os << "x^" << x_power;

                if (poly[i] > 0) 
                    os << '+';
                    
                if (poly[i] != T(1) || i == poly.size-1)
                    os << poly[i];
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

template<typename T>
Poly<T>::Poly(const Poly& poly) :
            size(poly.size)
{
    factors = new T[size];
    assert(factors!=nullptr);
    std::copy(poly.factors, poly.factors+size, factors);
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
bool Poly<T>::is_zero() const {
    return (size == 1) ? true : false;
}

template<typename T>
Poly<T> Poly<T>::operator+(const Poly<T>& poly) {

    int diff_size = std::abs(size - poly.size);
    int min_size = std::min(size, poly.size);
    T* arr = new T[std::max(size, poly.size)];

    if (size > poly.size) {
        std::copy(factors, factors + size, arr);
        for (int i = 0; i < min_size; ++i) {
            arr[i + diff_size] += poly[i];
        }
    }
    else {
        std::copy(poly.factors, poly.factors + poly.size, arr);
        for (int i = 0; i < min_size; ++i) {
            arr[i + diff_size] += factors[i];
        }
    }

    return Poly<T>(arr, std::max(size, poly.size));

}


    




template<typename T>
T& Poly<T>::operator[](int index) const {
    assert(-1 < index  && index < size);
    return factors[index];
}

#endif