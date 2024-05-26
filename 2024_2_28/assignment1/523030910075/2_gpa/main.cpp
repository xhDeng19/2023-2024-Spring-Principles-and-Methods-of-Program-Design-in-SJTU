#include <iostream>
#include <iomanip>

using namespace std;

/*
* Input the number of courses n,
* 0 < n < 100.
* Input n examination results and credits of the course.
* Use the GPA calculation rule in SJTU to output the mean GPA.
*/
int main()
{
    int courseNum; //courseNum = n
    double totalGPA = 0.0, totalCredit = 0.0, totalGrade = 0.0, credit, grade, gradePoint;

    cin >> courseNum;

    for (int i = 0; i < courseNum; i++) {
        cin >> grade >> credit;

        switch (int(grade / 5)) {
        case 20:
        case 19:
            gradePoint = 4.3;
            break;
        case 18:
            gradePoint = 4.0;
            break;
        case 17:
            gradePoint = 3.7;
            break;
        case 16:
            gradePoint = 3.3;
            break;
        case 15:
            gradePoint = 3.0;
            break;
        case 14:
            gradePoint = 2.7;
            break;
        default:
            if (grade >= 67) {
                gradePoint = 2.3;
            } else if (grade >= 65) {
                gradePoint = 2.0;
            } else if (grade >= 62) {
                gradePoint = 1.7;
            } else if (grade >= 60) {
                gradePoint = 1.0;
            }
        }

        totalCredit += credit;
        totalGrade += credit * gradePoint;
    }

    totalGPA = totalGrade / totalCredit;

    cout << fixed << setprecision(6) << totalGPA << endl;
    return 0;
}
