//#include "MyQueue.hpp"
#include <iostream>
#include<cstdint>

#define out(x, y) std::cout<<x<<' '<<y<<'\n';


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
        int64_t frontPointer;//首指针
        //尾指针
        int64_t tailPoint;
        T *data;

        //没注意到指针是无符号的。。赋值了-1
    public:
        ArrayLoopQueue(uint32_t capa) : capacity{capa}, data{new T[capacity]},
                                        frontPointer{0}, tailPoint{-1} {}

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


}

void test() {
    using namespace MyQueue;
    using namespace std;
    int n;
    ArrayLoopQueue<int> q(10110);
    cin >> n;
    while (n--) {
        int x, y;
        cin >> x;
        switch (x) {
            case 1: {
                cin >> y;
                q.Push(y);
                break;
            }
            case 2: {
                if (q.IsEmpty()) {
                    std::cout << "ERR_CANNOT_POP" << std::endl;

                } else q.Pop();
                break;
            }
            case 3: {
                if (q.IsEmpty()) {
                    cout << "ERR_CANNOT_QUERY" << std::endl;
                } else cout << q.Front() << endl;
                break;
            }
            case 4: {
                cout << q.Size() << endl;
                break;
            }
            default: {
            }
        }

       // std::cout << "SIZE:" << q.Size() << endl;
    }
}

int main() {
    test();
}
/*
 *
 */