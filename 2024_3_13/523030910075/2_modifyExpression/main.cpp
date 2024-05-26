#include <iostream>
#include <cmath>

using namespace std;

/*
* Transform the given string expression in form of "a+b" into int a, int b
* and their lengths.
*/
void expToNums(string exp, int & num1, int & num2, int & numLen1, int & numLen2)
{
    int pos = exp.find("+");
    string str1, str2;
    str1 = exp.substr(0, pos);
    str2 = exp.substr(pos + 1, exp.length());

    numLen1 = str1.length();
    numLen2 = str2.length();
    num1 = stoi(str1);
    num2 = stoi(str2);
}

/*
* Determines the positions of a pair of parentheses to ensure the answer
* calculated is as close as possible to a given int tgt.
* Output the string expression with parentheses.
*/
void pairsPos(int num1, int num2, int numLen1, int numLen2, int tgt, string exp)
{
    int res, ans, imin, jmin, ansMin = -1;
    int left, midl, midr, right;
    for (int i = 1; i <= numLen1; i++)
    {
        for (int j = numLen2 - 1; j >= 0; j--)
        {
            left = num1 / int(pow(10, i));
            midl = num1 % int(pow(10, i));
            midr = num2 / int(pow(10, j));
            right = num2 % int(pow(10, j));

            if (left == 0)
                left += 1;
            if (right == 0)
                right += 1;

            res = left * (midl + midr) * right;
            ans = abs(res - tgt);
            if (ans < ansMin || ansMin == -1)
            {
                imin = i;
                jmin = j;
                ansMin = ans;
            }
        }
    }
    exp.insert(numLen1 - imin, "(");
    exp.insert(numLen1 + numLen2 + 2 - jmin, ")");

    cout << exp << endl;
}

/*
* This program determines the position of a pair of parentheses in an addition formula
* so that the result of it is as close as possible to a correct answer given.
*/
int main()
{
    string exp;
    int num1, num2, numLen1, numLen2, tgt;
    getline(cin, exp);
    cin >> tgt;

    expToNums(exp, num1, num2, numLen1, numLen2);
    pairsPos(num1, num2, numLen1, numLen2, tgt, exp);

    return 0;
}
