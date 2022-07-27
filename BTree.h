#ifndef __BTREE_H__
#define __BTREE_H__


#include <bits/stdc++.h>
#include "Node.h"

class BTree
{
private:
    Node * root;
    int order;
private:
    void insert_in_node(Node *& node,  int data_insert);
    void print_to_console(Node * tmp);
public:
    BTree(int _order);
    void insert(int data_to_insert);
    int * search(int data_to_search);
    void remove(int data_to_remove);
    void print_to_console();
};

#endif // __BTREE_H__