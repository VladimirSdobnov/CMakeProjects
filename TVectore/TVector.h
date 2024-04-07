#pragma once

const int MAX_VECTOR_SIZE = 100000000;
#define EXPANSION 5
#define REDUCTION 5
#include <iostream>
#include <string>
#include <assert.h>

template<class T>
class TVector;
template<class T>
std::istream& operator>>(std::istream& istr, TVector<T>& v);
template<class T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v);

//Iterators

#include <iterator>
template<class T>
class InIterator : public std::iterator<std::input_iterator_tag, T> {
    friend class TVector<T>;
protected:
    T* p;
    InIterator(T* _p) : p(_p) {};
public:
    InIterator& operator=(const InIterator& it) {
        if (this != it) {
            p = it.p;
        }
        return *this;
    }
    bool operator!=(InIterator const& other) const { return p != other.p; }
    bool operator==(InIterator const& other) const { return p == other.p; }
    T& operator*() const { return *p; } //typename Iterator<T>::reference operator*() const;
    InIterator& operator++() { ++p; return *this; }
};

template<class T>
class OutIterator : public std::iterator<std::output_iterator_tag, T> {
    friend class TVector<T>;
protected:
    T* p;
    OutIterator(T* _p) : p(_p) {};
public:
    OutIterator& operator=(const OutIterator& it) {
        if (this != it) {
            p = it.p;
        }
        return *this;
    }
    T& operator*() { return *p; }
    bool operator!=(OutIterator const& other) const { return p != other.p; }
    bool operator==(OutIterator const& other) const { return p == other.p; }
    OutIterator& operator++() { ++p; return *this; }
    OutIterator operator++(int) {
        OutIterator tmp = *this;
        p++;
        return tmp;
    }
};

template <class T>
class ForwardIterator : public OutIterator<T>, 
    public std::iterator<std::forward_iterator_tag, T> {
    friend class TVector<T>;
protected:
    using OutIterator<T>::p;
    ForwardIterator(T* _p) : OutIterator<T>(_p) {};
public:
    ForwardIterator(const ForwardIterator& it) : OutIterator<T>(it.p) {};
    using OutIterator<T>::operator*;
    using OutIterator<T>::operator++;
    using OutIterator<T>::operator==;
    using OutIterator<T>::operator!=;
    
};

template <class T>
class BidirectionalIterator : public ForwardIterator<T>,
    public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class TVector<T>;
    using ForwardIterator<T>::p;
    BidirectionalIterator(T* p) : ForwardIterator<T>(p) {};
public:
    BidirectionalIterator(const BidirectionalIterator& it) : ForwardIterator<T>(it) {};
    using ForwardIterator<T>::operator*;
    using ForwardIterator<T>::operator++;
    using ForwardIterator<T>::operator==;
    using ForwardIterator<T>::operator!=;
    BidirectionalIterator& operator--() { --p; return *this; }
    BidirectionalIterator& operator--(int) {
        BidirectionalIterator tmp(*this);
        p--;
        return tmp;
    }
};

//template<class T>
//class 
//Vector
template<class T>
void swap(TVector<T>& lhs, TVector<T>& rhs) noexcept {
    std::swap(lhs._size, rhs._size);
    std::swap(lhs.pMem, rhs.pMem);
    std::swap(lhs._count, rhs._count);
}
template<class T>
class TVector {
protected:
    int _size;
    T* pMem;
    int _count;
public:
    TVector(int sz = 0, int ct = 0) : _size(sz), _count(ct) {
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = " + std::to_string(MAX_VECTOR_SIZE));
        if (sz < 0)
            throw std::length_error("Vector size cannot be less than zero");
        if (sz == 0) { pMem = nullptr; return; }
        pMem = new T[sz];
    }
    TVector(T* data, int sz) : _size(sz), _count(sz) {
        if (sz > MAX_VECTOR_SIZE)
            throw std::length_error("Vector size cannot be greater than MAX_VECTOR_SIZE = " + std::to_string(MAX_VECTOR_SIZE));
        if (sz < 0)
            throw std::length_error("Vector size cannot be less than zero");
        // ��� ���� ������ ����� ����������
        assert(data != nullptr && "TVector constructor requires non-nullptr argument.");
        pMem = new T[sz];
        // ��� �������� ����� ������������ std-������� � ��������, ��� �� ������ ��� ��� ��� �����������!
        std::copy(data, data + sz, pMem);
    }

