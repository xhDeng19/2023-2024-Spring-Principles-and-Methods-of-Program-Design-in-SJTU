#include <iostream>
#include <cmath> // Use pow function

using namespace std;

/*
* Encrypt a 12-digit school number(schoolNum):
* for every digit, output its unit's digit after adding 3.
*/
int main()
{
    long long int schoolNum, encryptNum = 0;
    int digit, encryptDigit;

    cin >> schoolNum;

    for (int i = 0; i < 12; i++) {
        digit = schoolNum % 10;
        encryptDigit = (digit + 3) % 10;
        encryptNum += encryptDigit * pow(10, i);

        schoolNum /= 10;
    }

    cout << encryptNum << endl;
    return 0;
}
