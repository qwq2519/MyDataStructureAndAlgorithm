//
// Created by 2519 on 2024/4/17.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP

#include<vector>
#include<iostream>
#include<algorithm>
#include<string>
#include<stack>
#include<queue>

namespace MyTree {
    template<typename T>
    class BinaryTree {
    public:
        using value_type = T;
        struct Node {
            value_type data{};
            Node *left{nullptr};
            Node *right{nullptr};
        };
        using iterator = Node *;
    public:
        iterator root{nullptr};

        ~BinaryTree();

    public:
        void PreOrderBuild(iterator &p, std::string &str);

        void destory(iterator p);

    public:

        void PreOrderTraversalRecursion(const iterator p, std::vector<T> &result) const;

        void PreOrderTraversalIteration(const iterator p, std::vector<Node> &result) const;

        void InOrderTraversalRecursion(const iterator p, std::vector<Node> &result) const;

        void InOrderTraversalIteration(const iterator p, std::vector<Node> &result) const;

        void PostOrderTraversalRecursion(const iterator p, std::vector<Node> &result) const;

        void PostOrderTraversalIteration(const iterator p, std::vector<Node> &result) const;

        void InOrderTraversalDivideAndConquer(const iterator p, std::vector<Node> &result) const;

        void LevelOrderTraversalBfs(const iterator p, std::vector<std::vector<Node>> &result) const;

        void LevelOrderTraversalDfs(const iterator p, int level, std::vector<std::vector<Node>> &result) const;


    private:
        std::vector<Node> DivideAndConquer(const iterator p) const;
    };

    template<typename T>
    class ArrayBinaryTree {
        using value_type = T;
    private:
        std::vector<value_type> Tree;

    public:
        explicit ArrayBinaryTree(std::vector<T> arr) : Tree{arr} {}

        size_t Size() {
            return Tree.size();
        }

        value_type GetVal(size_t index) {
            if (index < 0 || index >= Size()) {
                std::cerr << "Out of Bound!";
                return {};
            }
            return Tree[index];
        }

        size_t Left(size_t i) {
            return i * 2 + 1;
        }

        size_t Right(size_t i) {
            return i * 2 + 2;
        }

        size_t Parent(size_t i) {
            return (i - 1) / 2;
        }

    public:
        size_t GetHeightBfs() {
            std::queue<std::pair<size_t, size_t>> q;
            if (!Size()) return 0;
            q.push({0, 1});
            size_t ans(0);
            while (q.size()) {
                auto t = q.front();
                q.pop();
                ans = std::max(ans, t.second);
                if (GetVal(Left(t.first))) {
                    q.push({Left(t.first), t.second + 1});
                }
                if (GetVal(Right(t.first))) {
                    q.push({Right(t.first), t.second + 1});
                }
            }
            return ans;
        }

        size_t GetHeightDfs(int index) {
            if (!GetVal(index)) {
                return 0;
            } else {
                size_t l = GetHeightDfs(Left(index));
                size_t r = GetHeightDfs(Right(index));
                return 1 + std::max(l, r);
            }
        }
    };
}
namespace MyTree {

    template<typename T>
    BinaryTree<T>::~BinaryTree() {
        destory(root);
    }

    template<typename T>
    void BinaryTree<T>::destory(iterator p) {
        if (p != nullptr) {
            destory(p->left);
            destory(p->right);
            delete p;
        }
        p = nullptr;
    }


    template<typename T>
    void BinaryTree<T>::PreOrderBuild(iterator &p, std::string &str) {
        if (str.empty()) {
            p = nullptr;
            return;
        }
        char ch = *str.begin();
        str.erase(str.begin());
        if (ch == '#') {
            p = nullptr;
            return;
        }
        p = new Node{ch, nullptr, nullptr};
        PreOrderBuild(p->left, str);
        PreOrderBuild(p->right, str);
    }

    template<typename T>
    void BinaryTree<T>::PreOrderTraversalRecursion(const iterator p, std::vector<T> &result) const {
        if (p == nullptr) return;
        result.push_back(p->data);
        PreOrderTraversalRecursion(p->left, result);
        PreOrderTraversalRecursion(p->right, result);
    }

    template<typename T>
    void BinaryTree<T>::PreOrderTraversalIteration(const iterator p, std::vector<Node> &result) const {
        std::stack<iterator> call;
        if (p != nullptr) call.push(p);
        while (!call.empty()) {
            auto t = call.top();
            call.pop();
            if (t != nullptr) {
                if (t->right) call.push(t->right);
                if (t->left) call.push(t->left);
                call.push(t);//当前节点压栈，以后处理，因为是先序遍历，所以最先压栈
                call.push(nullptr);//在当前节点之前加入空节点表示已经访问过
            } else {//当前节点已经访问过
                result.push_back(*call.top());
                call.pop();//处理完了，第二次弹出，彻底从栈溢出
            }
        }
    }

