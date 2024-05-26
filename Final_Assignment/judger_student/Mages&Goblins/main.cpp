#include <iostream>
#include <fstream>
#include "field.h"
#include "units.h"
#include "engine.h"

using namespace std;

int main()
{
    // map loading with TXT begins
    string filename = "map.txt";
    ifstream ifs;
    ifs.open(filename.c_str());
    if (!ifs) {
        cout << "Cannot open the file: " << filename << endl;
        return -1;
    }
    // map loading with TXT ends

    Vector<Unit*> units;
    Field* f = loadMap(ifs, units);

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
