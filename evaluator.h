
#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "tree.h"

/*
 * Creates the nodes of tree and orders they in the correct way
 */
class Evaluator {

private:

    /*
     * Stores the nodes of the tree before creating the tree
     */
    DoubleLinkedList<Tree *> trees;

public:

    /*
     * Gets parameters of tree node and creates a new tree node
     */
    void getNodes(string, int);

    /*
     * Gets two names of tree and finds it in the list and attaches two given tree nodes
     */
    void order(string, string);

    /*
     * Gets the output file as parameter and find the root tree node and pass it to
     * print function of that tree node
     */
    void print(ofstream &);

};

void Evaluator::getNodes(string name, int volume) {

    trees.pushBack(new Tree(name, volume));
}

void Evaluator::order(string name1, string name2) {


    Tree *t1 = nullptr;
    Tree *t2 = nullptr;

    for (auto *ptr = trees.begin(); ptr != nullptr; ptr = ptr->next()) {

        if (ptr->value()->name() == name1) {
           t1 = ptr->value();
       }

       if (ptr->value()->name() == name2) {
           t2 = ptr->value();
       }
    }


    t1->attach(t2);


}

void Evaluator::print(ofstream &fout) {


    for (auto *ptr = trees.begin(); ptr != nullptr; ptr = ptr->next()) {

        if (ptr->value()->isRoot()) {
           ptr->value()->print(fout, 0);
           return;
        }
    }


}

#endif
