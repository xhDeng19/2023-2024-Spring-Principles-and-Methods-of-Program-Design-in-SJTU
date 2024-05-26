# include "link.h"

/*
* Build a list of node and return the head node.
*/
ListNode* BuildList(int num[], int length)
{
    ListNode* End = new ListNode;
    End->next = nullptr;
    End->val = num[length - 1];
    ListNode* root = End;

    for (int i = length - 2; i >= 0; i--)
    {
        ListNode* newL = new ListNode;
        newL->val = num[i];
        newL->next = root;

        root = newL;
    }

    return root;
}

/*
* Remove the Kth node from end, and return the head node after that.
*/
ListNode* removeKthFromEnd(ListNode* head, int k)
{
    int length = 0;

    // create a dummy node
    ListNode* dum_node = new ListNode;
    dum_node->val = 0;
    dum_node->next = head;

    for (ListNode* p = dum_node; p != nullptr; p = p->next)
        length++;

    ListNode *curPtr = dum_node->next, *prePtr = dum_node;

    for (int i = 0; i < length - k - 1; i++)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
    }
    prePtr->next = curPtr->next;
    delete curPtr;

    return dum_node->next;
}

/*
* Remove all nodes in the list.
*/
void deleteAllNodes(ListNode* head)
{
    if (head->next == nullptr)
        delete head;
    else
    {
        ListNode* current_head = head->next;
        delete head;
        deleteAllNodes(current_head);
    }
}
