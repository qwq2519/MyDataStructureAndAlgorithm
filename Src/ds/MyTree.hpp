//
// Created by 2519 on 2024/4/17.
//

#ifndef MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP
#define MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP

#include<vector>
#include<iostream>
#include<algorithm>
#include<memory>
#include<stack>
#include<queue>

namespace MyTree {
    template<typename T>
    class BinaryTree {
        using value_type = T;
        struct Node {
            value_type data{};
            std::shared_ptr<Node> left{nullptr};
            std::shared_ptr<Node> right{nullptr};
        };
        using iterator = std::shared_ptr<Node>;
    public:
        iterator root;
    public:

        void PreOrderTraversalRecursion(const iterator p, std::vector<Node> &result) const;

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
            if (!GetVal(index)){
                return 0;
            }
            else{
                return 1+std::max(GetHeightDfs(Left(index)),GetHeightDfs(Right(index)));
            }
    };
}

namespace MyTree {

    template<typename T>
    void BinaryTree<T>::PreOrderTraversalRecursion(const iterator p, std::vector<Node> &result) const {
        if (p == nullptr) return;
        result.push_back(p->val);
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

#endif //MYDATASTRUCTUREANDALGORITHM_MYTREE_HPP
