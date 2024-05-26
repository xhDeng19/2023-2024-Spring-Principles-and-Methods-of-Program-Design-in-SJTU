#include <iostream>
#include <string>

using namespace std;

/*
* Transform a string in form of "yyyy/mm/dd" into an int array
* whose first number is  the year, the second is the month, and the third is the day.
* Use reference to send the int array out.
*/
void getDay(string date, int (&num)[3])
{
    int posBegin = 0, posEnd;
    for (int i = 0; i < 2; i++)
    {
        posEnd = date.find("/", posBegin);
        num[i] = stoi(date.substr(posBegin, posEnd - posBegin));
        posBegin = posEnd + 1;
    }
    num[2] = stoi(date.substr(posBegin));
}

/*
* Examine whether a given year is a leap year.
* Returns 1 if it is a leap year, 0 otherwise.
*/
bool isLeap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*
* Returns the exact number of days in a given month considering leap years.
*/
int daysInMonth(int month, bool dayInLeap)
{
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        return 31;
    }
    else if (month == 2)
    {
        return 28 + dayInLeap;
    }
    else
    {
        return 30;
    }
}

/*
* Calculates the days difference between two dates in int arrays.
* Int array: {year, month, day}.
*/
int daysDifference(int day1[3], int day2[3])
{
    int result = 0, preDays1 = 0, preDays2 = 0;
    for (int i = day1[0]; i < day2[0]; i++)
        result += 365 + isLeap(i);

    for (int i = 1; i < day1[1]; i++)
        preDays1 += daysInMonth(i, isLeap(day1[0]));

    for (int i = 1; i < day2[1]; i++)
        preDays2 += daysInMonth(i, isLeap(day2[0]));

    result += - (preDays1 + day1[2]) + preDays2 + day2[2];
    return result;
}

/*
* This program calculates the days difference between two given dates in form of "yyyy/mm/dd"
* considering the existence of leap year.
*/
int main()
{
    string date1, date2;
    int day1[3], day2[3];

    getline(cin, date1);
    getline(cin, date2);

    getDay(date1, day1);
    getDay(date2, day2);

    if (day1[0] >= day2[0] && day1[1] >= day2[1] && day1[3] >= day2[3])
        cout << 0 << endl;
    else
        cout << daysDifference(day1, day2) << endl;

    return 0;
}
