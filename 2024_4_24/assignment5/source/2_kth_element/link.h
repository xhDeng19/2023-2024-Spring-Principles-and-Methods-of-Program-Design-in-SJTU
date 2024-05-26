# ifndef link_h
# define link_h

struct ListNode {
    int val;
    ListNode *next;
};

ListNode* BuildList(int num[], int length);  // Todo: Build a list of node and return the head node.
ListNode* removeKthFromEnd(ListNode* head, int k); // Todo: Remove the Kth node from end, and return the head node after that.
void deleteAllNodes(ListNode* head); // Todo: Remove all nodes in the list.

# endif