
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

        uint32_t capacity;//表示栈的最大容量，即能容纳元素的最大数量。
        uint32_t size;//表示当前栈中元素的数量。
        T *data;//一个动态分配的数组，用于存储栈中的元素。

    public:
        /*
         *  根据传入的参数初始化栈，创建一个容量为capa的数组，并将size设为0。
         */
        FixedSizeStack(uint32_t capa) : capacity(capa), size(0), data(new T[capacity]) {};

        /*
        * 在栈对象生命周期结束时调用，负责释放之前动态分配的数组内存。
        */
        ~FixedSizeStack() {
            delete[]data;
        }
        /*
         * 防止拷贝构造和赋值操作发生，这是因为栈内部管理了动态内存，直接拷贝可能导致资源泄露或逻辑错误。
         */
        FixedSizeStack(const FixedSizeStack &) = delete;
        FixedSizeStack(const FixedSizeStack &&) = delete;
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
