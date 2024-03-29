
#ifndef MYDATASTRUCTUREANDALGORITHM_MYSTACK_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYSTACK_HPP

#include <stdexcept>
#include <cstdint>
#include "MyLinkedList.hpp"

namespace MyStack {
    //抽象基类，至少包含一个纯虚函数
    template<typename U>
    class AbstractStack {
    public:
        uint32_t size;//表示当前栈中元素的数量。
    protected://防止被用户实例化
        AbstractStack() : size{0} {}

    public:
        //禁止派生类重写该函数
        bool IsEmpty() const {
            return size == 0;
        };

        uint32_t Size() const {
            return size;
        }

        virtual void Pop() = 0;

        virtual const U &Top() const = 0;

        virtual void Push(const U &value) = 0;
    };

    template<typename T>
    class ArrayStack final : public AbstractStack<T> {

    private:
        //表示栈的最大容量，即能容纳元素的最大数量,也可以理解为数组的最大容量。
        const uint32_t capacity;
        T *data;//一个动态分配的数组，用于存储栈中的元素。

    public:
        //  根据传入的参数初始化栈，创建一个容量为capa的数组。
        ArrayStack(uint32_t capa) : capacity{capa}, data{new T[capacity]} {}

        // 在栈对象生命周期结束时调用，负责释放之前动态分配的数组内存。
        ~ArrayStack() {
            delete[]data;
        }

        /*
         * 防止拷贝构造和赋值操作发生，这是因为栈内部管理了动态内存，直接拷贝可能导致资源泄露或逻辑错误。
         */
        /*
         * 引用乱了。。。研究下
         */
        ArrayStack(const ArrayStack &) = delete;

        ArrayStack(const ArrayStack &&) = delete;

        ArrayStack &operator=(const ArrayStack &) = delete;

    public:

        bool IsFull() const {
            return AbstractStack<T>::size < capacity;
        }

        const T &Top() const override {
            if (AbstractStack<T>::IsEmpty()) {
                throw std::out_of_range("Stack is empty!");
            } else {
                return data[AbstractStack<T>::size - 1];
            }
        }

        void Push(const T &value) override {
            if (!IsFull()) {
                throw std::runtime_error("Stack overflow: Cannot push into a full stack.");
            } else {
                data[AbstractStack<T>::size++] = value;
            }
        }

        void Pop() override {
            if (AbstractStack<T>::IsEmpty()) {
                throw std::out_of_range("Stack is empty!");
            } else {
                --AbstractStack<T>::size;
            }
        }

    };

    template<typename T>
    class LinkedStack : public AbstractStack<T> {
    private:
        MyLinkedList::DoubleLinkedList<T> data;
    public:
        void Push(const T &value) override;


        void Pop() override;

        const T &Top() const override;
    };
}// MyStack

namespace MyStack {
    template<typename T>
    void LinkedStack<T>::Push(const T &value) {
        data.InsertLast(value);
        ++AbstractStack<T>::size;

    }

    template<typename T>
    void LinkedStack<T>::Pop() {
        if (data.Size()) {
            throw std::out_of_range("Stack is empty!");
        } else {
            data.RemoveLast();
            --AbstractStack<T>::size;
        }
    }

    template<typename T>
    const T& LinkedStack<T>::Top() const {
        return data.GetTail();

    }
}

#endif
