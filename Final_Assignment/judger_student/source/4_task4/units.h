#ifndef UNITS_H_INCLUDED
#define UNITS_H_INCLUDED

#include <memory>
#include <string>
#include "field.h"

/* Types and Directions of goblins*/
enum GoblinType {Patrol, Tracking};
enum Direction {W, A, S, D};

/* Class for units */
class Unit {
public:

    // Constructor for mages
    Unit(bool sd, int row, int col);
    // Constructor for patrol goblins
    Unit(bool sd, int row, int col, GoblinType type, Direction dir, int ap);
    // Constructor for tracking goblins
    Unit(bool sd, int row, int col, GoblinType type, int fov);

    // Check which side the unit belongs to
    bool getSide() const;

    // Get and set row(col) of the unit
    int getRow() const;
    void setRow(int row);

    int getCol() const;
    void setCol(int col);

    // Get and set type of the goblin
    GoblinType getGobType() const;
    void setGobType(std::string type_str);

    // Get and set direction of the goblin
    Direction getGobDir() const;
    void setGobDir(Direction dir_pg);

    // Get and set the action points of the PG
    int getAP() const;
    void setAP(int ap_pg);

    // Get and set the field of view of the TG
    int getFOV() const;
    void setFOV(int fov_tg);

private:
    // Position in the field
    bool side;
    int row;
    int col;

    GoblinType gType;
    Direction gDir;

    // Action Points
    int ap;

    // Field of View
    int fov;
};

std::string getUnitSymbol(const Unit& u);
#endif // UNITS_H_INCLUDED
