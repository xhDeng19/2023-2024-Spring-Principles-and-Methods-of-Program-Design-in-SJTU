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

// To ensure units vector iterate through the right sequence
// while deleting units before the current unit
int unit_i = 0;

// Reverse the direction
Direction reverse_dir(Direction dir)
{
    switch(dir)
    {
    case W:
        return S;
    case A:
        return D;
    case S:
        return W;
    case D:
        return A;
    }
}

Direction get_dir_from_input(const string& dir_input)
{
    if (dir_input == "W")
        return W;
    else if (dir_input == "A")
        return A;
    else if (dir_input == "S")
        return S;
    else if (dir_input == "D")
        return D;

    assert (false);
}

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

// Remove a unit from field and vector units
void remove_unit(Field& field, Vector<Unit*>& units, const int r, const int c)
{
    Unit* temp_units = field.getUnit(r, c);
    for (int i = 0; i < units.size(); i++)
    {
        if (units[i] == temp_units)
        {
            units.remove(i);
            // Removed unit is before the current unit
            if (i <= unit_i)
                unit_i--;
        }

    }
    field.removeUnit(r, c);
}

// Realize the tornado attack
void tornado_attack(Field& field, Vector<Unit*>& units, const int& mr, const int& mc)
{
    // Use a clock-wise order
    const int rIncr[8] = {-1, -1, -1, 0, 1, 1, 1, 0}, cIncr[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    for (int dir_i = 0; dir_i < 8; dir_i++)
    {
        int r = mr + rIncr[dir_i], c = mc + cIncr[dir_i], n = 0;
        while (field.inBounds(r, c))
        {
            // Units can't be in the water or on the mountain
            if (field.getUnit(r, c) == nullptr)
                break;
            n++; // The number of continuous units in this direction
            r += rIncr[dir_i];
            c += cIncr[dir_i];
        }
        r -= rIncr[dir_i];
        c -= cIncr[dir_i];
        for (int i = 0; i < n; i++)
        {
            // In case of out-of-bounds
            if (!field.inBounds(r + rIncr[dir_i], c + cIncr[dir_i]) ||
                field.getTerrain(r + rIncr[dir_i], c + cIncr[dir_i]) == MOUNTAIN)
                break;

            // Units can't be moved into the water or mountain terrains
            field.moveUnit(r, c, r + rIncr[dir_i], c + cIncr[dir_i]);
            if (field.getTerrain(r + rIncr[dir_i], c + cIncr[dir_i]) == WATER)
                remove_unit(field, units, r, c);

            r -= rIncr[dir_i];
            c -= cIncr[dir_i];
        }
    }

}

// Check whether there is a mage in the goblin's
// up, down, left, or right directions and attack
// Return true if the attack occurs
bool goblin_attack(Field& field, Vector<Unit*>& units, const int& gRow, const int& gCol)
{
    bool hasAttacked = false;

    //UP
    if (field.inBounds(gRow - 1, gCol) && field.getUnit(gRow - 1, gCol) != nullptr)
    {
        if (field.getUnit(gRow - 1, gCol)->getSide())
        {
            remove_unit(field, units, gRow - 1, gCol);
            hasAttacked = true;
        }
    }
    //DOWN
    if (field.inBounds(gRow + 1, gCol) && field.getUnit(gRow + 1, gCol) != nullptr)
    {
        if (field.getUnit(gRow + 1, gCol)->getSide())
        {
            remove_unit(field, units, gRow + 1, gCol);
            hasAttacked = true;
        }
    }
    //LEFT
    if (field.inBounds(gRow, gCol - 1) && field.getUnit(gRow, gCol - 1) != nullptr)
    {
        if (field.getUnit(gRow, gCol - 1)->getSide())
        {
            remove_unit(field, units, gRow, gCol - 1);
            hasAttacked = true;
        }
    }
    //RIGHT
    if (field.inBounds(gRow, gCol + 1) && field.getUnit(gRow, gCol + 1) != nullptr)
    {
        if (field.getUnit(gRow, gCol + 1)->getSide())
        {
            remove_unit(field, units, gRow, gCol + 1);
            hasAttacked = true;
        }
    }

    return hasAttacked;
}

// Realize the movement of Patrol Goblins
// Return false if the end of the movement occurs
bool patrol_goblin_move(Field& field, int& gRow, int& gCol, Direction dir)
{
    int rIncr = 0, cIncr = 0;

    switch (dir)
    {
    case W:
        rIncr = -1;
        break;
    case A:
        cIncr = -1;
        break;
    case S:
        rIncr = 1;
        break;
    case D:
        cIncr = 1;
        break;
    default:
        assert (false);
    }

    if (field.moveUnit(gRow, gCol, gRow + rIncr, gCol + cIncr))
    {
        gRow += rIncr;
        gCol += cIncr;
        return true;
    }
    else
        return false;

}

// Load map and units
Field* loadMap(istream& is, Vector<Unit*>& units)
{
    string line;
    getline(is, line);
    // use string input stream
    istringstream iss(line);

    int M = 11, N = 11, NT = 0, NM = 0, NG = 0;
    iss >> M >> N >> NT >> NM >> NG;

    Field* f = new Field(M, N);

    // Initialize the terrain
    for (int i = 0; i < NT; i++)
    {
        int tRow = 0, tCol = 0;
        string t_input;
        Terrain t;

        getline(is, line);
        istringstream iss(line);

        iss >> tRow >> tCol >> t_input;

        // Check boundary and the input
        if (!get_terrain_symbol_from_input(t_input, t) || !f->inBounds(tRow, tCol))
            assert (false);

        f->setTerrain(tRow, tCol, t);
    }

    // Initialize the mages
    for (int i = 0; i < NM; i++)
    {
        getline(is, line);
        istringstream iss(line);

        int mRow = 0, mCol = 0;
        iss >> mRow >> mCol;

        // Check boundary
        if (!f->inBounds(mRow, mCol))
            assert (false);

        Unit* mage = new Unit(true, mRow, mCol);
        f->setUnit(mRow, mCol, mage);
        units.add(mage);
    }

    // Initialize the goblins
    for (int i = 0; i < NG; i++)
    {
        getline(is, line);
        istringstream iss(line);

        int gRow = 0, gCol = 0, PG_ap, TG_fov;
        string gType, PG_dir;
        iss >> gRow >> gCol >> gType;

        // Check boundary and the input
        if (!(f->inBounds(gRow, gCol) && (gType == "TG" || gType == "PG")))
           return NULL;

        // Initialize the patrol goblins
        if (gType == "PG")
        {
            iss >> PG_dir >> PG_ap;
            Unit* goblin = new Unit(false, gRow, gCol, Patrol, get_dir_from_input(PG_dir), PG_ap);
            f->setUnit(gRow, gCol, goblin);
            units.add(goblin);
        }
        // Initialize the tracking goblins
        else if (gType == "TG")
        {
            iss >> TG_fov;
            Unit* goblin = new Unit(false, gRow, gCol, Tracking, TG_fov);
            f->setUnit(gRow, gCol, goblin);
            units.add(goblin);
        }
        else
            return NULL;
    }

    return f;
}


// Main loop for playing the game
void play(Field& field, istream& is, ostream& os, Vector<Unit*>& units)
{

    int numTurns = 1;
    bool afterMove = false;

    while (is)
    {
        os << "Turn " << numTurns << " begins:" << endl;
        // Print the new map
        os << field << endl;

        assert (!units.isEmpty());

        // Check winning
        if (!units[0]->getSide())
        {
            // No mages
            os << "You Lose!" << endl;
            return;
        }
        else if (units[units.size() - 1]->getSide())
        {
            // No goblins
            os << "You Win!" << endl;
            return;
        }

        /* unit moves */

        // mage moves
        for (unit_i = 0; unit_i < units.size(); unit_i++)
        {
            // Check whether the unit is goblin or not
            if (!units[unit_i]->getSide())
                break;

            int mRow = units[unit_i]->getRow(), mCol = units[unit_i]->getCol(), op_counter = -1;

            os << "Please move the unit at (" << mRow << "," << mCol << ")" << endl;

            string line, op;
            getline(is, line);
            // use string input stream
            istringstream iss(line);
            iss >> op;
            while(iss)
            {
                if (op == "W")
                {
                    op_counter++;

                    if (op_counter >= 3)
                        break;
                    else if (field.moveUnit(mRow, mCol, mRow - 1, mCol))
                    {
                        mRow -= 1;
                        afterMove = true;
                    }
                }
                else if (op == "A")
                {
                    op_counter++;

                    if (op_counter >= 3)
                        break;
                    else if (field.moveUnit(mRow, mCol, mRow, mCol - 1))
                    {
                        mCol -= 1;
                        afterMove = true;
                    }
                }
                else if (op == "S")
                {
                    op_counter++;

                    if (op_counter >= 3)
                        break;
                    else if (field.moveUnit(mRow, mCol, mRow + 1, mCol))
                    {
                        mRow += 1;
                        afterMove = true;
                    }
                }
                else if (op == "D")
                {
                    op_counter++;

                    if (op_counter >= 3)
                        break;
                    else if (field.moveUnit(mRow, mCol, mRow, mCol + 1))
                    {
                        mCol += 1;
                        afterMove = true;
                    }
                }
                // Fireball attack
                else if (op == "X")
                {
                    if (!afterMove)
                        op_counter++;

                    if (op_counter >= 3)
                        break;

                    string direction;
                    iss >> direction;

                    int fRow = mRow, fCol = mCol;
                    if (direction == "W")
                    {
                        for (fRow = mRow - 1; fRow >= 0; fRow--)
                        {
                            if (field.getTerrain(fRow, fCol) == MOUNTAIN)
                                break;
                            else if (field.getUnit(fRow, fCol) != nullptr)
                            {
                                remove_unit(field, units, fRow, fCol);
                                break;
                            }
                        }
                    }
                    else if (direction == "A")
                    {
                        for (fCol = mCol - 1; fCol >= 0; fCol --)
                        {
                            if (field.getTerrain(fRow, fCol) == MOUNTAIN)
                                break;
                            else if (field.getUnit(fRow, fCol) != nullptr)
                            {
                                remove_unit(field, units, fRow, fCol);
                                break;
                            }
                        }
                    }
                    else if (direction == "S")
                    {
                        int h = field.getHeight();
                        for (fRow = mRow + 1; fRow < h; fRow++)
                        {
                            if (field.getTerrain(fRow, fCol) == MOUNTAIN)
                                break;
                            else if (field.getUnit(fRow, fCol) != nullptr)
                            {
                                remove_unit(field, units, fRow, fCol);
                                break;
                            }
                        }
                    }
                    else if (direction == "D")
                    {
                        int w = field.getWidth();
                        for (fCol = mCol + 1; fCol < w; fCol++)
                        {
                            if (field.getTerrain(fRow, fCol) == MOUNTAIN)
                                break;
                            else if (field.getUnit(fRow, fCol) != nullptr)
                            {
                                remove_unit(field, units, fRow, fCol);
                                break;
                            }
                        }
                    }
                    else if (direction == "")
                        os << "Direction is missing!" << endl;
                    else
                        assert (false);

                    // Attack won't consume movement counts after a move
                    afterMove = false;
                }
                // Tornado attack
                else if (op == "Y")
                {
                    if (!afterMove)
                        op_counter++;

                    if (op_counter >= 3)
                        break;

                    tornado_attack(field, units, mRow, mCol);

                    op_counter++;
                    afterMove = false;
                }
                iss >> op;
            }
            os << field << endl;
        }

        // goblin moves and attacks
        for (; unit_i < units.size(); unit_i++)
        {
            int gRow = units[unit_i]->getRow(), gCol = units[unit_i]->getCol();

            // patrol goblin moves and attacks
            if (units[unit_i]->getGobType() == Patrol)
            {
                int ap = units[unit_i]->getAP();
                Direction dir = units[unit_i]->getGobDir();
                while (ap >= 0)
                {
                    if (goblin_attack(field, units, gRow, gCol))
                        ap = 0;

                    if (ap == 0)
                    {
                        // reverse the direction
                        units[unit_i]->setGobDir(reverse_dir(dir));
                        break;
                    }

                    if (patrol_goblin_move(field, gRow, gCol, dir))
                        ap--;
                    else
                    {
                        // reverse the direction
                        units[unit_i]->setGobDir(reverse_dir(dir));
                        break;
                    }
                }
            }
            // tracking goblin moves and attacks
            else if (units[unit_i]->getGobType() == Tracking)
            {
                int fov = units[unit_i]->getFOV();
                struct Target
                {
                    int row = 21, col = 21, minLen = 401, tRow = -1, tCol = -1;
                } minTarget;

                // Search the mages in the field of view of the TG
                for (int y = gRow - fov; y <= gRow + fov; y++) // y represents row
                {
                    for (int x = abs(y - gRow) - fov + gCol; x <= fov - abs(y - gRow) + gCol; x++) // x represents column
                    {
                        if (field.inBounds(y, x) && field.getUnit(y, x) != nullptr && field.getUnit(y, x)->getSide())
                        {
                            pair<int, Vector<point>> target_mage = searchShortestPath(field, gRow, gCol, y, x);

                            // the target mage can't be reached
                            if (target_mage.first == -1)
                                continue;

                            // (y, x) has the more shortest distance than minTarget
                            // or it has the same distance as minTarget
                            // but the coordinate partial order is smaller
                            if ((target_mage.first < minTarget.minLen) ||
                                (target_mage.first == minTarget.minLen && coordOrder(y, x, minTarget.row, minTarget.col)))
                            {
                                minTarget.row = y;
                                minTarget.col = x;
                                minTarget.minLen = target_mage.first;
                                minTarget.tRow = target_mage.second[target_mage.second.size() - 2].first;
                                minTarget.tCol = target_mage.second[target_mage.second.size() - 2].second;
                            }
                        }
                    }
                }

                // Exists a mage in the field of view of the TG
                if (minTarget.minLen != 401)
                {
                    remove_unit(field, units, minTarget.row, minTarget.col);
                    field.moveUnit(gRow, gCol, minTarget.tRow, minTarget.tCol);
                }
            }
        }
        numTurns++;
    }
}


