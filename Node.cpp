#include "Node.h"

Node::Node()
{
    this->sons.push_back(nullptr);
    this->parent = nullptr;
}