    template<typename T>
    void BinaryTree<T>::InOrderTraversalIteration(const iterator p, std::vector<Node> &result) const {
        std::stack<iterator> call;
        if (p != nullptr) call.push(p);
        while (!call.empty()) {
            auto t = call.top();
            call.pop();
            if (t != nullptr) {
                if (t->right) call.push(t->right);
                call.push(t);
                call.push(nullptr);
                if (t->left) call.push(t->left);

            } else {//当前节点已经访问过
                result.push_back(*call.top());
                call.pop();
            }
        }
    }

    template<typename T>
    void BinaryTree<T>::PostOrderTraversalIteration(const iterator p, std::vector<Node> &result) const {
        std::stack<iterator> call;
        if (p != nullptr) call.push(p);
        while (!call.empty()) {
            iterator t = call.top();
            call.pop();
            if (t != nullptr) {
                call.push(t);
                call.push(nullptr);
                if (t->right) call.push(t->right);
                if (t->left) call.push(t->left);

            } else {
                result.push_back(*call.top());
                call.pop();
            }
        }
    }

    template<typename T>
    std::vector<typename BinaryTree<T>::Node> BinaryTree<T>::DivideAndConquer(const iterator p) const {
        std::vector<Node> result;
        if (p == nullptr) return result;

        std::vector<Node> left = DivideAndConquer(p->left);
        std::vector<Node> right = DivideAndConquer(p->right);

        result.push_back(p);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        return result;

    }

    template<typename T>
    void BinaryTree<T>::InOrderTraversalDivideAndConquer(const iterator p, std::vector<Node> &result) const {
        result = DivideAndConquer(p);
    }

    template<typename T>
    void BinaryTree<T>::LevelOrderTraversalBfs(const iterator p, std::vector<std::vector<Node>> &result) const {
        result.clear();
        if (p == nullptr) return;

        std::queue<iterator> q;
        q.push(p);
        while (!q.empty()) {
            auto len = q.size();
            std::vector<Node> Level;

            for (size_t i{0}; i < len; ++i) {
                auto t = q.front();
                q.pop();
                Level.push_back(t);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            result.push_back(Level);
        }
    }

    template<typename T>
    void
    BinaryTree<T>::LevelOrderTraversalDfs(const iterator p, int level, std::vector<std::vector<Node>> &result) const {
        if (p == nullptr) return;
        if (result.size() == level) result.resize(level + 1);
        result[level].push_back(p);
        LevelOrderTraversalDfs(p->left, level + 1, result);
        LevelOrderTraversalDfs(p->right, level + 1, result);
    }
}


namespace MyTree {
    template<typename T>
    struct TreeNode; //定义一个结构体原型

    template<typename T>
    class Tree;      //定义一个类原型

    template<typename T>
    class Iterator; //定义一个类原型

    template<typename T>
    TreeNode<T> *Clone(TreeNode<T> *, std::vector<TreeNode<T> *>, TreeNode<T> *);

    template<typename T>
    struct TreeNode {
        T data{};
        TreeNode *father{nullptr};
        std::vector<TreeNode<T> *> child;

        TreeNode(T val, TreeNode *f) : data{val}, father{f} {}

        void SetFather(TreeNode &node) {
            father = &node;
        }

        void AddChild(TreeNode &node) {
            child.push_back(&node);
        }
    };

    template<typename T>
    class Tree {
    private:
        std::vector<TreeNode<T> *> _nodes;         //节点数组
        std::vector<TreeNode<T> *>::iterator LIt; //一个节点迭代器
        size_t heightdfshelper(TreeNode<T> *);

        size_t level(TreeNode<T> *, Iterator<T>);

    public:
        Tree() = default;                            //默认构造函数
        Tree(const Tree &other) {                 //复制构造函数
            if (!other._nodes.empty()) {
                Clone(other._nodes.front(), _nodes, 0);
            }
        }

        Tree(const T val) {                   //带参数构造函数
            _nodes.push_back(new TreeNode(val));
        }

        Tree(const T, const std::vector<Tree *> &);//带参数构造函数
        ~Tree() {                           //析构函数
            for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
                delete *it;
            }
        }

        Tree &operator=(const Tree &);      //=符号运算符重载
        bool operator==(const Tree &);      //==符号运算符重载
        bool operator!=(const Tree &);      //!=符号运算符重载

        //下面是成员函数
        void Clear();                      //清空
        [[nodiscard]] bool IsEmpty() const { return _nodes.empty(); }               //判断是否为空
        [[nodiscard]] size_t Size() const { _nodes.size(); }                   //计算节点数目
        size_t Leaves();                      //计算叶子数
        size_t Heightdfs();                      //计算树的高度
        size_t Heightbfs();

        Iterator<T> begin() { return Iterator(this, _nodes.begin()); };                  //Tree Begin
        Iterator<T> end() { return Iterator(this, _nodes.end()); };                    //Tree End
        friend class Iterator<T>;

    };

