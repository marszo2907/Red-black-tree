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
        while (_root != child && child->_parent->_isRed) {
            /*
             * Case 1: A child's parent is a right child.
             */
            if (nullptr != child->_parent->_parent
                && child->_parent == child->_parent->_parent->_rightChild) {
                Node *uncle{child->_parent->_parent->_leftChild};

                /*
                 * Case 1.A: A child's uncle is red.
                 * Fix: Set a grandparent's color to red and a parent's and an
                 * uncle's color to black. Check if there is a conflict between
                 * a grandparent and a great-grandparent in a next iteration.
                 */
                if (nullptr != uncle && uncle->_isRed) {
                    uncle->_isRed = false;
                    child->_parent->_isRed = false;
                    child->_parent->_parent->_isRed = true;
                    child = child->_parent->_parent;
                } else {
                    /*
                     * Case 1.B: The right-left conflict.
                     * Fix: Perform a right rotation of a child-parent pair. Leads
                     * to the right-right conflict.
                     */
                    if (child == child->_parent->_leftChild) {
                        child = child->_parent;
                        rotateRight(child);
                    }

                    /*
                     * Case 1.C: The right-right conflict.
                     * Fix: Set a grandparent's color to red and a parent's color
                     * to black. Perform a left rotation of a parent-grandparent
                     * pair.
                     */
                    child->_parent->_isRed = false;
                    child->_parent->_parent->_isRed = true;
                    rotateLeft(child->_parent->_parent);
                }
            /*
             * Case 2: Child's parent is a left child.
             */
            } else {
                Node *uncle {child->_parent->_parent->_rightChild};

                /*
                 * Case 2.A: Child's uncle is red.
                 * Fix: Set a grandparent's color to red and a parent's and an
                 * uncle's color to black. Check if there is a conflict between
                 * a grandparent and a great-grandparent in a next iteration.
                 */
                if(nullptr != uncle && uncle->_isRed) {
                    uncle->_isRed = false;
                    child->_parent->_isRed = false;
                    child->_parent->_parent->_isRed = true;
                    child = child->_parent->_parent;
                } else {
                    /*
                     * Case 2.B: The left-right conflict.
                     * Fix: Perform a left rotation of a child-parent pair. Leads
                     * to the left-left conflict.
                     */
                    if (child == child->_parent->_rightChild) {
                        child = child->_parent;
                        rotateLeft(child);
                    }
                    /*
                     * Case 1.C: The left-left conflict.
                     * Fix: Set a grandparent's color to red and a parent's color
                     * to black. Perform a right rotation of a parent-grandparent
                     * pair.
                     */
                    child->_parent->_isRed = false;
                    child->_parent->_parent->_isRed = true;
                    rotateRight(child->_parent->_parent);
                }
            }
        }

        _root->_isRed = false;
    }
    void rotateLeft(Node *parent) {
        if (nullptr == parent || nullptr == parent->_rightChild) {
            return;
        }

        Node *child = parent->_rightChild;
        parent->_rightChild = child->_leftChild;

        if (nullptr != child->_leftChild) {
            child->_leftChild->_parent = parent;
        }
        child->_parent = parent->_parent;

        if (nullptr == parent->_parent) {
            _root = child;
        } else if(parent == parent->_parent->_leftChild) {
            parent->_parent->_leftChild = child;
        } else {
            parent->_parent->_rightChild = child;
        }

        child->_leftChild = parent;
        parent->_parent = child;
    }
    void rotateRight(Node *parent) {
        if(nullptr == parent || nullptr == parent->_leftChild) {
            return;
        }

        Node *child = parent->_leftChild;
        parent->_leftChild = child->_rightChild;

        if (nullptr != child->_rightChild) {
            child->_rightChild->_parent = parent;
        }
        child->_parent = parent->_parent;

        if (nullptr == parent->_parent) {
            _root = child;
        } else if(parent == parent->_parent->_leftChild) {
            parent->_parent->_leftChild = child;
        } else {
            parent->_parent->_rightChild = child;
        }

        child->_rightChild = parent;
        parent->_parent = child;
    }
};

#endif //REDBLACKTREE_REDBLACKTREE_HPP
