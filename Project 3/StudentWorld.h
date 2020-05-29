#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include <string>
#include <vector>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:

    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    void scoreBoard();
    virtual void cleanUp();
    void addToVec(Actor* temp);
    void randPoint(int& x, int& y, int radius);
    bool overlaps(int x, int y);
    void addNewActors();
    void addDirt();
    void addFood();
    void addPits();
    void deleteDead();
    bool dirtOverlap(const Actor* temp);
    void addBacteria(int num);
    Socrates* getPlayer();
    Socrates* overlapSocrates(const Actor* temp) const;
    Actor* findMove(const Actor* temp, std::string type) const;
    virtual ~StudentWorld();

private:
    std::vector<Actor*> myList;
    Socrates* player;
    int m_nBacteria;
};

#endif // STUDENTWORLD_H_
