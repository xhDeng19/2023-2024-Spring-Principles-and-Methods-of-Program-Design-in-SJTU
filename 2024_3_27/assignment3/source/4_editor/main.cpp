#include <iostream>
#include <sstream>
#include <string>
#include <vector.h>

using namespace std;

// global variables
Vector<int> cursor_record = {1, 0};
Vector<bool> redoable_record = {false}, undoable_record = {false};
Vector<string> text = {""};
Vector<Vector<string>> record = {{""}};
int cursor[2] = {1, 0};
int operands, currentOp = 1, value1, value2, length;
bool undoable = false, redoable = false;
string command, operation, str, line;

// function prototypes
void c(const int& r, const int& c);
void i(string& s);
void d(const int& k);
void ENT();
void u();
void r();
void p();


/*
* Insert the string s after the current cursor,
* and move the cursor to the end of s when the insertion is complete.
*/
void i(string& s)
{
    redoable = false;
    undoable = true;
    length = s.length();
    text[cursor[0] - 1].insert(cursor[1], s); // standard string.insert insert behind the position
    cursor[1] += length;

    currentOp++;
}

/*
* Wrap a line under the current cursor,
* the text behind the cursor is transferred to the new line,
* and the cursor position is moved to the beginning of the new line.
*/
void ENT()
{
    redoable = false;
    undoable = true;
    line = text[cursor[0] - 1].substr(cursor[1]);
    text[cursor[0] - 1].erase(cursor[1]);
    text.insert(cursor[0], line);
    cursor[0]++;
    cursor[1] = 0;

    currentOp++;
}

/*
* Move the cursor to the line n after the character m.
* Ignore this command if there is no such position.
*/
void c(const int& cRow, const int& cCol)
{
    redoable = false;
    if (cRow > int(text.size()))
    {
        undoable = false;
        currentOp++;
        return;
    }
    else
    {
        line = text[cRow - 1];
        if (int(line.length()) < cCol)
        {
            undoable = false;
            currentOp++;
            return;
        }
        else
        {
            undoable = true;
            cursor[0] = cRow;
            cursor[1] = cCol;
        }
    }

    currentOp++;
}

/*
* Delete min(k,m) characters from the current cursor,
* and move the cursor to the beginning of the deleted string.
*/
void d(const int& k)
{
    redoable = false;
    undoable = true;
    int start;
    if (k > cursor[1])
    {
        start = 0;
        length = cursor[1];
    }
    else
    {
        start = cursor[1] - k;
        length = k;
    }
    text[cursor[0] - 1].erase(start, length);
    cursor[1] = start;

    currentOp++;
}

/*
* Print the text content of the current editor, then print a newline
* (this instruction cannot be undone).
*/
void p()
{
    redoable = false;
    undoable = false;
    for (int i = 0; i < int(text.size()); i++)
    {
        cout << text[i] << endl;
    }

    currentOp++;
}

/*
* Cancel the last operation that can be undone.
* If there is no such operation, the command is ignored.
*/
void u()
{
    for (int i = currentOp - 1; i >= 0; i--)
    {
        if (undoable_record[i])
        {
            text = record[i - 1];
            cursor[0] = cursor_record[(i - 1) * 2];
            cursor[1] = cursor_record[(i - 1) * 2 + 1];
            undoable_record[i] = false;
            break;
        }
    }
    currentOp++;

    undoable = false;
    redoable = true;
}

/*
* Reverse the undo operation that is not redone before.
* If there is no such undo operation, this operation is ignored
*/
void r()
{
    for (int i = currentOp - 1; i >= 0; i--)
    {
        if (redoable_record[i])
        {
            text = record[i - 1];
            cursor[0] = cursor_record[(i - 1) * 2];
            cursor[1] = cursor_record[(i - 1) * 2 + 1];
            redoable_record[i] = false;
            break;
        }
    }
    currentOp++;

    undoable = true;
    redoable = false;
}

/*
* This program simulates the text editor,
* which stores the text and records the position of the current cursor
*/
int main(){
    cin >> operands;
    string totalCom[operands + 1];

    for (int i = 0; i <= operands; i++)
        getline(cin, totalCom[i]);

    while(currentOp <= operands)
    {
        command = totalCom[currentOp];
        istringstream iss(command);
        iss >> operation;

        if (operation == "c")
        {
            iss >> value1 >> value2;
            c(value1, value2);
        }
        else if (operation == "i")
        {
            str = command.substr(2);
            i(str);
        }
        else if (operation == "d")
        {
            iss >> value1;
            d(value1);
        }
        else if (operation == "ENT")
            ENT();
        else if (operation == "u")
            u();
        else if (operation == "r")
            r();
        else if (operation == "p")
            p();

        record.add(text);
        redoable_record.add(redoable);
        undoable_record.add(undoable);
        cursor_record.add(cursor[0]);
        cursor_record.add(cursor[1]);
    }

    return 0;
}