    template<typename T>
    class Iterator {
    private:
        Tree<T> *_tree{nullptr};                     //Tree data
        std::vector<TreeNode<T> *>::iterator lit; //List Iterator
    public:
        Iterator() = default;                               //默认构造函数
        Iterator(const Iterator &other) : _tree{other._tree}, lit{other.lit} {};                //复制构造函数
        Iterator(Tree<T> *t, TreeNode<T> *n) {
            _tree = t;
            lit = std::find(_tree->nodes.begin(), _tree->nodes.end(), n);
        };                //构造函数
        //运算符重载
        void operator=(const Iterator &) = default;          //赋值运算符重载
        Iterator &operator++() {                 //前缀++运算符
//            Iterator(*this);
            ++lit;
            return *this;
        }

        Iterator operator++(int) {                 //后缀++运算符
            Iterator it(*this);
            ++lit;
            return it;
        }

        int operator*() const {//获得节点信息
            return (*lit)->data;
        }

        [[nodiscard]] bool operator!() {
            return lit == _tree->_nodes.end();
        }

        friend class Tree<T>;
    };
}
namespace MyTree {
    template<typename T>
    Tree<T>::Tree(const T val, const std::vector<Tree *> &lit) {//很多颗树合并成一个，他们的父亲都是新树根，新树根节点是值为val的
        TreeNode<T> *root = new TreeNode(val);
        _nodes.push_back(root);

        typename std::vector<Tree *>::const_iterator it;
        for (it = lit.begin(); it != lit.end(); ++it) {
            if (!((*it)->_nodes.empty())) {
                Tree *tp = new Tree(**it);
                TreeNode<T> *p = tp->_nodes.front();
                root->child.push_back(p);
                p->father = root;
                typename std::vector<TreeNode<T> *>::iterator it1 = tp->_nodes.begin();
                typename std::vector<TreeNode<T> *>::iterator it2 = tp->_nodes.end();
                _nodes.push_back(it1, it2);
            }
        }
    }

    template<typename T>
    Tree<T> &Tree<T>::operator=(const Tree<T> &other) {
        if (&other != this) {
            Clear();
            Tree *p = new Tree(other);
            this->_nodes = p->nodes;
        }
        return *this;
    }

    template<typename T>
    bool Tree<T>::operator==(const Tree<T> &other) {
        if (_nodes.size() != other._nodes.size()) {
            return false;
        }
        auto it = _nodes.begin();
        const auto _it = other.begin();
        while (it != _nodes.end() && _it != other._nodes.end()) {
            if ((*it)->data != (*_it)->data) {
                return false;
            }
            ++it;
            ++_it;
        }
        return true;
    }

    template<typename T>
    bool Tree<T>::operator!=(const Tree<T> &other) {
        return !(*this == other);
    }

    template<typename T>
    void Tree<T>::Clear() {
        for (auto it{_nodes.begin()}; it != _nodes.end(); ++it) {
            delete *it;
        }
        _nodes.clear();
    }

    template<typename T>
    size_t Tree<T>::Leaves() {//计算叶子数
        size_t i = 0;
        for (auto it{_nodes.begin()}; it != _nodes.end(); ++it) {
            if ((*it)->_children.size() == 0) {
                i++;
            }
        }
        return i;
    }

    template<typename T>
    size_t Tree<T>::Heightdfs() {
        if (!_nodes.empty()) {
            TreeNode<T> *TNode = _nodes.front();//根节点
            return heightdfs(TNode);
        } else {
            return 0; //判断为空树
        }
    }

    template<typename T>
    size_t Tree<T>::heightdfshelper(TreeNode<T> *node) {
        if (!node) {
            return 0;
        } else {
            const auto &plist = node->child;
            if (plist.size() == 0) {
                return 0;
            }
            int maxH = 0;
            for (auto it = plist.begin(); it != plist.end(); it++) {
                int h = height(*it);
                if (h > maxH) {
                    maxH = h;
                }
            }
            return maxH + 1;
        }
    }

    template<typename T>
    size_t Tree<T>::Heightbfs() {
        if (_nodes.empty()) { return 0; }
        else {
            size_t maxH{1};
            std::queue<std::pair<TreeNode<T> *, size_t>> q;
            q.push(_nodes.front(), 1);
            while (!q.empty()) {
                auto t = q.front();
                maxH = max(maxH, t.second);
                q.pop();
                const auto &node = t.first->child;
                for (auto it: node) {
                    q.pop(it, t.second + 1);
                }
            }
            return maxH;
        }
    }

    template<typename T>
    TreeNode<T> *clone(TreeNode<T> *node, std::vector<TreeNode<T> *> &nodes, TreeNode<T> *nodep) {
        TreeNode<T> *cp = new TreeNode(node->_data, nodep);
        nodes.push_back(cp);
        auto &l = node->_children;
        auto &cl = cp->_children;
        for (auto lt = l.begin(); lt != l.end(); lt++) {
            cl.push_back(clone(*lt, nodes, cp));
        }
        return cp;
    }
}
#endif //MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP
