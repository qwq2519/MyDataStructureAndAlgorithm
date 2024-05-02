
#ifndef MYDATASTRUCTUREANDALGORITHM_MYRBTree_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYRBTree_HPP
/*
 性质:
 1.平衡二叉搜索树，中序遍历单调不减
 2.节点是红色/黑色
 3.根节点是黑色
 4.每个叶子结点都是黑色空节点
 5.不存在连续的两个红节点
 6.根节点到每个叶子结点的路径上包含的黑色节点数相同(又称为黑高度)
 */
#include<cstdint>
#include<optional>

namespace MyRBTree {
    template<typename T>
    class RBTree {
    private:
#define Red true
#define Black false
    private:
        struct Node {
            T val{};
            bool color{Red};
            Node *father{nullptr};
            Node *leftChild{nullptr};
            Node *rightChild{nullptr};
            size_t size{1};

            Node(T v, bool RB, Node *f, Node *l, Node *r, size_t ss)
                    : val(v), color(RB), father(f), leftChild(l), rightChild(r), size(ss) {}

            Node *brother() { //找节点的兄弟
                if (this->father->leftChild == this) {
                    return this->father->rightChild;
                } else {
                    return this->father->leftChild;
                }
            }

            bool IsleftChild() {//判断当前节点是父节点的左儿子
                return this != nullptr && this->father->leftChild == this;
            }

            bool IsrightChild() {
                return this != nullptr && this->father->rightChild == this;
            }

            void SetChild(Node *ls, Node *rs) {
                leftChild = ls;
                rightChild = rs;
                if (ls != nullptr) {
                    ls->father = this;
                }
                if (rs != nullptr) {
                    rs->father = this;
                }
            }

            Node *Succ();

            Node *PrevNode();

            Node *NextNode();

            void UpdateSize();
        };

        Node *root{nullptr};//根节点位置
        Node *hot{nullptr};//临时维护的节点



        void SolveDoubleRed(Node *);    ////双红修正
        void SolveDoubleBlack(Node *);    //双黑修正
        Node *find(T, const int);    ////允许重复的查找
        Node *rfind(T, const int);    ////不允许重复的查找
        Node *findkth(int, Node *);

        int find_rank(T, Node *);

        //单旋双旋左旋右旋过于复杂,这里采用3+4统一重平衡，将区域划分出三个节点四个字数
        //使用时判断是哪些子树即可
        void connect34(Node *, Node *, Node *, Node *, Node *, Node *, Node *);

    public:
        struct iterator {
        private:
            Node *realNode{nullptr};
        public:
            iterator &operator++() {
                realNode = realNode->NextNode();
                return *this;
            }

            iterator &operator--() {
                realNode = realNode->PrevNode();
                return *this;
            }

            T operator*() {
                return realNode->val;
            }

            iterator() = default;

            iterator(Node *p) : realNode{p} {}

            iterator(const T &val) : realNode{this->rfind(val, 0)} {}
        };

        RBTree() = default;

        int get_rank(T);

        iterator Insert(T);

        bool remove(T);

        int size();

        bool empty();

        iterator kth(int);

        iterator lower_bound(T);

        iterator upper_bound(T);
    };
}
namespace MyRBTree {
    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::Node::Succ() {
        Node *p = this->rightChild;
        while (p->leftChild != nullptr) {
            --(p->size);
            p = p->leftChild;
        }
        return p;
    }

    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::Node::PrevNode() {
        Node *p = this;
        if (leftChild == nullptr) {//该节点没有左子树,
            while (p->father && p->father->leftChild == p) {//一直往上走
                p = p->father;
            }
            p = p->father;
        } else {//有左子树，那么左子树最大的那个就是
            p = p->leftChild;
            while (p->rightChild) {
                p = p->rightChild;
            }
        }
        return p;
    }

    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::Node::NextNode() {
        Node *p = this;
        if (rightChild == nullptr) {
            while (p->father && p->father->rightChild == p)
                p = p->father;
            p = p->father;
        } else {
            p = p->rightChild;
            while (p->leftChild) {
                p = p->leftChild;
            }
        }
        return p;
    }

    template<typename T>
    void RBTree<T>::Node::UpdateSize() {
        size = 1;
        if (leftChild != nullptr) {
            size += leftChild->size;
        }
        if (rightChild != nullptr) {
            size += rightChild->size;
        }
    }


    // 参数op，插入时表示1，删除为-1，查询为0
    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::find(T val, const int op) {
        Node *p = root;//从根节点开始查询
        hot = nullptr;//维护父亲节点
        while (p != nullptr) {
            hot = p;
            p->size += op;
            if (p->val > val) {
                p = p->leftChild;
            } else {
                p = p->rightChild;
            }
        }
        return p;
    }

    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::rfind(T val, const int op) {
        Node *p = root;//从根节点开始查询
        hot = nullptr;//维护父亲节点
        while (p != nullptr && p->val != val) {//不一样的点，不允许查询相同的节点
            hot = p;
            p->size += op;
            if (p->val > val) {
                p = p->leftChild;
            } else {
                p = p->rightChild;
            }
        }
        return p;
    }

    /*
     * 将新节点当成红节点插入，保证不违反性质6，但是可能会违反性质5
     * 性质5好维护，判断是否出现双红情况即可
    */
    template<typename T>
    typename RBTree<T>::iterator RBTree<T>::Insert(T val) {
        Node *p = find(val, 1);
        if (hot == nullptr) {
            root = new Node(val, Black, nullptr, nullptr, nullptr, 1);
            return iterator(root);
        }
        p = new Node(val, Red, hot, nullptr, nullptr, 1);
        if (hot->val <= val) {
            hot->rightChild = p;
        } else {
            hot->leftChild = p;
        }
        SolveDoubleRed(p);
        return iterator(p);
    }

    template<typename T>
    void RBTree<T>::SolveDoubleRed(Node *p) {//当前节点是红色的，注意

        while ((!(p->father)) || p->father==Red) {//父节点也是红色的，双红不行
            if (p == root) {//当前节点为根节点，染黑即可
                root->color = Black;
                return;
            }
            Node *fa = p->father;
            if (fa->color==Black) return;//当前节点的父节点是黑色

            Node *uncle = p->father->brother();//叔节点
            Node *grdfa = p->father->father;//祖父节点
            if (uncle != nullptr && uncle->color==Red) {//父亲和叔叔都是红色
                grdfa->color = Red;
                uncle->color = Black;
                fa->color = Black;
                p = grdfa;
            } else {//父亲为红(则父亲非根，祖父非空)，叔叔为黑(也可能是叶子结点，祖父也可能是根)
                if (fa->IsleftChild()) {
                    if (p->IsleftChild()) {
                        fa->father = grdfa->father;
                        if (grdfa == root) root = fa;
                        else if (grdfa->father->leftChild == grdfa) {
                            grdfa->father->leftChild = fa;
                        } else {
                            grdfa->father->rightChild = fa;
                        }
                        connect34(fa, p, grdfa, p->leftChild, p->rightChild, fa->rightChild, uncle);
                        fa->color = Black;
                        grdfa->color = Red;
                    } else {
                        p->father = grdfa->father;
                        if (grdfa == root) root = p;
                        else if (grdfa->father->leftChild == grdfa) grdfa->father->leftChild = p;
                        else grdfa->father->rightChild = p;
                        connect34(p, fa, grdfa, fa->leftChild, p->leftChild, p->rightChild, uncle);
                        p->color = Black;
                        grdfa->color = Red;
                    }
                } else {
                    if (p->IsleftChild()) {
                        p->father = grdfa->father;
                        if (grdfa == root) root = p;
                        else if (grdfa->father->leftChild == grdfa) grdfa->father->leftChild = p;
                        else grdfa->father->rightChild = p;
                        connect34(p, grdfa, fa, uncle, p->leftChild, p->rightChild, fa->rightChild);
                        p->color = Black;
                        grdfa->color = Red;
                    } else {
                        fa->father = grdfa->father;
                        if (grdfa == root) root = fa;
                        else if (grdfa->father->leftChild == grdfa) grdfa->father->leftChild = fa;
                        else grdfa->father->rightChild = fa;
                        connect34(fa, grdfa, p, uncle, fa->leftChild, p->leftChild, p->rightChild);
                        fa->color = Black;
                        grdfa->color = Red;
                    }
                }
                return;
            }
        }
    }

