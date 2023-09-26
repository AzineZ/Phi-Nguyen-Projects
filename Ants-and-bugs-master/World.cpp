#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "TwinBugs.h"
#include "windows.h"
using namespace std;

///////////////////
// Public functions
///////////////////
void gotoxy(int x, int y);


// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 10
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 7
    createOrganisms(BUG, INITIAL_BUGS);
    // creates Twin Bugs = 2
    createOrganisms(TWINBUG, INITIAL_TBUGS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int numAnts = 0;
    int numBugs = 0;
    int numTwins = 0;
    cout << endl << endl;
    for (int j = 0; j < WORLDSIZE; j++) {
        for (int i = 0; i < WORLDSIZE; i++) {
            gotoxy(i + 44, j + 8);
            if (grid[i][j] == NULL) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << ".";
            }
            //change color based on organism type
            else {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                    SetConsoleTextAttribute(hConsole, 12);
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                    SetConsoleTextAttribute(hConsole, 6);
                }
                else if (grid[i][j]->getType() == TWINBUG) {
                    numTwins++;
                    SetConsoleTextAttribute(hConsole, 14);
                }
                cout << grid[i][j]->representation();
            }
        }
        cout << endl;
    }
    //set these values on the top of the grid, add some color
    gotoxy(35, 4);
    SetConsoleTextAttribute(hConsole, 12);
    cout << "Ants: " << numAnts << endl;
    gotoxy(35, 5);
    SetConsoleTextAttribute(hConsole, 10);
    cout << "Bugs: " << numBugs << endl;
    gotoxy(35, 6);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "Twin Bugs: " << numTwins << endl;
    //change color back to white text and black background
    SetConsoleTextAttribute(hConsole, 12);
    gotoxy(53, 4);
    cout << "Press a to add one ant";
    SetConsoleTextAttribute(hConsole, 10);
    gotoxy(53, 5);
    cout << "Press b to add one bug";
    SetConsoleTextAttribute(hConsole, 14);
    gotoxy(53, 6);
    cout << "Press t to add two twin bugs";
    SetConsoleTextAttribute(hConsole, 15);
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move twin bugs
    // 3. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the bugs
    moveOrganism(BUG);

    //move the twinbugs
    moveOrganism(TWINBUG);

    // Move the ants
    moveOrganism(ANT);



    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == TWINBUG) {
                new TwinBug(this, p.x, p.y);   //create a twin bug at this location in the world
            }
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
