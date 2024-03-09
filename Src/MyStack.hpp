
#ifndef MYDATASTRUCTUREANDALGORITHM_MYSTACK_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYSTACK_HPP

#include <exception>
#include <cstdint>

namespace MyStack {
    /*
     capacity --- maximum number of elements stack can hold
     Size --- current size of stack
    */
    template<typename T>
    class FixedSizeStack {
    private:

        uint32_t capacity;
        uint32_t size;
        T *data;

    public:
        FixedSizeStack(uint32_t capa) : capacity(capa), size(0), data(new T[capacity]) {};

        ~FixedSizeStack() {
            delete[]data;
        }

        FixedSizeStack(const FixedSizeStack &) = delete;

        FixedSizeStack &operator=(const FixedSizeStack &) = delete;

    public:

        bool isEmpty() const {
            return size == 0;
        }

        bool isFull() const {
            return size < capacity;
        }

        void pop() {
            if (isEmpty()) {
                throw "Stack is empty!";
            } else {
                --size;
            }
        }

        const T &top() const {
            if (isEmpty()) {
                throw "Stack is empty!";
            } else {
                return data[size - 1];
            }
        }

        void push(const T &value) {
            if (!isFull()) {
                throw "Stack is Full!";
            } else {
                data[size++] = value;
            }
        }

        uint32_t Size() const {
            return size;
        }


    };
}// MyStack

#endif
