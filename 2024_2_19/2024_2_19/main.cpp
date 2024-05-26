#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    string line, op, op1;
    getline(cin, line);
    istringstream iss(line);
    int i = 0;

    iss >> op;
    while(iss)
    {
        cout << op << endl;

        iss >> op;
    }

    return 0;
}