    TVector(const TVector& v) : _size(v._size), _count(v._count){
        pMem = new T[v._size];
        std::copy(v.pMem, v.pMem + _count, pMem);
    }

    TVector(TVector&& v) noexcept : _size(0), pMem(nullptr), _count(0) {
        std::swap(v.pMem, pMem);
        std::swap(v._size, _size);
        std::swap(v._count, _count);
    }

    ~TVector() {
        delete[] pMem;
        pMem = nullptr;
    }


    InIterator<T> begin_in() { return InIterator<T>(pMem); }
    InIterator<T> end_in() { return InIterator<T>(pMem + _count); }
    InIterator<T> begin_in() const { return InIterator<const T>(pMem); }
    InIterator<T> end_in() const { return InIterator<const T>(pMem + _count); }

    OutIterator<T> begin_out() { return OutIterator<T>(pMem); }
    OutIterator<T> end_out() { return OutIterator<T>(pMem + _count); }
    OutIterator<T> begin_out() const { return OutIterator<const T>(pMem); }
    OutIterator<T> end_out() const { return OutIterator<const T>(pMem + _count); }

    ForwardIterator<T> begin_forward() { return ForwardIterator<T>(pMem); }
    ForwardIterator<T> end_forward() { return ForwardIterator<T>(pMem + _count); }
    ForwardIterator<T> begin_forward() const { return ForwardIterator<const T>(pMem); }
    ForwardIterator<T> end_forward() const { return ForwardIterator<const T>(pMem + _count); }

    BidirectionalIterator<T> begin() { return BidirectionalIterator<T>(pMem); }
    BidirectionalIterator<T> end() { return BidirectionalIterator<T>(pMem + _count); }
    BidirectionalIterator<T> begin() const { return BidirectionalIterator<const T>(pMem); }
    BidirectionalIterator<T> end() const { return BidirectionalIterator<const T>(pMem + _count); }

    TVector& operator=(const TVector& v) {
        if (this == &v) { return *this; }
        _size = v._size;
        pMem = new T[_size];
        _count = v._count;
        std::copy(v.pMem, v.pMem + _count, pMem);
        return *this;
    }

    TVector& operator=(TVector&& v) noexcept {
        if (this == &v) { return *this; }
        delete[] pMem;
        pMem = nullptr;
        _size = 0;
        _count = 0;
        swap<T>(*this, v);
        return *this;
    }

    int size() const noexcept { return _count; }

    // ����������
    T& operator[](size_t ind) {
        return pMem[ind];
    }
    T& operator[](ForwardIterator<T> it) {
        return *it;
    }
    const T& operator[](ForwardIterator<T> it) const {
        return *it;
    }
    const T& operator[](size_t ind) const {
        return pMem[ind];
    }

    // ���������� � ��������� - �������� � ��� ������� � ��������� ��� ����� ������
    T& at(int ind) {
        if ((ind > _count - 1) || (ind < 0)) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }
    const T& at(int ind) const {
        if ((ind > _count - 1) || (ind < 0)) { throw std::out_of_range("Index out of range"); }
        return pMem[ind];
    }

