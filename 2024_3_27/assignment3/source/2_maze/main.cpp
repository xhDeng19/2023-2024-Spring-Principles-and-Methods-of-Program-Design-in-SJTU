#include <iostream>
#include <vector.h>
#include <Queue.h>

using namespace std;
typedef Vector<Vector<bool>> BoolMap;

/*
* Check whether it is a passage or a wall.
* Return true if it is a passage.
*/
bool isPassage(char temp)
{
    return temp == '.';
}

/*
* Initialize the given start point in a vector in the order of row and column.
*/
void initStartPoint(Vector<int>& startPoint, int n)
{
    n *= 2;
    int temp;
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        startPoint.add(temp);
    }
}

/*
* Initialize the given grid and add a fence around it.
*/
void initGrid(BoolMap& grid, const int& row, const int& col)
{
    char temp;
    for (int r = 1; r <= row; r++)
    {
        for (int c = 1; c <= col; c++)
        {
            cin >> temp;
            grid[r][c] = isPassage(temp);
        }
    }
}

/*
* Breadth First Searching using queue and check whether there is a path from start point
* to end point (lower right corner).
*/
void BFS(BoolMap& grid, const int& row, const int& col, Vector<int>& startPoint, const int& k)
{
    int startR, startC, startNum = k * 2, pointR, pointC;
    bool isReachable;
    BoolMap grid_temp = grid;
    Queue<int> point;
    Vector<int> adjacentR = {-1, 0, 1, 0}, adjacentC = {0, 1, 0, -1}; // up, right, down, left

    for (int i = 0; i < startNum; i += 2)
    {
        isReachable = false;
        grid = grid_temp;
        point.clear();

        startR = startPoint[i] + 1;
        startC = startPoint[i + 1] + 1;

        point.enqueue(startR);
        point.enqueue(startC);

        if (!grid[startR][startC])
        {
            cout << "unreachable" << endl;
            continue;
        }
        else
            grid[startR][startC] = false;

        while(!point.isEmpty())
        {
            pointR = point.dequeue();
            pointC = point.dequeue();

            if (pointR == row && pointC == col) // reach the exit
            {
                isReachable = true;
                break;
            }

            for (int i = 0; i < 4; i++) // adjacent point
            {
                if (grid[pointR + adjacentR[i]][pointC + adjacentC[i]])
                {
                    point.enqueue(pointR + adjacentR[i]);
                    point.enqueue(pointC + adjacentC[i]);

                    grid[pointR + adjacentR[i]][pointC + adjacentC[i]] = false;

                }
            }

        }

        if (isReachable)
            cout << "reachable" << endl;
        else
            cout << "unreachable" << endl;
    }
}

/*
* This program checks whether there is a path from n given start point
* to a given grid's lower right corner.
*/
int main(){
    Vector<int> startPoint;
    int row, col, k;
    cin >> row >> col >> k;
    BoolMap grid(row + 2, Vector<bool>(col + 2, false));

    initStartPoint(startPoint, k);
    initGrid(grid, row, col);

    BFS(grid, row, col, startPoint, k);

    return 0;
}
