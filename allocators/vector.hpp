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
        void erase(int pos);
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
            resize(size * 2);
        }
        data[size++] = value;
    }

    template<class T>
    void vector<T>::erase(int pos) {
        std::unique_ptr<T[]> newData(new T[allocated]);
        for(int i = 0; i < size; ++i) {
            if(i < pos) {
                newData[i] = data[i];
            } else if(i > pos) {
                newData[i - 1] = data[i];
            }
        }
        data = std::move(newData);
        size--;
    }


    template <class T>
    void vector<T>::resize(int size) {
        std::unique_ptr<T[]> newData(new T[size]);
        int n = std::min(size, this->size);
        for(int i = 0; i < n; ++i) {
            newData[i] = data[i];
        }
        data = std::move(newData);
        this->size = n;
        allocated = size;
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
        return data[size];
    }

}

#endif //MY_VECTOR_HPP_