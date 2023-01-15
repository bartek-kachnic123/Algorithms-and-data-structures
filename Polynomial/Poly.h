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
        Poly(const T* factors, int _size);

        // destructor
        ~Poly();

        Poly(const Poly& poly);
        Poly(Poly&& poly);
        
        // methods
        T Horner(T x);
        void clear();
        bool is_zero() const;

        // operators 2 args
        Poly<T> operator+(const Poly<T>& poly) const;
        Poly<T> operator-(const Poly<T>& poly) const;
        Poly<T> operator*(const Poly<T>& poly) const;
        bool operator==(const Poly<T>& poly) const;
        bool operator!=(const Poly<T>& poly) const;
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
    private:
        Poly(bool empty) {
            if (empty) {
                size = 0;
                factors = nullptr;
            }
            else Poly();
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
Poly<T>::Poly(const T* factors, int _size) :
            size(_size)          
{
    if (size <= 0) {
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
Poly<T> Poly<T>::operator+(const Poly<T>& poly) const {

    Poly<T> new_poly(true);
    
    int diff_size = std::abs(size - poly.size);
    int min_size = std::min(size, poly.size);
    new_poly.factors = new T[std::max(size, poly.size)];
    new_poly.size = std::max(size, poly.size);

    if (size > poly.size) {
        std::copy(factors, factors + size, new_poly.factors);
        for (int i = 0; i < min_size; ++i) {
            new_poly.factors[i + diff_size] += poly[i];
        }
    }
    else {
        std::copy(poly.factors, poly.factors + poly.size, new_poly.factors);
        for (int i = 0; i < min_size; ++i) {
            new_poly.factors[i + diff_size] += factors[i];
        }
    }

    return new_poly;
}

template<typename T>
Poly<T> Poly<T>::operator-(const Poly<T>& poly) const {

    Poly<T> new_poly(true);

    int diff_size = std::abs(size - poly.size);
    int min_size = std::min(size, poly.size);

    if (size == poly.size) {

        int i;
        for(i=0; i < min_size - 1; ++i) {
            if (factors[i] - poly[i] != T())
                break;
        }

        new_poly.factors = new T[min_size - i];
        new_poly.size = min_size - i;
        assert(new_poly.factors != nullptr);

        for (int j = 0; j < min_size - i; ++j)
            new_poly.factors[j] = factors[j+i] - poly[j+i];

        return new_poly;
    }
    else if (size > poly.size) {

        new_poly.factors = new T[size];
        new_poly.size = size;
        assert(new_poly.factors!=nullptr);

        std::copy(factors, factors + size, new_poly.factors);
        for (int i = 0; i < min_size; ++i) 
            new_poly.factors[i + diff_size] -= poly[i];
        
    }
    else {
        new_poly.factors = new T[poly.size];
        new_poly.size = poly.size;

        assert(new_poly.factors != nullptr);

        for (int i = 0; i < poly.size; ++i) {
            if (i < diff_size)
                new_poly.factors[i] = (-poly[i]);
            else new_poly.factors[i] = factors[i-diff_size] - poly[i];
        }
    }
        

    return new_poly;


}

template<typename T>
Poly<T> Poly<T>::operator*(const Poly<T>& poly) const {
    
    Poly<T> new_poly(true);
    new_poly.size = size + poly.size - 1;
    new_poly.factors = new T[new_poly.size];
    assert(new_poly.factors!=nullptr);

    std::fill(new_poly.factors, new_poly.factors + new_poly.size, T());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < poly.size; ++j) {
            new_poly.factors[i+j] += factors[i] * poly.factors[j];
        }
    }
    return new_poly;
}

template<typename T>
bool Poly<T>::operator==(const Poly<T>& poly) const {
    Poly<T> diff_poly = *this - poly;
    return diff_poly.is_zero();
}

template<typename T>
bool Poly<T>::operator!=(const Poly<T>& poly) const{
    Poly<T> diff_poly = *this - poly;
    return !(diff_poly.is_zero());
}



template<typename T>
Poly<T>& Poly<T>::operator=(const Poly<T>& poly){

    if (this == &poly) return *this;

    clear();
    factors = new T[poly.size];
    assert(factors!=nullptr);

    size = poly.size;
    std::copy(poly.factors, poly.factors+size, factors);
}





template<typename T>
T& Poly<T>::operator[](int index) const {
    assert(-1 < index  && index < size);
    return factors[index];
}

#endif