#include <iostream>
#include <sstream>
#include <string>
#include <stack.h>
#include <Map.h>

using namespace std;

// global variables
Stack<int> stackMachine; // the main stack
Map<string, int> state; // the state
int Operands; // the program counter(pc)
int currentOp = 1, value;
string command, operation, name;


// function prototypes
void Add();
void Sub();
void Mul();
void Div();
void Assign(string& name);
void Var(string& name);
void Jmp(const int& Op);
void JmpEq(const int& Op);
void JmpGt(const int& Op);
void JmpLt(const int& Op);
void Const(const int& n);
void Print(string& name);
void Halt();
void Error();


/*
* Output "Error" and quit when encountered
* division by zero,
* pc jumping outside the program,
* operands missing,
* and outputing undefined variables.
*/
void Error()
{
    cout << "Error" << endl;
    exit(0);
}

/*
* Push integer "n" into the main stack.
*/
void Const(const int& n)
{
    stackMachine.push(n);
    currentOp++;
}

/*
* Pop an integer "value" out of the main stack
* and map "name" into "value" in the state.
*/
void Assign(string& name)
{
    value = stackMachine.pop();
    state.put(name, value);
    currentOp++;
}

/*
* Jump to line "Op".
*/
void Jmp(const int& Op)
{
    if (Op <= Operands)
        currentOp = Op;
    else
        Error();
}

/*
* Push the value of "name" in state into
* the main stack.
*/
void Var(string& name)
{
    if (state.containsKey(name))
    {
        value = state.get(name);
        stackMachine.push(value);
    }
    else
        Error();

    currentOp++;
}

/*
* Jump to line "Op" if the top two elements
* in the main stack are the same.
* Remove these two elements from the main stack.
*/
void JmpEq(const int& Op)
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    if(value1 == value2)
        Jmp(Op);
    else
        currentOp++;
}


/*
* Jump to line "Op" if the second element is
* greater than the first element in top of
* the main stack.
* Remove these two elements from the main stack.
*/
void JmpGt(const int& Op)
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    if(value2 > value1)
        Jmp(Op);
    else
        currentOp++;
}

/*
* Jump to line "Op" if the second element is
* less than the first element in top of
* the main stack.
* Remove these two elements from the main stack.
*/
void JmpLt(const int& Op)
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    if(value2 < value1)
        Jmp(Op);
    else
        currentOp++;
}

/*
* Pop two elements from the top of the main stack and
* push their addition into the stack.
*/
void Add()
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    value = value1 + value2;
    stackMachine.push(value);

    currentOp++;
}

/*
* Pop the first top element "value1" and the second
* top element "value2" from the main stack and
* push value2 - value1 into the stack.
*/
void Sub()
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    value = value2 - value1;
    stackMachine.push(value);

    currentOp++;
}

/*
* Pop the first top element "value1" and the second
* top element "value2" from the main stack and
* push value2 / value1 into the stack.
*/
void Div()
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    if (value1 == 0)
        Error();
    else
    {
        value = value2 / value1;
        stackMachine.push(value);
    }

    currentOp++;
}

/*
* Pop two elements from the top of the main stack and
* push their product into the stack.
*/
void Mul()
{
    int value1, value2;
    value1 = stackMachine.pop();
    value2 = stackMachine.pop();

    value = value1 * value2;
    stackMachine.push(value);

    currentOp++;
}

/*
* Output the value of "name" and wrap around.
*/
void Print(string& name)
{
    if (state.containsKey(name))
    {
        value = state.get(name);
        cout << value << endl;
    }
    else
        Error();

    currentOp++;
}

/*
* Quit the program.
*/
void Halt()
{
    if (currentOp != Operands)
        Error();
}

/*
* This program simulates the operation of a simple
* "ASM"(Assembly) language  virtual machine, which
* is a stack machine.
*/
int main(){
    cin >> Operands; // the total number of operation
    string totalCom[Operands + 1];
    for (int i = 0; i <= Operands; i++)
        getline(cin, totalCom[i]);

    while(true) // realize each command
    {
        if (currentOp > Operands) // overoperate
            Error();

        command = totalCom[currentOp];

        istringstream iss(command);
        iss >> operation;

        if (operation == "Add")
            Add();
        else if (operation == "Sub")
            Sub();
        else if (operation == "Mul")
            Mul();
        else if (operation == "Div")
            Div();
        else if (operation == "Assign")
        {
            iss >> name;
            Assign(name);
        }
        else if (operation == "Var")
        {
            iss >> name;
            Var(name);
        }
        else if (operation == "Jmp")
        {
            iss >> value;
            value++; // This program sets the initial operands "currentOp" to 1.
            Jmp(value);
        }
        else if (operation == "JmpEq")
        {
            iss >> value;
            value++;
            JmpEq(value);
        }
        else if (operation == "JmpGt")
        {
            iss >> value;
            value++;
            JmpGt(value);
        }
        else if (operation == "JmpLt")
        {
            iss >> value;
            value++;
            JmpLt(value);
        }
        else if (operation == "Const")
        {
            iss >> value;
            Const(value);
        }
        else if (operation == "Print")
        {
            iss >> name;
            Print(name);
        }
        else if (operation == "Halt")
        {
            Halt();
            return 0;
        }
        else
            Error(); // invalid input
    }

    return 0;
}

