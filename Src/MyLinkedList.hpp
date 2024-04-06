//
// Created by 2519 on 2024/3/16.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP

#include "MyNode.h"
#include<cstdint>
#include<vector>
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
        void clear();
        void Insert(int64_t index, T value);

        void InsertFront(T value);

        void InsertLast(T value);

        void Remove(int64_t index);

        void RemoveFront();

        void RemoveLast();

        const T GetHead() const;


        const T GetTail() const;

        const T GetValue(int64_t index) const;

        void ForwardIteration() const;

        void IntervalReverse(int64_t begin, int64_t end);

        void AllReverse();

        void Unique();//去重，需要排序后使用

        static DoubleLinkedList<T> MergeOutPlace(const DoubleLinkedList<T> &a, const DoubleLinkedList<T> &b);

        void SortByBinaryLifting();

    public:
        bool IsEmpty() const;

        int64_t Size() const;

    private:
        Pointer Get(int64_t index) const;

    public:
        DoubleLinkedList<T>& operator =(const DoubleLinkedList<T>& rhs);

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os,const DoubleLinkedList<U> a);

        friend DoubleLinkedList<T> operator+(const DoubleLinkedList<T> &a,const DoubleLinkedList<T> &b);
        friend DoubleLinkedList<T> operator-(const DoubleLinkedList<T> &a,const DoubleLinkedList<T> &b);
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
    void DoubleLinkedList<T>::clear() {
        Pointer pNode = sentinel->next;
        while (pNode != sentinel) {
            Pointer temp = pNode->next;
            delete pNode;
            pNode = temp;
        }
        delete sentinel;
        sentinel = new MyNode::MyNode<T>({}, nullptr, nullptr);
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
        size = 0;
    }

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
    DoubleLinkedList<T>::Pointer DoubleLinkedList<T>::Get(int64_t index) const{
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
            return;
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
    const T DoubleLinkedList<T>::GetHead() const {
        return sentinel->next->data;
    }

    template<typename T>
    const T DoubleLinkedList<T>::GetTail() const {
        return sentinel->prev->data;
    }

    template<typename T>
    const T DoubleLinkedList<T>::GetValue(int64_t index) const {
        return Get(index)->data;
    }

    template<typename T>
    void DoubleLinkedList<T>::ForwardIteration() const {
        for (auto it = sentinel->next; it != sentinel; it = it->next) {
            std::cout << (it->data) ;
            if (it->next != sentinel)
                std::cout << " -> " << ' ';
        }
    }


    template<typename T>
    void DoubleLinkedList<T>::IntervalReverse(int64_t begin, int64_t end) {
        Pointer pNode = Get(begin);
        Pointer eNode = Get(end);

        Pointer PrevpNode = pNode->prev;//区间的前继
        Pointer NexteNode = eNode->next;//区间的后继
        pNode->prev = nullptr;
        eNode->next = nullptr;
        for (auto it = pNode; it != nullptr;) {
            auto temp = it->next;
            it->next = it->prev;
            it->prev = temp;
            it = temp;
        }
        PrevpNode->next = eNode;
        NexteNode->prev = pNode;
        eNode->prev = PrevpNode;
        pNode->next = NexteNode;
    }

    template<typename T>
    void DoubleLinkedList<T>::AllReverse() {
        IntervalReverse(0, Size() - 1);
    }

    template<typename T>
    void DoubleLinkedList<T>::Unique() {
        std::vector<int> a;
        int total=0;
        int index;
        Pointer t=sentinel->next->next;
        index=1;
        while(t!=sentinel){
            if(t->prev->data==t->data){
             ++total;
             a.push_back(index);
            }
            ++index;
            t=t->next;
        }
        for(auto ele:a){
            Remove(ele-total);
            ++total;
        }
    }

    template<typename T>
    DoubleLinkedList<T>
    DoubleLinkedList<T>::MergeOutPlace(const DoubleLinkedList<T> &a, const DoubleLinkedList<T> &b) {
        DoubleLinkedList<T> c;
        Pointer tempa{a.sentinel->next};
        Pointer tempb{b.sentinel->next};

        while (tempa != a.sentinel && tempb != b.sentinel) {
            if (tempa->data <= tempb->data) {
                c.InsertLast(tempa->data);
                tempa  = tempa->next;
            } else {
                c.InsertLast(tempb->data);
                tempb = tempb->next;
            }
          //  std::cout<<"fuck";

        }
        while (tempa != a.sentinel) {
            c.InsertLast(tempa->data);
            tempa = tempa->next;
           // std::cout<<"fuck22";

        }
        while (tempb != b.sentinel) {
            //std::cout<<tempb->data<<'\n';
           // system("pause");
            c.InsertLast(tempb->data);
            tempb = tempb->next;
        }
        return c;
    }
    template<typename T>
    void DoubleLinkedList<T>::SortByBinaryLifting() {
        Pointer head=sentinel->next;
//
//        sentinel->next->prev= nullptr;
//        sentinel->prev->next= nullptr;//变成一条链
        for(int subLength(1);subLength<size;subLength<<=1) {
            for (int H(0);H<size-subLength ;H += subLength*2) {//注意边界，容易记错
                DoubleLinkedList<T> sublsP, sublsN;//一前一后的两条子链
                Pointer Beg(Get(H));
                Pointer p = Beg;
                for (int i = subLength; i; --i) {
                    sublsP.InsertLast(p->data);
                    p = p->next;
                }
                for (int i = subLength; i && p != sentinel; --i) {
                    sublsN.InsertLast(p->data);
                    p = p->next;
                }
              //  std::cout << sublsP << '\n';
               // std::cout << sublsN << '\n';
                auto temp = MyLinkedList::DoubleLinkedList<int>::MergeOutPlace(sublsP, sublsN);
                Pointer TP = temp.sentinel->next;
                p = Beg;
                while (TP != temp.sentinel) {
                    p->data = TP->data;
                    p = p->next;
                    TP = TP->next;
                }
            }
        }
    }
    template<typename T>
     std::ostream& operator<<(std::ostream& os,const DoubleLinkedList<T> a){
        a.ForwardIteration();
        return os;
     }
    template<typename T>
    DoubleLinkedList<T> operator+(const DoubleLinkedList<T> &a,const DoubleLinkedList<T> &b){

    }
    template<typename T>
    DoubleLinkedList<T> operator-(const DoubleLinkedList<T> &a,const DoubleLinkedList<T> &b){

    }
}





#endif //MYDATASTRUCTUREANDALGORITHM_MYLINKEDLIST_HPP
