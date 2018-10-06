#include "ListNode.h"
#include "BinaryTreeNode.h"

int main()
{
    ListNode *ln1 = new ListNode(1);
    ListNode *ln2 = new ListNode(2);
    ListNode *ln3 = new ListNode(3);
    ListNode *ln4 = new ListNode(4);

    ln1->SetNext(ln2);
    ln2->SetNext(ln3);
    ln3->SetNext(ln4);
    
    ListNode *p = ln1->Next();
    p->PrintValue();
    p = p->Next();
    p->PrintValue();
    p = p->Next();
    p->PrintValue();
    p = p->Prev()->Prev()->Prev();
    p->PrintValue();
    
    delete ln1;
    delete ln2;
    delete ln3;
    delete ln4;
}
