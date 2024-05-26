#include <iostream>
#include <algorithm>
using namespace std;
const size_t MAX_SIZE = 102;

/*
* Initialize the model array.
* Record the total number of blocks and the adjacent area in z axis.
*/
void model_init(int (&model)[MAX_SIZE][MAX_SIZE], const int& n, const int& m, int& totalNum, int& adjacentNum)
{
    int temp;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
           cin >> temp;
           model[i][j] = temp;
           totalNum += temp;
           adjacentNum += temp - 1; // z axis adjacent
        }
    }
}

/*
* Record the adjacent area in x and y axis.
*/
void adjacent_num(int (&model)[MAX_SIZE][MAX_SIZE], const int& n, const int& m, int& adjacentNum)
{
    for(int i = 0; i < m - 1; i++) // row 0
    {
        adjacentNum += min(model[0][i], model[0][i + 1]);
    }

    for (int row = 1; row < n; row++) // row 1 to row n
    {
        for (int col = 0; col < m - 1; col++)
        {
            adjacentNum += min(model[row][col], model[row][col + 1]); // row adjacent
            adjacentNum += min(model[row][col], model[row - 1][col]); // column adjacent
        }
        adjacentNum += min(model[row][m - 1], model[row - 1][m - 1]);
    }
}


/*
* This program determines the surface area of a given 3D model,
* which is contributed by 1 * 1 * 1 blocks.
*/
int main()
{
    int model[MAX_SIZE][MAX_SIZE] = {};
    int n, m, totalNum = 0, adjacentNum = 0, ans;
    cin >> n >> m;

    model_init(model, n, m, totalNum, adjacentNum);

    adjacent_num(model, n, m, adjacentNum);

    ans = totalNum * 6 - adjacentNum * 2;
    cout << ans << endl;
    return 0;
}
