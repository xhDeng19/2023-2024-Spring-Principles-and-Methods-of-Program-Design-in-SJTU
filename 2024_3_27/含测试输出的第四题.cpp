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
*
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
*
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
*
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
*
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
*
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
*
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
*
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
*
*/
int main(){
    cin >> operands;
    string totalCom[operands + 1];

    for (int i = 0; i <= operands; i++)
    {
        getline(cin, totalCom[i]);
    }

    //for (int i = 0; i <= operands; i++)
    //    cout << "command " << i << ": " << totalCom[i] << endl;

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
        {
            ENT();
        }
        else if (operation == "u")
        {
            u();
        }
        else if (operation == "r")
        {
            r();
        }
        else if (operation == "p")
        {
            p();
        }
        //cout << currentOp - 1<< " turn" << endl;
        //cout << command << " command" << endl;
        //cout << currentOp << " currentOp" << endl;
        //cout << "text: " << text << endl;
        //cout << "cursor: " << cursor[0] << " " << cursor[1] << "\n" << endl;
        record.add(text);
        redoable_record.add(redoable);
        undoable_record.add(undoable);
        cursor_record.add(cursor[0]);
        cursor_record.add(cursor[1]);

        //cout << record << endl;
        //cout << undoable_record << endl;
        //cout << redoable_record << endl;
    }

    return 0;
}
