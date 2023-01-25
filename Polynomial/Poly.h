#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

template<typename T>
class Poly {
    T *coeffs; // coeffs of x from [x^n, x^(n-1)... x^0]
    int size;

    public:
        // constructors
        Poly();
        Poly(const T* coeffs, unsigned int _size);
        Poly(std::map<unsigned int, T> &coeffsMap);

        // destructor
        ~Poly();

        Poly(const Poly& other);
        Poly(Poly&& other);
        
        // methods
        T calcValue(T x);
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

            if (poly.size == 1) {
                os << poly.coeffs[0];
                return os;
            }

            int x_power = poly.size;
            for (int i = 0; i < poly.size; ++i){

                --x_power;

                if (poly.coeffs[i] == T()) {
                    continue;
                }

                if (poly.coeffs[i] > 0 && i > 0) 
                    os << '+';
                    
                if (poly.coeffs[i] != T(1) || i == poly.size-1)
                    os << poly.coeffs[i];

                if (x_power == 0)
                    continue;
                else if (x_power == 1) 
                    os << "x";
                else os << "x^" << x_power;

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
Poly<T>::Poly()
{
    size = 1;
    coeffs = new T[size];
    assert(coeffs!=nullptr);

    coeffs[0] = T();
}

template<typename T>
Poly<T>::Poly(const T* coeffs, unsigned int _size) :
            size(_size)          
{
    if (size == 0) {
        Poly();
    }
    else {
        this->coeffs = new T[size];
        assert(this->coeffs!=nullptr);
        std::copy(coeffs, coeffs+size, this->coeffs);
    }
}

template<typename T>
Poly<T>::Poly(std::map<unsigned int, T> &coeffsMap){
    if (coeffsMap.empty())
        Poly();
    else {

        int xPower = (--coeffsMap.end())->first; //map is sorted
        size = xPower + 1;

        this->coeffs = new T[size];
        assert(this->coeffs!=nullptr);

        std::fill(this->coeffs, this->coeffs+size, T());
        for (auto it = coeffsMap.begin(); it != coeffsMap.end(); ++it) {
            (*this)[it->first] = it->second;  // [] operator

        }
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

template<typename T> // move constructor
Poly<T>::Poly(Poly<T>&& other){

    coeffs = other.coeffs;
    size = other.size;

    other.coeffs = nullptr;
    other.size = 0;
}

template<typename T>
Poly<T>::~Poly() {
    if (coeffs != nullptr)
    {
        delete []coeffs;
    }
}

template<typename T> 
T Poly<T>::calcValue(T x) {

    T result = coeffs[0];
    for (int i = 1; i < size; ++i) {
        result = result * x + coeffs[i];
    }

    return result;
}



template<typename T>
void Poly<T>::clear() {
    if (coeffs != nullptr) {
        delete []coeffs;
        coeffs = nullptr;
    }

    size = 1;
    coeffs = new T[size];
    assert(coeffs!=nullptr);
    coeffs[0] = T();
}

template<typename T>
bool Poly<T>::is_zero() const {
    for (int i = 0; i < size; ++i) 
        if (coeffs[i] != T()) 
            return false;
    return true;
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

        int i; // count start
        for(i=0; i < min_size - 1; ++i) {
            if (coeffs[i] - other.coeffs[i] != T())
                break;
        }

        new_poly.coeffs = new T[min_size - i];
        new_poly.size = min_size - i;
        assert(new_poly.coeffs != nullptr);

        for (int j = 0; j < min_size - i; ++j)
            new_poly.coeffs[j] = coeffs[j+i] - other.coeffs[j+i];

    }
    else if (size > other.size) {

        new_poly.coeffs = new T[size];
        new_poly.size = size;
        assert(new_poly.coeffs!=nullptr);

        std::copy(coeffs, coeffs + size, new_poly.coeffs);
        for (int i = 0; i < min_size; ++i) 
            new_poly.coeffs[i + diff_size] -= other.coeffs[i];
        
    }
    else {
        new_poly.coeffs = new T[other.size];
        new_poly.size = other.size;

        assert(new_poly.coeffs != nullptr);

        for (int i = 0; i < other.size; ++i) {
            if (i < diff_size)
                new_poly.coeffs[i] = (-other.coeffs[i]);
            else new_poly.coeffs[i] = coeffs[i-diff_size] - other.coeffs[i];
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

    delete [] coeffs;
    coeffs = new T[other.size];
    assert(coeffs!=nullptr);

    size = other.size;
    std::copy(other.coeffs, other.coeffs+size, coeffs);
}

template<typename T>
Poly<T>& Poly<T>::operator=(Poly<T>&& other){
    if (this == &other) return *this;
    if (coeffs != nullptr)
        delete[] coeffs;

    coeffs = std::move(other.coeffs);
    size = other.size;
    other.coeffs = nullptr;
    other.size = 0;
    
    return *this;
}


template<typename T>
T& Poly<T>::operator[](int index) const {
    assert(-1 < index  && index < size);
    return coeffs[size - index - 1];
}

#endif