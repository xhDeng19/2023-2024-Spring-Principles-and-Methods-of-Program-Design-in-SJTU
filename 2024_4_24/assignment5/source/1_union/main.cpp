# include <iostream>
# include <sstream>
# include <iomanip>
# include <stack.h>
# include <Map.h>

using namespace std;

// global variables
const int N = 100;
int pc = 1, i_temp;
double d_temp;
char c_temp;
enum Operation {AddL, AddR, SubL, SubR, Assign, Var, Jmp, JmpEq, JmpGt, JmpLt, Const, Print, Halt};
struct Command{
    Operation type;
    union {
        int i;
        double d;
        char c;
    } value;
}cmd[N];
Stack<double> stackMachine; // the main stack
Map<string, double> state; // the state

/*
* Output "Error" and quit when pop empty stack.
*/
void Error()
{
    cout << "Error" << endl;
    exit(0);
}

/*
* Initialize the struct Command cmd[N].
*/
void decodeCommand(const string& com, const int& i)
{
    string commandType;
    istringstream iss(com);
    iss >> commandType;

    if (commandType == "AddL")
    {
        cmd[i].type = AddL;
    }
    else if (commandType == "AddR")
    {
        cmd[i].type = AddR;
        iss >> d_temp;
        cmd[i].value.d = d_temp;
    }
    else if (commandType == "SubL")
    {
        cmd[i].type = SubL;
    }
    else if (commandType == "SubR")
    {
        cmd[i].type = SubR;
        iss >> d_temp;
        cmd[i].value.d = d_temp;
    }
    else if (commandType == "Assign")
    {
        cmd[i].type = Assign;
        iss >> c_temp;
        cmd[i].value.c = c_temp;
    }
    else if (commandType == "Var")
    {
        cmd[i].type = Var;
        iss >> c_temp;
        cmd[i].value.c = c_temp;
    }
    else if (commandType == "Jmp")
    {
        cmd[i].type = Jmp;
        iss >> i_temp;
        cmd[i].value.i = i_temp + 1;
    }
    else if (commandType == "JmpEq")
    {
        cmd[i].type = JmpEq;
        iss >> i_temp;
        cmd[i].value.i = i_temp + 1;
    }
    else if (commandType == "JmpGt")
    {
        cmd[i].type = JmpGt;
        iss >> i_temp;
        cmd[i].value.i = i_temp + 1;
    }
    else if (commandType == "JmpLt")
    {
        cmd[i].type = JmpLt;
        iss >> i_temp;
        cmd[i].value.i = i_temp + 1;
    }
    else if (commandType == "Const")
    {
        cmd[i].type = Const;
        iss >> d_temp;
        cmd[i].value.d = d_temp;
    }
    else if (commandType == "Print")
    {
        cmd[i].type = Print;
        iss >> c_temp;
        cmd[i].value.c = c_temp;
    }
}

/*
* Run the Command.
*/
void runCommand(const int& totalOp)
{
    double value1, value2;
    while(pc < totalOp)
    {
        switch (cmd[pc].type)
        {
        case AddL:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();

                if (!stackMachine.isEmpty())
                    value2 = stackMachine.pop();
                else
                    Error();
            }
            else
                Error();

            stackMachine.push(value1 + value2);
            pc++;
            break;

        case AddR:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();
                stackMachine.push(value1 + cmd[pc].value.d);
            }
            else
                Error();
            pc++;
            break;

        case SubL:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();

                if (!stackMachine.isEmpty())
                    value2 = stackMachine.pop();
                else
                    Error();
            }
            else
                Error();

            stackMachine.push(value2 - value1);
            pc++;
            break;

        case SubR:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();
                stackMachine.push(value1 - cmd[pc].value.d);
            }
            else
                Error();
            pc++;
            break;

        case Assign:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();
                state.put(&cmd[pc].value.c, value1);
            }
            else
                Error();
            pc++;
            break;

        case Var:
            if (state.containsKey(&cmd[pc].value.c))
            {
                value1 = state.get(&cmd[pc].value.c);
                stackMachine.push(value1);
            }
            else
                Error();
            pc++;
            break;

        case Jmp:
            pc = cmd[pc].value.i;
            break;

        case JmpEq:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();

                if (!stackMachine.isEmpty())
                    value2 = stackMachine.pop();
                else
                    Error();
            }
            else
                Error();

            if (value1 == value2)
                pc = cmd[pc].value.i;
            else
                pc++;
            break;

        case JmpGt:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();

                if (!stackMachine.isEmpty())
                    value2 = stackMachine.pop();
                else
                    Error();
            }
            else
                Error();

            if (value1 < value2)
                pc = cmd[pc].value.i;
            else
                pc++;
            break;

        case JmpLt:
            if (!stackMachine.isEmpty())
            {
                value1 = stackMachine.pop();

                if (!stackMachine.isEmpty())
                    value2 = stackMachine.pop();
                else
                    Error();
            }
            else
                Error();

            if (value1 > value2)
                pc = cmd[pc].value.i;
            else
                pc++;
            break;

        case Const:
            stackMachine.push(cmd[pc].value.d);
            pc++;
            break;

        case Print:
            cout << fixed << setprecision(2) << state.get(&cmd[pc].value.c) << endl;
            pc++;
            break;

        case Halt:
            break;
        }
    }
}

/*
* This program simulates the operation of a simple
* "ASM"(Assembly) language  virtual machine, which
* is a stack machine.
* Elements' type is double.
*/
int main()
{
    // Todo: First read all the commands into cmd[N];
    // Then use pc as a subscript in cmd.
    int totalOp;
    string com;
    cin >> totalOp;

    for (int i = 0; i < totalOp; i++)
    {
        getline(cin, com);
        decodeCommand(com, i);
    }
    cin >> com; // Halt

    runCommand(totalOp);

    return 0;
}
