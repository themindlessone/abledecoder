#ifndef ABLEDECODER_ARRAY_H
#define ABLEDECODER_ARRAY_H


#include <cstddef>
#include <cstdint>
#include <stdexcept>

template<class T> class Array {

public:
    Array() {
        this->head = nullptr;
        this->view = nullptr;
        this->size = 0;
    }

    explicit Array(const size_t size) {
        this->head = new T[size];
        this->view = this->head;
        this->size = size;
    }

    inline void allocate(const size_t size) {
        delete[] this->head;

        this->head = new T[size];
        this->view = this->head;
        this->size = size;
    }

    Array(const Array &byteArray) = delete;

    Array(Array &&byteArray) = delete;

    Array &operator=(const Array &byteArray) = delete;

    Array &operator=(Array &&byteArray) = delete;

    ~Array() {
        delete[] this->head;
    }

    inline const T &operator[](size_t at) const {
        return this->view[at];
    }

    inline T &operator[](size_t at) {
        return this->view[at];
    }

    inline size_t getSize() const {
        return this->size;
    }

    inline void setView(size_t begin, size_t end) {
        this->view = &this->view[begin];
        this->size = end - begin;
    }

private:
    T *head;

    T *view;

    size_t size;
};


#endif //ABLEDECODER_ARRAY_H
