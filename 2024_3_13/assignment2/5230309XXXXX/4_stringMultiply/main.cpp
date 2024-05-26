#include <iostream>

using namespace std;

/*
* Transform alphabets into integers, 'a'-'z' are represented by 0-25.
*/
int atoi(char chr)
{
    return chr - 'a';
}

/*
* Transform integers into alphabets, 0-25 represent 'a'-'z'.
*/
char itoa(int num)
{
    return num + 'a';
}

/*
* Multiplication of two alphabetic strings using base 26.
* Output the answer in form of alphabetic strings.
*/
void alphabetMul(string str1, string str2)
{
    int strLen1 = str1.length(), strLen2 = str2.length();
    int intermediate[strLen1 + strLen2] = {};
    int carry = 0, ansMid = 0;
    bool preZero = true;

    for (int i = strLen1 - 1; i >= 0; i--)
    {
        for (int j = strLen2 - 1; j >= 0; j--)
        {
            ansMid = intermediate[i + j + 1] + atoi(str1[i]) * atoi(str2[j]) + carry;
            intermediate[i + j + 1] = ansMid % 26;
            carry = ansMid / 26;
        }
        if (carry != 0)
            intermediate[i] += carry;
        carry = 0;
    }

    for (int i = 0; i < strLen1 + strLen2 - 1; i++)
    {
        if (preZero && intermediate[i] == 0)
            continue;

        preZero = false;
        cout << itoa(intermediate[i]);
    }
    cout << itoa(intermediate[strLen1 + strLen2 - 1]);
}


/*
* This program uses base 26 multiplying two alphabetic strings, where
* 'a'-'z' is represented by 0-25.
*/
int main()
{
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);

    alphabetMul(str1, str2);
    return 0;
}
