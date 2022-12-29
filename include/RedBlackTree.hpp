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

        Node(const int &id, const T &data, Node *parent = nullptr,
             Node *leftChild = nullptr, Node *rightChild = nullptr,
             const bool &isRed = false) :
             _id(id), _data(data), _parent(parent), _leftChild(leftChild),
             _rightChild(rightChild), _isRed(isRed) {}

        std::string toString() const {
            std::stringstream outputStream{};

            outputStream << "ID: " << _id << "\t\t" << "NODE DATA: " << _data
                    << "\t\tCOLOR: ";
            if (_isRed) {
                outputStream << "R\t\t";
            } else {
                outputStream << "B\t\t";
            }

            outputStream << "PARENT: ";
            if (nullptr == _parent) {
                outputStream << "NA\t\t";
            } else {
                outputStream << _parent->_id << "\t\t";
            }

            outputStream << "LEFT CHILD: ";
            if (nullptr == _leftChild) {
                outputStream << "NA\t\t";
            } else {
                outputStream << _leftChild->_id << "\t\t";
            }

            outputStream << "RIGHT CHILD: ";
            if (nullptr == _rightChild) {
                outputStream << "NA\t\t";
            } else {
                outputStream << _rightChild->_id << "\t\t";
            }

            return outputStream.str();
        }
    };

    RedBlackTree() = default;
    ~RedBlackTree() {
        clear();
    }

    int getHeight() const {
        return heightHelper(_root);
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
        if (nullptr == _root) {
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
        clearHelper(_root);
        _root = nullptr;
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
        preOrderHelper(vectorOfOrder, _root);
    }
    void inOrder(std::vector<int> &vectorOfOrder) const {
        inOrderHelper(vectorOfOrder, _root);
    }
    std::string toString() const {
        std::stringstream outputStream{};

        printHelper(outputStream, _root);

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
                if (nullptr != uncle && uncle->_isRed) {
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
        if (nullptr == parent || nullptr == parent->_leftChild) {
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
    void clearHelper(Node *node) {
        if (nullptr != node) {
            clearHelper(node->_leftChild);
            clearHelper(node->_rightChild);

            if (nullptr != node->_parent) {
                if (node == node->_parent->_leftChild) {
                    node->_parent->_leftChild = nullptr;
                } else {
                    node->_parent->_rightChild = nullptr;
                }
            }

            delete node;
        }
    }
    void preOrderHelper(std::vector<int> &vectorOfOrder, const Node *node) const {
        if (nullptr != node) {
            vectorOfOrder.push_back(node->_id);
            preOrderHelper(vectorOfOrder, node->_leftChild);
            preOrderHelper(vectorOfOrder, node->_rightChild);
        }
    }
    void inOrderHelper(std::vector<int> &vectorOfOrder, const Node *node) const {
        if (nullptr != node) {
            inOrderHelper(vectorOfOrder, node->_leftChild);
            vectorOfOrder.push_back(node->_id);
            inOrderHelper(vectorOfOrder, node->_rightChild);
        }
    }
    void printHelper(std::stringstream &outputStream, const Node *node) const {
        if (nullptr != node) {
            outputStream << node->toString() << std::endl;
            printHelper(outputStream, node->_leftChild);
            printHelper(outputStream, node->_rightChild);
        }
    }
    int heightHelper(const Node *node) const {
        int leftHeight{};
        int rightHeight{};

        if (nullptr != node) {
            leftHeight = heightHelper(node->_leftChild);
            rightHeight = heightHelper(node->_rightChild);

            return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
        }

        return 0;
    }
};

#endif //REDBLACKTREE_REDBLACKTREE_HPP
