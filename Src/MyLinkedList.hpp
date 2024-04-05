//
// Created by 2519 on 2024/3/16.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP

#include "MyNode.h"
#include<cstdint>
#include <iostream>


namespace MyLinkedList {
    template<typename T>
    class DoubleLinkedList {
    public:
        using Pointer = MyNode::MyNode<T> *;
        Pointer sentinel;//哨兵节点
        int64_t size;
    public:
        DoubleLinkedList();

        ~DoubleLinkedList();

    public:
        void Insert(int64_t index, T value);

        void InsertFront(T value);

        void InsertLast(T value);

        void Remove(int64_t index);

        void RemoveFront();

        void RemoveLast();

        const T &GetHead() const;


        const T &GetTail() const;

        const T &GetValue(int64_t index) const;
        void ForwardIteration() const;

        void IntervalReverse(int64_t begin,int64_t end);

        void AllReverse();

        void SortByBinaryLifting();

    public:
        bool IsEmpty() const;

        int64_t Size() const;

    private:
        Pointer Get(int64_t index);

    public:
        const T &GetData(int64_t index) const;

    };
}
namespace MyLinkedList {
    template<typename T>
    DoubleLinkedList<T>::DoubleLinkedList() {
        sentinel = new MyNode::MyNode<T>({}, nullptr, nullptr);
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        size = 0;
    }

    template<typename T>
    DoubleLinkedList<T>::~DoubleLinkedList() {
        Pointer pNode = sentinel->next;
        while (pNode != sentinel) {
            Pointer temp = pNode->next;
            delete pNode;
            pNode = temp;
        }
        delete sentinel;
    }

    template<typename T>
    int64_t DoubleLinkedList<T>::Size() const {
        return size;
    }

    template<typename T>
    bool DoubleLinkedList<T>::IsEmpty() const { return size == 0; }

    template<typename T>
    void DoubleLinkedList<T>::InsertFront(T value) {
        Pointer newNode = new MyNode::MyNode<T>(value, sentinel, sentinel->next);
        sentinel->next->prev = newNode;
        sentinel->next = newNode;
        ++size;

    }

    template<typename T>
    void DoubleLinkedList<T>::InsertLast(T value) {
        Pointer newNode = new MyNode::MyNode<T>(value, sentinel->prev, sentinel);
        sentinel->prev->next = newNode;
        sentinel->prev = newNode;
        ++size;
    }

    template<typename T>
    DoubleLinkedList<T>::Pointer DoubleLinkedList<T>::Get(int64_t index) {
        if (index >= size) {
            return nullptr;
        }
        Pointer pNode;
        if (index <= size / 2) {
            pNode = sentinel->next;
            while (index--) {
                pNode = pNode->next;
            }
        } else {
            index = size - index - 1;
            pNode = sentinel->prev;
            while (index--) {
                pNode = pNode->prev;
            }
        }
        return pNode;
    }

//在index位置之前插入
    template<typename T>
    void DoubleLinkedList<T>::Insert(int64_t index, T value) {
        if (index == 0) {
            return InsertFront(value);
        }

        Pointer pNode = Get(index);
        if (pNode == nullptr) {
            std::cerr << "this is a nullptr" << '\n';
            return ;
        }

        Pointer newNode = new MyNode::MyNode<T>(value, pNode->prev, pNode);
        pNode->prev->next = newNode;
        pNode->prev = newNode;
        ++size;
    }

    template<typename T>
    void DoubleLinkedList<T>::RemoveFront() {
        if (!size) {
            std::cerr << "this is a nullptr" << '\n';
            return;
        }
        Pointer pNode = sentinel->next;
        sentinel->next = pNode->next;
        pNode->next->prev = sentinel;
        delete pNode;
        --size;
    }

    template<typename T>
    void DoubleLinkedList<T>::RemoveLast() {
        if (!size) {
            std::cerr << "this is a nullptr" << '\n';
            return;
        }
        Pointer pNode = sentinel->prev;
        pNode->prev->next = sentinel;
        sentinel->prev = pNode->prev;
        delete pNode;
        --size;
    }

    template<typename T>
    void DoubleLinkedList<T>::Remove(int64_t index) {
        if (index == 0) {
            RemoveFront();
            return;
        } else if (index == size - 1) {
            RemoveLast();
        } else if (index >= size) {
            return;
        }

        Pointer pNode = Get(index);
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
        delete pNode;
        --size;
    }

    template<typename T>
    const T &DoubleLinkedList<T>::GetHead() const {
        return sentinel->next->data;
    }

    template<typename T>
    const T &DoubleLinkedList<T>::GetTail() const {
        return sentinel->prev->data;
    }

    template<typename T>
    const T &DoubleLinkedList<T>::GetValue(int64_t index) const {
        return Get(index)->data;
    }

    template<typename T>
    void DoubleLinkedList<T>::ForwardIteration() const {
        for (auto it = sentinel->next; it != sentinel; it = it->next) {
            std::cout << (it->data)<<"("<<it<<") " ;
            if(it->next!=sentinel)
            std::cout<< " -> \n" << ' ';
        }
    }


    template<typename T>
    void DoubleLinkedList<T>::IntervalReverse(int64_t begin, int64_t end) {
        Pointer pNode=Get(begin);
        Pointer eNode=Get(end);

        Pointer PrevpNode=pNode->prev;//区间的前继
        Pointer NexteNode=eNode->next;//区间的后继
        pNode->prev= nullptr;
        eNode->next= nullptr;
        for(auto it=pNode;it!= nullptr;){
            auto temp=it->next;
            it->next=it->prev;
            it->prev=temp;
            it=temp;
        }
        PrevpNode->next=eNode;
        NexteNode->prev=pNode;
        eNode->prev=PrevpNode;
        pNode->next=NexteNode;
    }

    template<typename T>
    void DoubleLinkedList<T>::AllReverse() {
        IntervalReverse(0,Size()-1);
    }


}


#endif //MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP
