#include "ListNode.h"
#include <iostream>

ListNode::ListNode(int v)
{
    this->value = v;
    this->next = nullptr;
    this->prev = nullptr;
}

void ListNode::SetNext(ListNode *p)
{
    this->next = p;
    p->prev = this;
}

ListNode* ListNode::Next()
{
    return next;
}

ListNode* ListNode::Prev()
{
    return prev;
}

void ListNode::PrintValue() const
{
    std::cout << value << std::endl;
}
