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
    void add(const T &data,
             std::function<const int (const T &, const T &)> comparator) {
        if (_root == nullptr) {
            _root = new Node(_size++, data);
            return;
        }

        Node *currentNode{_root};
        Node *parentNode{nullptr};
        bool isLeft{};

        while (nullptr != currentNode) {
            int result = comparator(currentNode->_data, data);

            if (0 == result) {
                return;
            } else if (0 < result) {
                parentNode = currentNode;
                currentNode = currentNode->_leftChild;
                isLeft = true;
            } else {
                parentNode = currentNode;
                currentNode = currentNode->_rightChild;
                isLeft = false;
            }
        }

        currentNode = new Node(_size++, data, parentNode, nullptr, nullptr, true);

        if (isLeft) {
            parentNode->_leftChild = currentNode;
        } else {
            parentNode->_rightChild = currentNode;
        }

        addHelper(currentNode);
    }
    void clear() {
        // TODO
    }

    /*
     * Return pointer to a node which contains the data or a nullptr if the data
     * is not in the tree
     */
    Node *find(const T &data,
               std::function<const int (const T &,const T &)> comparator) const {
        Node *currentNode{_root};

        while (nullptr != currentNode) {
            int result = comparator(currentNode->_data, data);
            if (0 == result) {
                break;
            } else if (0 < result) {
                currentNode = currentNode->_leftChild;
            } else {
                currentNode = currentNode->_rightChild;
            }
        }

        return currentNode;
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

    void addHelper(Node *child) {
        // TODO
    }
    void rotateLeft(Node *parent) {
        // TODO
    }
    void rotateRight(Node *parent) {
        // TODO
    }
};

#endif //REDBLACKTREE_REDBLACKTREE_HPP
