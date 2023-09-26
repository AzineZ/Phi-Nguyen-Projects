#pragma once
#include <iostream>
#include "Organism.h"
#include "World.h"


class TwinBug : public Organism
{
public:
    TwinBug(World* aWorld, int xcoord, int ycoord);
    // In the given world moves this organism.
    void move();

    // Makes this organism breed.
    void breed();

    // Returns the type of this organism.
    OrganismType getType() const;

    // The character representation of this organism.
    char representation() const;

    //return size of this organism
    int size() const;

    //check if x, y is in the grid or not
    bool in_range(int xx, int yy);

    //twin bugs don't need this but needs to override it
    void generateOffspring(int whereX, int whereY);

    //blow up adjacent cells in 8 directions and itself
    void explode();

    //flag for explode() function
    //use this to make sure that they touch on display first then blow up later.
    //Do not let them explode before display.
    bool detonator = false;
private:

};
