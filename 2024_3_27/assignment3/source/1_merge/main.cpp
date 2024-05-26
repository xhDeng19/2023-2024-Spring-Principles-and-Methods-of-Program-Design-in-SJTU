#include <iostream>
#include <vector.h>

using namespace std;

/*
* Initialize vectors from input stream.
*/
void initializer_vec(Vector<int>& vec, int sizeVec)
{
    int res;
    for (int i = 0; i < sizeVec; i++)
    {
        cin >> res;
        vec.add(res);
    }
}

/*
* Merge two ascending ordered vectors into one ascending ordered vector and return.
*/
Vector<int> mergeOrdPairs(Vector<int>& vec1, int sizeVec1, Vector<int>& vec2, int sizeVec2)
{
    Vector<int> result;
    int i = 0, j = 0;
    bool outBoundsVec1, outBoundsVec2;

    while(true)
    {
        outBoundsVec1 = (i >= sizeVec1);
        outBoundsVec2 = (j >= sizeVec2);

        if (outBoundsVec1)
        {
            while (j < sizeVec2)
            {
                result.add(vec2[j]);
                j++;
            }
            break;
        }
        else if (outBoundsVec2)
        {
            while (i < sizeVec1)
            {
                result.add(vec1[i]);
                i++;
            }
            break;
        }


        if (vec1[i] <= vec2[j])
        {
            result.add(vec1[i]);
            i++;
        }
        else if (vec1[i] > vec2[j])
        {
            result.add(vec2[j]);
            j++;
        }
    }

    return result;
}


/*
* This program merges two ascending ordered integer arrays,
* got from input stream,
* into one ascending ordered integer array and output it.
*/
int main()
{
    int n, m, sizeRes;
    cin >> n >> m;
    Vector<int> vec1, vec2, result;

    initializer_vec(vec1, n);
    initializer_vec(vec2, m);

    result = mergeOrdPairs(vec1, n, vec2, m);
    sizeRes = result.size();

    for (int i = 0; i < sizeRes - 1; i++)
    {
        cout << result[i] << " ";
    }
    cout << result[sizeRes - 1] << endl;

    return 0;
}
