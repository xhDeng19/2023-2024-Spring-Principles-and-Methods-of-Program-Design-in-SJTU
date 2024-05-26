#include "units.h"
#include "field.h"
#include <cassert>
using namespace std;

/* Unit */

// Constructor
Unit::Unit(bool sd, int row, int col)
    : side(sd), row(row), col(col)
{

}


// Get the side
bool Unit::getSide() const
{
    return side;
}

// Get and set the row[col] of a unit
int Unit::getRow() const
{
    return row;
}

int Unit::getCol() const
{
    return col;
}

void Unit::setRow(int r)
{
    row = r;
}

void Unit::setCol(int c)
{
    col = c;
}

// Get the symbol of the unit
string getUnitSymbol(const Unit& u)
{
    bool side = u.getSide();
    if (side){
        return "@@";
    }
    else{
        return "PG";
    }
    assert (false);
}


