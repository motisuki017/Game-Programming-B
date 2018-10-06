#ifndef ListNode_h
#define ListNode_h
#pragma once

class ListNode
{
public:
    ListNode(int v);
public:
    void SetNext(ListNode *p);
    ListNode* Next();
    ListNode* Prev();
    void PrintValue() const;
private:
    ListNode *prev;
    ListNode *next;
    int value;
};

#endif /* ListNode_h */
