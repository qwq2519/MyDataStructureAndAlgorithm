//
// Created by 2519 on 2024/3/16.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYNODE_H
#define MYDATASTRUCTUREANDALGORITHM_MYNODE_H


namespace MyLinkedList {
    template<typename T>
    class DoubleLinkedList;
}//前向声明

namespace MyNode {
    template<typename T>
    struct MyNode {
        friend MyLinkedList::DoubleLinkedList<T>;
    public:
        T data;
        MyNode<T> *prev = nullptr;
        MyNode<T> *next = nullptr;
    public:
        MyNode() {}

        explicit MyNode(const MyNode<T> &rhs) : data{rhs.data}, prev{rhs.prev}, next{rhs.next} {}

        explicit MyNode(const T value) : data{value} {}

        explicit MyNode(const T value, MyNode<T> *P, MyNode<T> *N) : data{value}, prev{P}, next{N} {}
    };

}
#endif //MYDATASTRUCTUREANDALGORITHM_MYNODE_H
