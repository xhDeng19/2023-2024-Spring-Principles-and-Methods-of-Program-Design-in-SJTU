#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"

using namespace std;

int main()
{
    Vector<Unit*> units;
    Field* f = loadMap(cin, units);

    if (f == NULL) {
        cout << "Failed to load map!" << endl;
        return -1;
    }
    //play(*f, ifs, ofs);
    play(*f, cin, cout, units);

    delete f;
    for (int i = 0; i < units.size(); i++) {delete units[i];}

    return 0;
}
