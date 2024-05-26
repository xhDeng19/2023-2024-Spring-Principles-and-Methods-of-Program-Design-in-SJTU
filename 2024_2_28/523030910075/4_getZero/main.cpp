#include <iostream>

using namespace std;

/*
* 0 <= num1, num2 <= 10^5.
* num1 -= num2 if num1 >= num2; num2 -= num1 if otherwise.
* Returns the operands that makes num1 = 0 or num2 = 0.
*/
int main()
{
    int num1, num2, operands = 0;
    cin >> num1 >> num2;

    while(num1 != 0 && num2 != 0) {
        if (num1 >= num2) {
            operands += num1 / num2;
            num1 = num1 % num2;
        } else {
            operands += num2 / num1;
            num2 = num2 % num1;
        }
    }

    cout << operands << endl;
    return 0;
}
