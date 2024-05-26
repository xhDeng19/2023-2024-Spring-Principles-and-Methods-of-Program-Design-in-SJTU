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

// Get and set the type of a goblin
GoblinType Unit::getGobType() const
{
    return gType;
}

void Unit::setGobType(string type_str)
{
    if (type_str == "PG")
        gType = Patrol;
    else if (type_str == "TG")
        gType = Tracking;
}

// Get and set the direction of a goblin
Direction Unit::getGobDir() const
{
    return gDir;
}

void Unit::setGobDir(Direction dir_pg)
{
    gDir = dir_pg;
}

// Get and set the action points of a PG
int Unit::getAP() const
{
    return ap;
}

void Unit::setAP(int ap_pg)
{
    ap = ap_pg;
}

// Get and set the field of view of a TG
int Unit::getFOV() const
{
    return fov;
}

void Unit::setFOV(int fov_tg)
{
    fov = fov_tg;
}

// Get the symbol of the unit
string getUnitSymbol(const Unit& u)
{
    bool side = u.getSide();
    GoblinType gType = u.getGobType();
    if (side){
        return "@@";
    }
    else{
        if (gType == Patrol)
            return "PG";
        else if (gType == Tracking)
            return "TG";
    }
    assert (false);
}