    //统一重平衡
    template<typename T>
    void RBTree<T>::connect34(Node *nroot, Node *nleftChild, Node *nrightChild,
                              Node *ntree1, Node *ntree2, Node *ntree3, Node *ntree4) {
        nleftChild->SetChild(ntree1, ntree2);
        nrightChild->SetChild(ntree3, ntree4);
        nroot->SetChild(nleftChild, nrightChild);

        nleftChild->UpdateSize();
        nrightChild->UpdateSize();
        nroot->UpdateSize();
    }

    template<typename T>
    typename RBTree<T>::iterator RBTree<T>::lower_bound(T val) {
        Node *p = root;
        while (p) {
            hot = p;
            if (p->val < val) {
                p = p->rightChild;
            } else {
                p = p->leftChild;
            }
        }
        if (hot->val < val) {
            p = hot;//当前节点的右子树为空，找不到再大点的了，只能选择节点了
        } else {//当前节点略大于它，找个略小的
            p = hot->PrevNode();
        }
        return iterator(p);
    }

    template<typename T>
    typename RBTree<T>::iterator RBTree<T>::upper_bound(T val) {
        Node *p = root;
        while (p) {
            hot = p;
            if (p->val > val) {
                p = p->leftChild;
            } else {
                p = p->rightChild;
            }
        }
        if (hot->val > val) {
            p = hot;
        } else {
            p = hot->NextNode();
        }
        return iterator(p);
    }

    template<typename T>
    typename RBTree<T>::iterator RBTree<T>::kth(int rank) {
        return iterator(findkth(rank, root));
    }

    template<typename T>
    typename RBTree<T>::Node *RBTree<T>::findkth(int rank, Node *p) {
        if (!(p->leftChild)) {//没有左子树
            if (rank == 1) {
                return p;
            } else {
                return findkth(rank - 1, p->rightChild);
            }
        } else {
            if (p->leftChild->size == rank - 1) return p;//当前节点就是要找的
            else if (p->leftChild->size >= rank) return findkth(rank, p->leftChild);
            else return findkth(rank - (p->leftChild->size) - 1, p->rightChild);
        }
    }

    template<typename T>
    int RBTree<T>::get_rank(T v) {
        return find_rank(v, root);
    }

    template<typename T>
    int RBTree<T>::find_rank(T v, Node *p) {
        if (!p) return 1;
        else if (p->val >= v) return find_rank(v, p->leftChild);
        else return (1 + ((p->leftChild) ? (p->leftChild->size) : 0) + find_rank(v, p->rightChild));
    }

    template<typename T>
    bool RBTree<T>::remove(T v) {
        Node *p = rfind(v, -1);
        if (!p) return false;
        Node *node_suc;
        while (p->leftChild || p->rightChild) {    ////迭代寻找真后继
            if (!(p->leftChild)) {//左子树不存在
                node_suc = p->rightChild;
            } else if (!(p->rightChild)) {//右子树不存在
                node_suc = p->leftChild;
            } else {//两个子树均存在
                node_suc = p->Succ();
            }
            --(p->size);
            p->val = node_suc->val;
            p = node_suc;
        }

        if (p->color == Black) {
            --(p->size);
            SolveDoubleBlack(p);
        }
        if (p == root) {
            root = nullptr;
            delete p;
            return true;
        }
        if (p->father->leftChild == p)
            p->father->leftChild = nullptr;
        else
            p->father->rightChild = nullptr;
        delete p;
        return true;
    }

