
#ifndef MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP

#include<cstdint>
#include<algorithm>
#include<iostream>

namespace MyVector {
    template<typename T>
    class Vector {
    public:
        using value_type = T;
        using iterator = T *;
        using const_iterator=const T*;
    private:
        value_type *data{nullptr};
        uint64_t size{0};
        uint64_t capacity{0};

    public:
        Vector();

        ~Vector();

        Vector(const Vector<T> &rhs);

        Vector<T>& operator=(const Vector<T> &rhs);

        template<typename InputIterator>
        Vector(InputIterator first,InputIterator last);

    public:
        value_type& operator[](uint64_t index) ;

        bool operator==(const Vector &rhs) const;
    public:
        iterator begin(){return data;}
        iterator end(){return data+size;}
        const_iterator begin() const{return data;}
        const_iterator end() const{return data+size;}
    public:
        void PushBack(value_type value);

        void Insert(iterator it, value_type value);

        void PopBack();

        void Erase(iterator it);
    };
}

namespace MyVector {
    template<typename T>
    Vector<T>::Vector() {}

    template<typename T>
    Vector<T>::~Vector() {
        delete[]data;
        data = NULL;
        size = 0;
        capacity = 0;
    }

    //拷贝构造函数
    template<typename T>
    Vector<T>::Vector(const Vector<T> &rhs) {
        size = rhs.size;
        capacity = rhs.capacity;
        data = new value_type[capacity];

        std::copy(rhs.data, rhs.data + rhs.size, data);
    }

    template<typename T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &rhs) {
        if (*this == rhs) return *this;
        size = rhs.size;
        capacity = rhs.capacity;

        delete[]data;

        data = new value_type[rhs.capacity];
        std::copy(rhs.data, rhs.data + rhs.size, data);

        return *this;
    }

    template<typename T>
    Vector<T>::value_type& Vector<T>::operator[](uint64_t index)  {
        if (index >= size) {
            std::cerr << "Index Out Of Range" << std::endl;
        }
        return data[index];
    }

    template<typename T>
    bool Vector<T>::operator==(const Vector<T> &rhs) const {
        if (size != rhs.size) return false;
        for (int64_t i{0}; i < size; ++i) {
            if (data[i] != rhs.data[i]) {
                return false;
            }
        }//后面用foreach改掉
        return true;
    }

    template<typename T>
    void Vector<T>::PushBack(Vector<T>::value_type value) {
        if (!capacity) {
            capacity = 1;
            data = new value_type[1];
        } else if (size + 1 > capacity) {
            capacity *= 2;

            value_type *temp = new value_type[capacity];
            std::copy(data, data + size, temp);
            delete[]data;

            data = new value_type[capacity];
            std::copy(temp, temp + size, data);

            delete[]temp;
        }
        data[size] = value;
        ++size;
    }

    template<typename T>
    void Vector<T>::Insert(Vector<T>::iterator it, Vector<T>::value_type value) {
        int64_t index = std::distance(it, data);
        if (!capacity) {
            capacity = 1;
            data = new value_type[1];
            data[0] = value;
        } else if (size + 1 > capacity) {
            capacity *= 2;
            value_type *temp = new value_type[capacity];
            for (auto i{0}; i < index; ++i) {
                temp[i] = data[i];
            }
            temp[index] = value;
            for (auto i{index}; i < size; ++i) {
                temp[i + 1] = data[i];
            }

            ++size;
            delete[]data;
            data = new value_type[capacity];
            std::copy(temp, temp + size, data);
            delete[]temp;
        } else {
            for (auto i{size - 1}; i >= index; --i) {
                data[i + 1] = data[i];
            }
            data[index] = value;

            ++size;
        }
    }

    template<typename T>
    void Vector<T>::PopBack() {
        if (!size) {
            std::cerr << "Vector is empty!";
        }else --size;
    }

    template<typename T>
    void Vector<T>::Erase(Vector<T>::iterator it) {
        int64_t index=std::distance(it,data);
        for(auto i{index};i<size-1;++i){
            data[i]=data[i+1];
        }
        --size;
    }
}

#endif //MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP
