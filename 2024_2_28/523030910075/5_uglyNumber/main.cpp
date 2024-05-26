#include <iostream>

using namespace std;

/*
* Determine the positive integers that contain only prime factors 2, 3 and 5.
*/
int main()
{
    int num, factor[3] = {2, 3, 5}, originalNum;
    cin >> num;

    originalNum = num; // Use originalNum to determine the case of 1
    for (int i = 0; i < 3; i++) {
        while (num % factor[i] == 0) {
            num /= factor[i];
        }
    }

    if (num == 1 && originalNum != 1) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
