
#ifndef MYDATASTRUCTUREANDALGORITHM_MYQUEUE_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYQUEUE_HPP

#include <stdexcept>
#include <cstdint>
#include "MyLinkedList.hpp"

namespace MyQueue {
    template<typename U>
    class AbstractQueue {
    public:
        uint32_t size;
    protected:
        AbstractQueue() : size{0} {}

        ~AbstractQueue() {}

    public:
        bool IsEmpty() const {
            return size == 0;
        }

        uint32_t Size() const {
            return size;
        }

        virtual void Pop() = 0;

        virtual void Push(const U &) = 0;

        virtual const U &Front() const = 0;


    };

    template<typename T>
    class ArrayLoopQueue final : public AbstractQueue<T> {

    private:
        const uint32_t capacity;
        int64_t frontPointer{0};//首指针
        int64_t tailPoint{-1};//尾指针 便于判断队列为空
        T *data;

        //没注意到指针是无符号的。。赋值了-1
    public:
        ArrayLoopQueue(uint32_t capa) : capacity{capa}, data{new T[capacity]} {}

        ~ArrayLoopQueue() {
            delete[]data;
        }

        bool IsFull() const {
            return AbstractQueue<T>::size >= capacity;
        }

        const T &Front() const override {
            if (AbstractQueue<T>::IsEmpty()) {
                throw std::out_of_range("Queue is empty!");
            } else {
                return data[frontPointer];
            }
        }


        void Pop() override {
            if (AbstractQueue<T>::IsEmpty()) {
                throw std::out_of_range("Queue is empty!");
            } else {
                --AbstractQueue<T>::size;
                ++frontPointer;
                if (frontPointer == capacity) {
                    frontPointer = 0;
                }
            }
        }

        void Push(const T &value) override {
            if (IsFull()) {
                throw std::runtime_error("Queue overflow: Cannot push into a full queue.");
            } else {
                ++AbstractQueue<T>::size;
                ++tailPoint;
                if (tailPoint == capacity) {
                    tailPoint = 0;
                }
                data[tailPoint] = value;
            }
        }

    };

    template<typename T>
    class LinkedQueue final : public AbstractQueue<T> {
    private:
        MyLinkedList::DoubleLinkedList<T> data;
    public:
        void Pop() override;

        void Push(const T &) override;

        const T &Front() const override;
    };
}

namespace MyQueue {
    template<typename T>
    void LinkedQueue<T>::Pop() {
        if (AbstractQueue<T>::IsEmpty()) {
            throw std::out_of_range("Queue is empty!");
        } else {
            --AbstractQueue<T>::size;
            data.RemoveFront();
        }
    }

    template<typename T>
    void LinkedQueue<T>::Push(const T &value) {
        ++AbstractQueue<T>::size;
        data.InsertLast(value);
    }

    template<typename T>
    const T & LinkedQueue<T>::Front() const{
        return data.GetHead();
    }
}


#endif //MYDATASTRUCTUREANDALGORITHM_MYQUEUE_HPP
