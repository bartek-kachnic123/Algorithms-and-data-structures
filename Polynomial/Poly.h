#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <array>

template<typename T>
class Poly {
    T *coeffs; // coeffs of x from [x^n, x^(n-1)... x^0]
    int size;

    public:
        // constructors
        Poly();
        Poly(const T* coeffs, int _size);

        // destructor
        ~Poly();

        Poly(const Poly& other);
        Poly(Poly&& other);
        
        // methods
        T Horner(T x);
        void clear();
        bool is_zero() const;

        // operators 2 args
        Poly<T> operator+(const Poly<T>& other) const;
        Poly<T> operator-(const Poly<T>& other) const;
        Poly<T> operator*(const Poly<T>& other) const;
        bool operator==(const Poly<T>& other) const;
        bool operator!=(const Poly<T>& other) const;
        Poly<T>& operator=(const Poly<T>& other);
        Poly<T>& operator=(Poly<T>&& other);

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
                coeffs = nullptr;
            }
            else Poly();
        }


};

template<typename T>
Poly<T>::Poly() :
            size(1)
            
{
    coeffs = new T[size];
    assert(coeffs!=nullptr);

    coeffs[0] = T();
}

template<typename T>
Poly<T>::Poly(const T* coeffs, int _size) :
            size(_size)          
{
    if (size <= 0) {
        Poly();
    }
    else {
        this->coeffs = new T[size];
        assert(this->coeffs!=nullptr);
        std::copy(coeffs, coeffs+size, this->coeffs);
    }
}

template<typename T>
Poly<T>::Poly(const Poly& other) :
            size(other.size)
{
    coeffs = new T[size];
    assert(coeffs!=nullptr);
    std::copy(other.coeffs, other.coeffs+size, coeffs);
}


template<typename T> // maybe other type for x?
T Poly<T>::Horner(T x) {

    T result = coeffs[0];
    for (int i = 1; i < size; ++i) {
        result = result * x + coeffs[i];
    }

    return result;
}

template<typename T>
Poly<T>::~Poly() {
    clear();
}

template<typename T>
void Poly<T>::clear() {
    delete []coeffs;
    coeffs = nullptr;
}

template<typename T>
bool Poly<T>::is_zero() const {
    return (size == 1) ? true : false;
}

template<typename T>
Poly<T> Poly<T>::operator+(const Poly<T>& other) const {

    Poly<T> new_poly(true);
    
    int diff_size = std::abs(size - other.size);
    int min_size = std::min(size, other.size);
    new_poly.coeffs = new T[std::max(size, other.size)];
    new_poly.size = std::max(size, other.size);

    if (size > other.size) {
        std::copy(coeffs, coeffs + size, new_poly.coeffs);
        for (int i = 0; i < min_size; ++i) {
            new_poly.coeffs[i + diff_size] += other[i];
        }
    }
    else {
        std::copy(other.coeffs, other.coeffs + other.size, new_poly.coeffs);
        for (int i = 0; i < min_size; ++i) {
            new_poly.coeffs[i + diff_size] += coeffs[i];
        }
    }

    return new_poly;
}

template<typename T>
Poly<T> Poly<T>::operator-(const Poly<T>& other) const {

    Poly<T> new_poly(true);

    int diff_size = std::abs(size - other.size);
    int min_size = std::min(size, other.size);

    if (size == other.size) {

        int i;
        for(i=0; i < min_size - 1; ++i) {
            if (coeffs[i] - other[i] != T())
                break;
        }

        new_poly.coeffs = new T[min_size - i];
        new_poly.size = min_size - i;
        assert(new_poly.coeffs != nullptr);

        for (int j = 0; j < min_size - i; ++j)
            new_poly.coeffs[j] = coeffs[j+i] - other[j+i];

        return new_poly;
    }
    else if (size > other.size) {

        new_poly.coeffs = new T[size];
        new_poly.size = size;
        assert(new_poly.coeffs!=nullptr);

        std::copy(coeffs, coeffs + size, new_poly.coeffs);
        for (int i = 0; i < min_size; ++i) 
            new_poly.coeffs[i + diff_size] -= other[i];
        
    }
    else {
        new_poly.coeffs = new T[other.size];
        new_poly.size = other.size;

        assert(new_poly.coeffs != nullptr);

        for (int i = 0; i < other.size; ++i) {
            if (i < diff_size)
                new_poly.coeffs[i] = (-other[i]);
            else new_poly.coeffs[i] = coeffs[i-diff_size] - other[i];
        }
    }
        

    return new_poly;


}

template<typename T>
Poly<T> Poly<T>::operator*(const Poly<T>& other) const {
    
    Poly<T> new_poly(true);
    new_poly.size = size + other.size - 1;
    new_poly.coeffs = new T[new_poly.size];
    assert(new_poly.coeffs!=nullptr);

    std::fill(new_poly.coeffs, new_poly.coeffs + new_poly.size, T());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            new_poly.coeffs[i+j] += coeffs[i] * other.coeffs[j];
        }
    }
    return new_poly;
}

template<typename T>
bool Poly<T>::operator==(const Poly<T>& other) const {
    Poly<T> diff_poly = *this - other;
    return diff_poly.is_zero();
}

template<typename T>
bool Poly<T>::operator!=(const Poly<T>& other) const{
    Poly<T> diff_poly = *this - other;
    return !(diff_poly.is_zero());
}



template<typename T>
Poly<T>& Poly<T>::operator=(const Poly<T>& other){

    if (this == &other) return *this;

    clear();
    coeffs = new T[other.size];
    assert(coeffs!=nullptr);

    size = other.size;
    std::copy(other.coeffs, other.coeffs+size, coeffs);
}





template<typename T>
T& Poly<T>::operator[](int index) const {
    assert(-1 < index  && index < size);
    return coeffs[index];
}

#endif