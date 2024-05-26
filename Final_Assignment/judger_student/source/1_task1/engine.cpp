#include <sstream>
#include <iomanip>
#include <cassert>
#include <Queue.h>
#include "engine.h"
#include "units.h"
#include "vector.h"
#include "Stack.h"
#include "algorithms.h"
using namespace std;

// Convert the string input "M" and "W" to enumerate type
// Return false if the input is invalid
bool get_terrain_symbol_from_input(const string& t_input, Terrain& t)
{
    if (t_input == "M")
    {
        t = MOUNTAIN;
        return true;
    }
    else if (t_input == "W")
    {
        t = WATER;
        return true;
    }
    return false;
}

// Load map and units
Field* loadMap(istream& is)
{
    int M = 11, N = 11, NT = 0, NM = 0, NG = 0;
    is >> M >> N >> NT >> NM >> NG;

    Field* f = new Field(M, N);

    // Initialize the terrain
    for (int i = 0; i < NT; i++)
    {
        int tRow = 0, tCol = 0;
        string t_input;
        Terrain t;

        is >> tRow >> tCol >> t_input;

        // Check boundary and the input
        if (!get_terrain_symbol_from_input(t_input, t) || !f->inBounds(tRow, tCol))
            assert (false);

        f->setTerrain(tRow, tCol, t);
    }

    // Initialize the mages
    for (int i = 0; i < NM; i++)
    {
        int mRow = 0, mCol = 0;
        is >> mRow >> mCol;

        // Check boundary
        if (!f->inBounds(mRow, mCol))
            assert (false);

        Unit* mage = new Unit(true, mRow, mCol);
        f->setUnit(mRow, mCol, mage);
    }

    // Initialize the goblins
    for (int i = 0; i < NG; i++)
    {
        int gRow = 0, gCol = 0;
        string gType;
        is >> gRow >> gCol >> gType;

        // Check boundary and the input
        // NOT initialize the tracking goblins!
        if (!(f->inBounds(gRow, gCol) && (gType == "TG" || gType == "PG")))
           assert (false);

        Unit* goblin = new Unit(false, gRow, gCol);
        f->setUnit(gRow, gCol, goblin);
    }

    return f;
}


// Main loop for playing the game
void play(Field& field, istream& is, ostream& os)
{

    int numTurns = 1;

    while (is)
    {
        os << "Turn " << numTurns << " begins:" << endl;
        // Print the new map
        os << field << endl;

        // Check winning
        // Fill in your code here

        // unit moves
        // Fill in your code here

        // Preventing loop in empty program
		// Please delete this 2 lines of code
        string line;
        getline(is,line);

        numTurns++;
    }
}


