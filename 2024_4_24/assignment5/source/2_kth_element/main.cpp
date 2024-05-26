# include <iostream>
# include "link.h"
using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    int *num = new int[n];
    for (int i=0; i<n; i++)  cin >> num[i];

    ListNode* head = BuildList(num, n);
    ListNode* ptr = head;
    while (ptr != nullptr)
    {
        cout << ptr->val << " ";
        ptr = ptr->next;
    }
    cout << endl;

    ListNode* head_new = removeKthFromEnd(head, k);
    ptr = head_new;
    while (ptr != nullptr)
    {
        cout << ptr->val << " ";
        ptr = ptr->next;
    }

    deleteAllNodes(head_new);
    delete []num;
    return 0;
}
