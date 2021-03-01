
#ifndef TREE_H
#define TREE_H

#include <algorithm>

#include "linked list.h"
#include "my stack.h"

using namespace std;

class Tree {

private:

    string nodeName;
    int nodeVolume;
    Tree *parent;
    DoubleLinkedList<Tree *> children;

public:

    /*
     * Constructor
     *
     * With three optional input :
     * the name of the folder,
     * the volume of the folder,
     * the parent of the tree
     */
    explicit Tree(string = string(), int const & = int(), Tree * = nullptr);

    /*
     * Destructor
     *
     * Calls the destructor of the children and deletes this
     */
    ~Tree();

    /*
     * Gets the volume of the folder
     */
    int volume() const;

    /*
     * Gets the name of the folder
     */
    string name();

    /*
     * Gets the address of the parent
     */
    Tree *getParent() const;

    /*
     * Gets the number of the children
     */
    int degree() const;

    /*
     * Checks if the node is root
     */
    bool isRoot() const;

    /*
     * Checks if the node is leaf
     */
    bool isLeaf() const;

    /*
     * Gets the child at given integer input
     */
    Tree *childAt(int) const;

    /*
     * Gets the max height of the tree
     */
    int height() const;

    /*
     * Gives the name and the volume and creates a new node and adds it
     * to children
     */
    void addChild(string, int);

    /*
     * Returns the number of nodes in the tree
     */
    int size() const;

    /*
     * Attaches the input tree to this tree
     * If the input tree is not a root detaches it from it's tree
     */
    void attach(Tree *);

    /*
     * Removes itself from it's parent and sets it's parent NULL
     */
    void detach();

    /*
     * Prints this node's volume and then calls it's children's Print function
     */
    void print(ofstream &, int);

    /*
     * Calculates the total volume of each node
     */
    int totalVolume();
};

Tree::Tree(string name, const int &volume, Tree *p) :
        nodeName(std::move(name)),
        nodeVolume(volume),
        parent(p) {

}

Tree::~Tree() {

    for (int i = 0; i < degree(); ++i) {
        childAt(i)->~Tree();
    }

    delete this;
}

int Tree::volume() const {
    return nodeVolume;
}

string Tree::name() {

    return nodeName;
}

Tree *Tree::getParent() const {
    return parent;
}

int Tree::degree() const {

    return children.size();
}

bool Tree::isRoot() const {

    return parent == nullptr;
}

bool Tree::isLeaf() const {

    return children.empty();
}

Tree *Tree::childAt(int n) const {

    if (n < 0 || n >= degree()) {
        return nullptr;
    }

    auto child = children.begin();

    for (int i = 0; i < n; ++i) {
        child = child->next();
    }
    return child->value();


}

int Tree::height() const {

    int treeHeight = 0;

    for (auto child = children.begin(); child != nullptr; child = child->next()) {
        treeHeight = max(treeHeight, child->value()->height() + 1);
    }

    return treeHeight;
}

void Tree::addChild(string name, int volume) {

    Tree *t = new Tree(name, volume);

    t->parent = this;

    children.pushBack(t);
}

int Tree::size() const {

    int treeSize = 1;

    for (auto child = children.begin(); child != nullptr; child = child->next()) {
        treeSize += child->value()->size();
    }

    return treeSize;
}

void Tree::attach(Tree *tree) {

    if (!tree->isRoot()) {
        tree->detach();
    }

    tree->parent = this;

    children.pushBack(tree);

}

void Tree::detach() {

    if (isRoot()) {
        return;
    }

    getParent()->children.erase(this);

    parent = nullptr;

}

void Tree::print(ofstream &ofs, int depth) {

    for (int i = 0; i < depth; ++i) {
        ofs << "    ";
    }

    ofs << nodeName << "/ " << totalVolume() << endl;

    for (int i = 0; i < degree(); ++i) {
        childAt(i)->print(ofs, depth + 1);
    }

}

int Tree::totalVolume() {

    int totalV = 0;

    Stack<Tree *> stack;

    stack.push(this);

    while (!stack.empty()) {

        Tree *currTree = stack.pop();
        totalV += currTree->volume();

        for (int i = currTree->degree() - 1; i >= 0; --i) {

            stack.push(currTree->childAt(i));
        }
    }

    return totalV;
}


#endif
