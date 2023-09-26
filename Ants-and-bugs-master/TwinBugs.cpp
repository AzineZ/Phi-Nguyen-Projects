#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"
#include "TwinBugs.h"
using namespace std;

TwinBug::TwinBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
}

//Scan before AND after moving. Use the same scanning method from bug.
//Scan twice because if 2 twin bugs two blocks apart move close to each other in the middle,
//they will trigger detonator in the next turn and blow up in the turn after that. In short, 
//scan twice to avoid exploding one turn late. If scan only before moving, there would be 
//explosion one turn late. If scan only after moving, two twin bugs that are closed might move
//further away before scan and they can't blow up
void TwinBug::move()
{
    //first scan
    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == TWINBUG && detonator == true)
        {
            explode();
            world->getAt(x, y + 1)->explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x, y + 1)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == TWINBUG && detonator == true)
        {
            explode();
            world->getAt(x, y - 1)->explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x, y - 1)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == TWINBUG && detonator == true)
        {
            explode();
            world->getAt(x - 1, y)->explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x - 1, y)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }
    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == TWINBUG && detonator == true)
        {
            explode();
            world->getAt(x + 1, y)->explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x + 1, y)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }
    
    //move
    Move mover = world->randomMove();
    switch (mover) {
    case UP:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
        }
        break;
    case DOWN:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
        }
        break;
    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
        }
        break;
    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
        }
        break;
    default:
        break;
    }

    //scan second time
    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == TWINBUG && detonator == true)
        {
            world->getAt(x, y + 1)->explode();
            explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x, y + 1)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == TWINBUG && detonator == true)
        {
            world->getAt(x, y - 1)->explode();
            explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x, y - 1)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == TWINBUG && detonator == true)
        {
            world->getAt(x - 1, y)->explode();
            explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x - 1, y)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }
    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == TWINBUG && detonator == true)
        {
            world->getAt(x + 1, y)->explode();
            explode();
            detonator = false;
            return;
        }
        else if (world->getAt(x + 1, y)->getType() == TWINBUG && detonator == false)
        {
            detonator = true;
            return;
        }
    }
}

//twin bugs dont need this function so make it return
void TwinBug::breed()
{
    return;
}

OrganismType TwinBug::getType() const
{
    return TWINBUG;
}

char TwinBug::representation() const
{
    return 233;
}

int TwinBug::size() const
{
    return 0;
}

bool TwinBug::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}

//twin bugs dont need this function so make it return
void TwinBug::generateOffspring(int whereX, int whereY)
{
    return;
}

//make sure to blow up 8 directions. Avoid blowing spots that are off the grid
//Do nothing if the location is null or another twin bug, then delete itself
void TwinBug::explode()
{
    if (world->getAt(x + 1, y) != NULL && in_range(x + 1, y))
    {
        if (world->getAt(x + 1, y)->getType() == TWINBUG || world->getAt(x + 1, y) == NULL) {}
        else
        {
            delete world->getAt(x + 1, y);
            world->setAt(x + 1, y, NULL);
        }
    }

    if (world->getAt(x - 1, y) != NULL && in_range(x - 1, y))
    {
        if (world->getAt(x - 1, y)->getType() == TWINBUG || world->getAt(x - 1, y) == NULL) {}
        else
        {
            delete world->getAt(x - 1, y);
            world->setAt(x - 1, y, NULL);
        }
    }

    if (world->getAt(x, y + 1) != NULL && in_range(x, y + 1))
    {
        if (world->getAt(x, y + 1)->getType() == TWINBUG || world->getAt(x, y + 1) == NULL) {}
        else
        {
            delete world->getAt(x, y + 1);
            world->setAt(x, y + 1, NULL);
        }
    }

    if (world->getAt(x, y - 1) != NULL && in_range(x, y - 1))
    {
        if (world->getAt(x, y - 1)->getType() == TWINBUG || world->getAt(x, y - 1) == NULL) {}
        else
        {
            delete world->getAt(x, y - 1);
            world->setAt(x, y - 1, NULL);
        }
    }

    if (world->getAt(x + 1, y + 1) != NULL && in_range(x + 1, y + 1))
    {
        if (world->getAt(x + 1, y + 1)->getType() == TWINBUG || world->getAt(x + 1, y + 1) == NULL) {}
        else
        {
            delete world->getAt(x + 1, y + 1);
            world->setAt(x + 1, y + 1, NULL);
        }
    }

    if (world->getAt(x + 1, y - 1) != NULL && in_range(x + 1, y - 1))
    {
        if (world->getAt(x + 1, y - 1)->getType() == TWINBUG || world->getAt(x + 1, y - 1) == NULL) {}
        else
        {
            delete world->getAt(x + 1, y - 1);
            world->setAt(x + 1, y - 1, NULL);
        }
    }

    if (world->getAt(x - 1, y - 1) != NULL && in_range(x - 1, y - 1))
    {
        if (world->getAt(x - 1, y - 1)->getType() == TWINBUG || world->getAt(x - 1, y - 1) == NULL) {}
        else
        {
            delete world->getAt(x - 1, y - 1);
            world->setAt(x - 1, y - 1, NULL);
        }
    }

    if (world->getAt(x - 1, y + 1) != NULL && in_range(x - 1, y + 1))
    {
        if (world->getAt(x - 1, y + 1)->getType() == TWINBUG || world->getAt(x - 1, y + 1) == NULL) {}
        else
        {
            delete world->getAt(x - 1, y + 1);
            world->setAt(x - 1, y + 1, NULL);
        }
    }
    world->setAt(x, y, NULL);
    delete world->getAt(x, y);
}

