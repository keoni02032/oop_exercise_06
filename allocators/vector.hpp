#ifndef MY_VECTOR_HPP_
#define MY_VECTOR_HPP_ 1

#include <memory>
#include <iterator>
#include <utility>

namespace containers {

    template <class T>
    struct vector {

    public:
        using value_type = T;
        using iterator = T*;

        iterator begin() const;
        iterator end() const;
        vector() : data(std::move(std::unique_ptr<T[]>(new T[1]))), size(0), allocated(1) {};
        vector(int size) : data(std::move(std::unique_ptr<T[]>(new T[size]))), size(0), allocated(size) {};

        T& operator[] (int posision);
        void PushBack(const T& value);
        void erase(iterator pos);
        void resize(int NewSize);
        int GetSize();
        ~vector() {};

    private:
        std::unique_ptr<T[]> data;
        int size;
        int allocated;
    };

    template <class T>
    T& vector<T>::operator[] (int posision) {
        if (posision >= size) {
            throw std::logic_error("ERROR");
        }
        return data[posision];
    }

    template <class T>
    void vector<T>::PushBack(const T& value) {
        if (allocated == size) {
            resize(size + 1);
        }
        data[size + 1] = value;
    }

    template <class T>
    void vector<T>::erase(typename vector<T>::iterator it) {
        for (int i = 0; i < size; ++i) {
            if (&data[i] == it) {
                for (int j = i; j < size - 1; ++j) {
                    data[j] = data[j + 1];
                }
                resize(size - 1);
                allocated -= 1;
                return;
            }
        }
        throw std::logic_error("ERROR");
    }

    template <class T>
    void vector<T>::resize(int NewSize) {
        if (size == NewSize) {
            return;
        }
        
        std::unique_ptr<T[]> result = std::unique_ptr<T[]>(new T[NewSize]);

        for (int i = 0; i < NewSize; ++i) {
            result[i] = data[i];
        }
        
        size = NewSize;
        data = std::move(result);
    }

    template <class T>
    int vector<T>::GetSize() {
        return size;
    }

    template <class T>
    typename vector<T>::iterator vector<T>::begin() const {
        return &data[0];
    }

    template <class T>
    typename vector<T>::iterator vector<T>::end() const {
        return &data[size];
    }

}

#endif //MY_VECTOR_HPP_