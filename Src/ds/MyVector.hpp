
#ifndef MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP

#include<cstdint>
#include<algorithm>
#include<iostream>
#include<memory>
#include<utility>

namespace MyVector {
    template<typename T>
    class Vector {
    public:
        using value_type = T;
        using iterator = T *;
        using constIterator = const T *;
    private:
        iterator first{nullptr};
        iterator last{nullptr};
        iterator end{nullptr};


    public:
        Vector() = default;

        explicit Vector(const size_t size);

        Vector(const Vector &other);

        Vector &operator=(const Vector &other);

        Vector(Vector &&other) noexcept;

        Vector &operator=(Vector &&other) noexcept;

        ~Vector() noexcept;

    public:
        T& operator[](const size_t index);

        T& operator[](const size_t index) const;

    public:
        size_t Size() const;

        size_t Capacity() const;

        void Clear();

        void Resize(const size_t newSize);

        void Reserve(const size_t newCapacity);

        void ShrinkToFit();

    public:
        const T& PushBack(value_type &&value);

        const T& PushBack(const value_type &value);

    private:
        void AllocateAndMove(const size_t newCapacity);

        size_t CalculateGrowth(const size_t newSize) const;

        void GrowIfNeeded(const size_t newSize);


    };
}

namespace MyVector {

    template<typename T>
    Vector<T>::Vector(const size_t size) {
        first = new T[size]{};
        end = last = first + size;
    }

    template<typename T>
    Vector<T>::Vector(const Vector &other) {
        first = new T[other.Size()];
        end = last = std::copy(other.first, other.last, first);
    }

    template<typename T>
    typename Vector<T>::Vector& Vector<T>::operator=(const Vector &other) {
        if (&other == this) return *this;
        delete[]first;

        first = new T[other.Size()];
        end = last = std::copy(other.first, other.last, first);
        return *this;
    }

    template<typename T>
    Vector<T>::Vector(Vector &&other) noexcept {
        first = std::exchange(other.first, nullptr);
        last = std::exchange(other.last, nullptr);
        end = std::exchange(other.end, nullptr);
    }

    template<typename T>
    typename Vector<T>::Vector& Vector<T>::operator=(Vector &&other) noexcept {
        delete []first;
        first = std::exchange(other.first, nullptr);
        last = std::exchange(other.last, nullptr);
        end = std::exchange(other.end, nullptr);
        return *this;
    }


    template<typename T>
    Vector<T>::~Vector() noexcept {
        delete[]first;
    }

    template<typename T>
    T& Vector<T>::operator[](const size_t index) {
        return first[index];
    }

    template<typename T>
    T& Vector<T>::operator[](const size_t index) const {
        return first[index];
    }

    template<typename T>
    void Vector<T>::AllocateAndMove(const size_t newCapacity) {
        iterator newFirst = new T[newCapacity];
        last = std::move(first, last, newFirst);
        delete first;
        first = newFirst;
        end = first + newCapacity;
    }

    template<typename T>
    size_t Vector<T>::CalculateGrowth(const size_t newSize) const {
        const size_t grow = Capacity() * 1.5;
        return std::max(grow, newSize);
    }

    template<typename T>
    void Vector<T>::GrowIfNeeded(const size_t newSize) {
        if (newSize <= Capacity()) return;
        AllocateAndMove(CalculateGrowth(newSize));
    }

    template<typename T>
    size_t Vector<T>::Size() const {
        return std::distance(first, last);
    }

    template<typename T>
    size_t Vector<T>::Capacity() const {
        return std::distance(first, end);
    }

    template<typename T>
    const T& Vector<T>::PushBack(value_type &&value) {
        GrowIfNeeded(Size() + 1);
        return *last++ = std::move(value);
    }

    template<typename T>
    const T& Vector<T>::PushBack(const value_type &value) {
        GrowIfNeeded(Size() + 1);
        return *last++ = value;
    }

    template<typename T>
    void Vector<T>::Clear() {
        last = first;
    }

    template<typename T>
    void Vector<T>::Resize(const size_t newSize) {
        Reserve(newSize);
        last = first + newSize;
    }

    template<typename T>
    void Vector<T>::Reserve(const size_t newCapacity) {
        if (newCapacity > Capacity()) {
            AllocateAndMove(newCapacity);
        }
    }

    template<typename T>
    void Vector<T>::ShrinkToFit() {
        if (Capacity() != Size()) {
            AllocateAndMove(Size());
        }
    }
}

#endif //MYDATASTRUCTUREANDALGORITHM_MYVECTOR_HPP