    // ���������
    bool operator==(const T& elem) const noexcept {
        for (auto i = 0; i != _count; i++) {
            if (pMem[i] != elem) { return false; }
        }
        return true;
    }
    bool operator==(const TVector& v) const noexcept {
        if (_count != v._count) { return false; }
        for (int i = 0; i < _count; i++) { if (pMem[i] != v.pMem[i]) { return false; } }
        return true;
    }
    bool operator!=(const TVector& v) const noexcept {
        return !(*this == v);
    }
    TVector operator+(T val) {
        TVector<T> tmp(*this);
        for (int i = 0; i < _count; i++) {
            tmp[i] = tmp[i] + val;
        }
        return tmp;
    }
    TVector operator-(T val) {
        TVector<T> tmp(*this);
        for (int i = -; i < _count; i++) {
            tmp[i] = tmp[i] - val;
        }
        return tmp;
    }
    TVector operator*(T val) {
        TVector<T> tmp(*this);
        for (int i = 0; i < _count; i++) {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }
    TVector operator+(const TVector& v) {
        TVector<T> tmp(*this);
        for (int i = 0; i < _count; i++) {
            tmp[i] = tmp[i] + v[i];
        }
        return tmp;
    }
    TVector operator-(const TVector& v) {
        TVector<T> tmp(*this);
        for (int i = 0; i < _count; i++) {
            tmp[i] = tmp[i] - v[i];
        }
        return tmp;
    }
    
    void append(const T& elem) {
        if (_count < _size - 1) { pMem[_count] = elem; _count++; }
        else {
            TVector<T> tmp(_size + EXPANSION);
            std::copy(begin_in(), end_in(), tmp.pMem);
            tmp[_count] = elem;
            tmp._count = _count + 1;
            *this = tmp;
        }
    }
    void pop_back() { _count--; }
    void insert(const T& elem, int i) {
        if (_count < _size - 1) {
            InIterator<T> it = begin_in();
            for (int x = _count; x > i; x--) pMem[x] = pMem[x - 1];
            pMem[i] = elem;
            _count++;
        }
        else {
            TVector<T> tmp(_size + EXPANSION);
            tmp._count = _count + 1;
            InIterator<T> it = begin_in();
            for (int x = 0; x < i; x++) ++it;
            std::copy(begin_in(), it, tmp.pMem);
            for (int x = _count; x > i; x--) tmp.pMem[x] = pMem[x - 1];
            tmp.pMem[i] = elem;
            *this = tmp;
        }
    }
    void erase(int i) {
		if (i < 0 || i >= _count) { throw std::out_of_range("Index out of range"); }
        if (i == _count - 1) { pop_back(); }
        InIterator<T> it = begin_in();
        for (int x = 0; x < i; x++) { ++it; }
		std::copy(begin_in(), it,pMem);
        ++it;
		std::copy(it, end_in(), pMem + i);
        _count--;
    }

    friend void swap <T>(TVector& lhs, TVector& rhs) noexcept;

    // ����/�����
    friend std::istream& operator>> <T>(std::istream& istr, TVector& v);
    friend std::ostream& operator<< <T>(std::ostream& ostr, const TVector& v);
};



// ����/�����
template<class T>
std::istream& operator>>(std::istream& istr, TVector<T>& v) {
    for (size_t i = 0; i < v._size; i++)
        istr >> v[i];
    return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TVector<T>& v) {
    for (size_t i = 0; i < v._count; i++) {
        ostr << v.pMem[i] << ' ';
    }
    return ostr;
}

template<class T>
void fill(ForwardIterator<T> first, ForwardIterator<T> last, const T& val) {
    for (auto elem = first; elem != last; elem++) {
        *elem = val;
    }
}

template<class T>
size_t count(ForwardIterator<T> begin, ForwardIterator<T> end, const T& elem) {
    size_t count = 0;
    while (begin != end) {
        if (*begin == elem) count++;
        begin++;
    }
    return count;
}

template <class T>
ForwardIterator<T>* find(ForwardIterator<T> begin, ForwardIterator<T> end, const T& elem) {
    while (begin != end) {
        if (*begin == elem) return &begin;
        begin++;
    }
    return nullptr;
}

template <class T>
int* find_pos(ForwardIterator<T> begin, ForwardIterator<T> end, const T& elem) {
    int tmp = 0;
    while (begin != end) {
        if (*begin == elem) return &tmp;
        tmp++;
        begin++;
    }
    return nullptr;
}

template<class T>
int BinarSearchPos(TVector<T> data, const T& elem) {
    int left = 0;
    int right = data.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = (left + right) * 0.5;
        if (elem == data[mid]) return mid;
        if (elem > data[mid]) left = mid + 1;
        else if (elem < data[mid]) right = mid - 1;
    }
    return mid;
}