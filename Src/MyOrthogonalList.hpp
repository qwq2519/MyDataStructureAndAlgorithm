

#ifndef MYDATASTRUCTUREANDALGORITHM_MYORTHOGONALLIST_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYORTHOGONALLIST_HPP

#include<cstdint>
#include<iostream>
#include<format>
#include<string>
/*
十字链表，可以用来存稀疏矩阵，省空间
 可以便于统计每个节点的出度和入度
 *
 */
namespace MyOrthogonalList {

    template<typename T>
    class OrthogonalList {
    public:
        using value_type = T;
        using itertaor = T *;
    private:
        struct node {
            int64_t row{0}, col{0};
            value_type data{};
            node *right{nullptr};
            node *down{nullptr};

            node() = default;

            node(int64_t i, int64_t j, value_type val) : row{i}, col{j}, data{val} {}

            ~node() {
                std::string out=std::format("第{}行第{}列元素{}被析构\n",row,col,data);
                std::cout<<out;
                delete right;
                delete down;
            }
        };

    private:
        node **rowHead, **colHead;
        int64_t rowNums{0}, colNums{0}, size{0};//矩阵的行数列数以及非零元的个数
    public:
        OrthogonalList() = default;

        OrthogonalList(int64_t i, int64_t j) : rowNums{i}, colNums{j} {
            rowHead = new node *[i + 1];
            colHead = new node *[j + 1];
            for (int64_t k(0); k <= i; ++k) {
                rowHead[k] = new node;
            }
            for (int64_t k(0); k <= j; ++k) {
                colHead[k] = new node;
            }
        }

        ~OrthogonalList();

        OrthogonalList(const OrthogonalList &) = delete;

        OrthogonalList &operator=(const OrthogonalList &) = delete;

    public:
        void AddNode(int64_t i, int64_t j, value_type val);

        void Print() const;
    };


}

namespace MyOrthogonalList {
    template<typename T>
    OrthogonalList<T>::~OrthogonalList() {
        for (int64_t k(0); k <= rowNums; ++k) {
            if(rowHead[k]!= nullptr){
                auto p{rowHead[k]};
                while(p->right!= nullptr){
                    auto temp=p->right;
                    p->~node();
                    p=temp;
                }
                p->~node();
            }else if(rowHead[k]== nullptr){

            }
        }
        delete []rowHead;
        delete []colHead;
    }

    template<typename T>
    void OrthogonalList<T>::AddNode(int64_t i, int64_t j, value_type val) {
        node *e = new node(i, j, val);
//
        if (rowHead[i]->right == nullptr || rowHead[i]->right->col > e->col) {//第i行当前是零行，或者目前所有非0元素都在该元素的右边，直接插入
            e->right = rowHead[i]->right;
            rowHead[i]->right = e;
        } else {
            for (auto p{rowHead[i]->right};; p = p->right) {
                if (p->right == nullptr) {//到结尾了，说明e是在所有非零元素最右边的
                    p->right = e;
                    break;
                } else if (p->right != nullptr && p->col < e->col && p->right->col > e->col) {
                    e->right = p->right;
                    p->right = e;
                }
            }
        }
        if (colHead[j]->down == nullptr || colHead[j]->down->row > e->row) {
            e->down = colHead[j]->down;
            colHead[j]->down = e;
        } else {
            for (auto p{colHead[j]->down};; p = p->down) {
                if (p->down == nullptr) {//到结尾了，说明e是在所有非零元素最下边的
                    p->down = e;
                    break;
                } else if (p->down != nullptr && p->row < e->row && p->down->row > e->row) {
                    e->down = p->down;
                    p->down = e;
                }
            }
        }
    }

    template<typename T>
    void OrthogonalList<T>::Print() const {

        for (int64_t i{1}; i <= rowNums; ++i) {

            if (rowHead[i] == nullptr) {//该行是纯0行
                for (int64_t j{1}; j <= colNums; ++j) {
                    std::cout << '0' << (j == colNums ? "" : " ");
                }
                std::cout << std::endl;
            } else {//该行有非零元
                auto curNode = rowHead[i]->right;
                for (int64_t j{1}; j <= colNums; ++j) {

                    if (curNode == nullptr) {//该行非零元输出完了
                        for (; j <= colNums; ++j) {
                            std::cout << '0' << (j == colNums ? "" : " ");
                        }
                        break;
                    }

                    if (curNode->col > j) {//下一个在当前列的右边
                        std::cout << '0' << (j == colNums ? "" : " ");
                    } else {
                        std::cout << curNode->data << (j == colNums ? "" : " ");
                        curNode = curNode->right;
                    }
                }
                std::cout << std::endl;
            }
        }
    }

}


#endif