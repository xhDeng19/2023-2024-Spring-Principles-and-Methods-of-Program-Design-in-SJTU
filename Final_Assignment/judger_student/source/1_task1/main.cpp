#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"

using namespace std;

int main()
{
    Vector<Unit*> units;
    Field* f = loadMap(cin);

    if (f == NULL) {
        cout << "Failed to load map!" << endl;
        return -1;
    }

    // Just print the field
    cout << *f << endl;
    //play(*f, ifs, ofs);
    //play(*f, cin, cout, units);

    delete f;
    for (int i = 0; i < units.size(); i++) {delete units[i];}

    return 0;
}
