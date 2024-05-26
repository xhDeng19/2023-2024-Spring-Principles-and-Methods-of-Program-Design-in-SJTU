#include <iostream>

using namespace std;

/*
* 0 < n < 1000000.
* Output numbers from 1 to n(1 and n are inclusive).
* Output "Fizz" instead of numbers if they are divisible by 3.
* Output "Buzz" instead of numbers if they are divisible by 5.
* Output "FizzBuzz" instead of numbers if they are divisible by 3 and 5.
*/
int main()
{
    int maxNum; //maxNum = n

    cin >> maxNum;

    for (int i = 1; i <= maxNum; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz ";
        } else if (i % 3 == 0) {
            cout << "Fizz ";
        } else if (i % 5 == 0) {
            cout << "Buzz ";
        } else {
            cout << i << " ";
        }
    }

    return 0;
}
