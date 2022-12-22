#ifndef REDBLACKTREE_REDBLACKTREE_HPP
#define REDBLACKTREE_REDBLACKTREE_HPP

#include <iostream>
#include <sstream>
#include <vector>

template<typename T>
class RedBlackTree {
public:
    struct Node {
        int _id{};
        T _data{};
        Node *_parent{};
        Node *_leftChild{};
        Node *_rightChild{};
        bool _isRed{};

        Node(const int &id, const T &data, const Node *parent = nullptr,
             const Node *leftChild = nullptr, const Node *rightChild = nullptr,
             const bool &isRed = false) :
             _id(id), _data(data), _parent(parent), _leftChild(leftChild),
             _rightChild(rightChild), _isRed(isRed) {}

        std::string toString() const {
            std::stringstream outputStream{};
            // TODO
            return outputStream.str();
        }
    };

    RedBlackTree() = default;
    ~RedBlackTree() {
        clear();
    }

    int getHeight() const {
        // TODO
        return 0;
    }
    T getRootData() const {
        T rootData{};

        if (nullptr != _root) {
            rootData = _root->_data;
        }

        return rootData;
    };
    void add(const T &data, std::function<const int(const T &, const T &)> comparator) {
        // TODO
    }
    void clear() {
        // TODO
    }
    Node *find(const T &data, std::function<const int(const T &, const T &)> comparator) const {
        // TODO
        return nullptr;
    }
    void preOrder(std::vector<int> &vectorOfOrder) const {
        // TODO
    }
    void inOrder(std::vector<int> &vectorOfOrder) const {
        // TODO
    }
    std::string toString() const {
        std::stringstream outputStream{};
        // TODO
        return outputStream.str();
    }

private:
    int _size{};
    Node *_root{};

    void rotateLeft(Node *parent) {
        // TODO
    }
    void rotateRight(Node *parent) {
        // TODO
    }
};

#endif //REDBLACKTREE_REDBLACKTREE_HPP
