# include <iostream>
# include <sstream>
using namespace std;

int s, n, m;
// Use linked list to store memory information.
struct LinkedMemory
{
    int task, Start, len, End;
    LinkedMemory* next;
};

/*
* Assign informations(task index, start point, length, end point)
* to a linked list, and return the linked list.
*/
LinkedMemory* assignMemory(int task, int Start, int len)
{
    LinkedMemory* newM = new LinkedMemory;
    newM->task = task;
    newM->Start = Start;
    newM->len = len;
    newM->End = Start + len;
    newM->next = nullptr;
    return newM;
}

/*
* Allocate a block of memory of length y from address x to task a.
* If the allocation is unsuccessful (conflicts with other occupied blocks),
* an "error" will be output and the program will continue to run.
*/
void A1(LinkedMemory** proot, int task, int Start, int len)
{
    LinkedMemory *prePtr = nullptr, *curPtr = *proot;
    while (curPtr != nullptr && curPtr->Start < Start)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
    }

    int available_start = prePtr->End, available_end = s;

    if (curPtr != nullptr)
        available_end = curPtr->Start;

    if (available_start > Start || available_end < (Start + len))
    {
        cout << "error" << endl;
        return;
    }
    else
    {
        LinkedMemory* newM = new LinkedMemory;
        newM = assignMemory(task, Start, len);
        newM->next = curPtr;
        prePtr->next = newM;
    }
}

/*
* Allocate a block of memory of length y to task a,
* using a strategy called "First".
*
* "First":
* Find a location to allocate that can accommodate the demand
* and has the smallest memory address.
*/
void A2_f(LinkedMemory** proot, int task, int len)
{
    LinkedMemory* curPtr = *proot, *prePtr = nullptr;

    while (curPtr->next != nullptr)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
        if (curPtr->Start - prePtr->End >= len)
        {
            LinkedMemory* newM = new LinkedMemory;
            newM = assignMemory(task, prePtr->End, len);
            newM->next = curPtr;
            prePtr->next = newM;
            return;
        }
    }
    if (len <= (s - curPtr->End))
    {
        LinkedMemory* newM = new LinkedMemory;
        newM = assignMemory(task, curPtr->End, len);
        newM->next = nullptr;
        curPtr->next = newM;
    }
    else
    {
        cout << "error" << endl;
        return;
    }
}

/*
* Allocate a block of memory of length y to task a,
* using a strategy called "Smallest".
*
* "Smallest":
* Find the smallest free block currently in memory,
* and start allocating from the head of that free block.
*/
void A2_s(LinkedMemory** proot, int task, int len)
{
    int min_gap = s + 1, gap;
    LinkedMemory *curPtr = *proot, *prePtr = nullptr, *min_curPtr = *proot, *min_prePtr = nullptr;
    while (curPtr->next != nullptr)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
        gap = curPtr->Start - prePtr->End;
        if (gap < min_gap && len <= gap)
        {
            min_curPtr = curPtr;
            min_prePtr = prePtr;
            min_gap = gap;
        }
    }
    if (s - curPtr->End < min_gap && len <= s - curPtr->End)
    {
        LinkedMemory* newM = new LinkedMemory;
        newM = assignMemory(task, curPtr->End, len);
        curPtr->next = newM;
        newM->next = nullptr;
        return;
    }
    else if (min_gap == s + 1)
    {
        cout << "error" << endl;
        return;
    }

    LinkedMemory* newM = new LinkedMemory;
    newM = assignMemory(task, min_prePtr->End, len);
    min_prePtr->next = newM;
    newM->next = min_curPtr;
}

/*
* Allocate a block of memory of length y to task a,
* using a strategy called "Biggest".
*
* "Biggest":
* Find the largest free block currently in memory,
* and start allocating from the head of that free block.
*/
void A2_b(LinkedMemory** proot, int task, int len)
{
    int max_gap = 0, gap;
    LinkedMemory *curPtr = *proot, *prePtr = nullptr, *max_curPtr = *proot, *max_prePtr = nullptr;
    while (curPtr->next != nullptr)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
        gap = curPtr->Start - prePtr->End;
        if (gap > max_gap && len <= gap)
        {
            max_curPtr = curPtr;
            max_prePtr = prePtr;
            max_gap = gap;
        }
    }

    if (s - curPtr->End > max_gap && len <= s - curPtr->End)
    {
        LinkedMemory* newM = new LinkedMemory;
        newM = assignMemory(task, curPtr->End, len);
        curPtr->next = newM;
        newM->next = nullptr;
        return;
    }
    else if (max_gap == 0)
    {
        cout << "error" << endl;
        return;
    }

    LinkedMemory* newM = new LinkedMemory;
    newM = assignMemory(task, max_prePtr->End, len);
    max_prePtr->next = newM;
    newM->next = max_curPtr;
}

/*
* Output the current memory status.
*/
void PrintMemory(LinkedMemory* memory)
{
    for (LinkedMemory* p = memory->next; p != nullptr; p = p->next)
        cout << p->Start << " " << p->len << " " << p->task << endl;
}

/*
* Memory compaction.
*/
void S(LinkedMemory** proot)
{
    LinkedMemory* root = *proot;
    int preEnd = root->End;
    for (LinkedMemory* p = root->next; p != nullptr; p = p->next)
    {
        p->Start = preEnd;
        p->End = p->Start + p->len;
        preEnd = p->End;
    }
}

/*
* Free all memory blocks occupied by task a.
*/
void R(LinkedMemory** proot, int task)
{
    LinkedMemory *curPtr = *proot, *prePtr = nullptr;
    while (curPtr->next != nullptr)
    {
        prePtr = curPtr;
        curPtr = curPtr->next;
        if (curPtr->task == task)
        {
            prePtr->next = curPtr->next;
            curPtr = prePtr;
        }
    }
}

/*
* Operate each input command.
*/
void RunTask()
{
    int a, x, y;
    char c;
    LinkedMemory* memory = new LinkedMemory;
    memory = assignMemory(-1, -1, 1); // dummy node
    string op_name, command;
    for (int i = -1; i < m; i++)
    {
        getline(cin, command);
        istringstream iss(command);
        iss >> op_name;

        if (op_name == "A1")
        {
            iss >> a >> x >> y;
            A1(&memory, a, x, y);
        }
        else if (op_name == "A2")
        {
            iss >> a >> y >> c;

            if (c == 'f')
                A2_f(&memory, a, y);
            else if (c == 'b')
                A2_b(&memory, a, y);
            else if (c == 's')
                A2_s(&memory, a, y);
        }
        else if (op_name == "O")
            PrintMemory(memory);
        else if (op_name == "S")
            S(&memory);
        else if (op_name == "R")
        {
            iss >> a;
            R(&memory, a);
        }
    }
}

/*
* This program simulates a simple memory model,
* and implements simple dynamic memory allocations.
*/
int main()
{
    cin >> s >> n >> m;

    RunTask();

    return 0;
}