    template<typename T>
    void RBTree<T>::SolveDoubleBlack(Node *nn) {
        while (nn != root) {
            Node *pftr = nn->father;
            Node *bthr = nn->brother();
            if (bthr->color) {//兄弟为红色
                bthr->color = Black;
                pftr->color = Red;
                if (root == pftr) root = bthr;
                if (pftr->father) {
                    if (pftr->father->leftChild == pftr)
                        pftr->father->leftChild = bthr;
                    else
                        pftr->father->rightChild = bthr;
                }
                bthr->father = pftr->father;
                if (nn->IsleftChild()) {
                    connect34(bthr, pftr, bthr->rightChild, nn, bthr->leftChild, bthr->rightChild->leftChild,
                              bthr->rightChild->rightChild);
                } else {
                    connect34(bthr, bthr->leftChild, pftr, bthr->leftChild->leftChild, bthr->leftChild->rightChild,
                              bthr->rightChild, nn);
                }
                bthr = nn->brother();
                pftr = nn->father;
            }
            if (bthr->leftChild && bthr->leftChild->color) {    ////BB-3
                bool oldcolor = pftr->color;
                pftr->color = false;
                if (pftr->leftChild == nn) {
                    if (pftr->father) {
                        if (pftr->father->leftChild == pftr)
                            pftr->father->leftChild = bthr->leftChild;
                        else
                            pftr->father->rightChild = bthr->leftChild;
                    }
                    bthr->leftChild->father = pftr->father;
                    if (root == pftr) root = bthr->leftChild;
                    connect34(bthr->leftChild, pftr, bthr, pftr->leftChild, bthr->leftChild->leftChild,
                              bthr->leftChild->rightChild, bthr->rightChild);
                } else {
                    bthr->leftChild->color = false;
                    if (pftr->father) {
                        if (pftr->father->leftChild == pftr)
                            pftr->father->leftChild = bthr;
                        else
                            pftr->father->rightChild = bthr;
                    }
                    bthr->father = pftr->father;
                    if (root == pftr) root = bthr;
                    connect34(bthr, bthr->leftChild, pftr, bthr->leftChild->leftChild, bthr->leftChild->rightChild,
                              bthr->rightChild, pftr->rightChild);
                }
                pftr->father->color = oldcolor;
                return;
            } else if (bthr->rightChild && bthr->rightChild->color) {    //兄弟为黑色且有哄儿子
                bool oldcolor = pftr->color;
                pftr->color = false;
                if (pftr->leftChild == nn) {
                    bthr->rightChild->color = false;
                    if (pftr->father) {
                        if (pftr->father->leftChild == pftr)
                            pftr->father->leftChild = bthr;
                        else
                            pftr->father->rightChild = bthr;
                    }
                    bthr->father = pftr->father;
                    if (root == pftr) root = bthr;
                    connect34(bthr, pftr, bthr->rightChild, pftr->leftChild, bthr->leftChild,
                              bthr->rightChild->leftChild, bthr->rightChild->rightChild);
                } else {
                    if (pftr->father) {
                        if (pftr->father->leftChild == pftr)
                            pftr->father->leftChild = bthr->rightChild;
                        else
                            pftr->father->rightChild = bthr->rightChild;
                    }
                    bthr->rightChild->father = pftr->father;
                    if (root == pftr) root = bthr->rightChild;
                    connect34(bthr->rightChild, bthr, pftr, bthr->leftChild, bthr->rightChild->leftChild,
                              bthr->rightChild->rightChild, pftr->rightChild);
                }
                pftr->father->color = oldcolor;
                return;
            }
            if (pftr->color) {                    //兄弟为黑色且没有红儿子，父亲为红色
                pftr->color = Black;
                bthr->color = Red;
                return;
            } else {                        //兄弟父亲都是黑色，且兄弟没有红儿子
                bthr->color = Red;
                nn = pftr;
            }
        }
    }
}
#endif //MYDATASTRUCTUREANDALGORITHM_MYRBTree_HPP