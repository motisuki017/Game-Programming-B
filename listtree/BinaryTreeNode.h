#ifndef BinaryTreeNode_h
#define BinaryTreeNode_h
#pragma once

class BinaryTreeNode
{
public:
    BinaryTreeNode(int v);
public:
    void SetLeft(BinaryTreeNode *p);
    void SetRight(BinaryTreeNode *p);
    BinaryTreeNode* Left();
    BinaryTreeNode* Right();
    void PrintValue() const;
private:
    BinaryTreeNode *parent;
    BinaryTreeNode *leftChild;
    BinaryTreeNode *rightChild;
    int value;
};

#endif /* BinaryTreeNode_h */
