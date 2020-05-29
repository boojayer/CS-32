#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;


GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_nBacteria(0)
{
    player = nullptr;
}

int StudentWorld::init()
{
    addDirt();
    addFood();
    addPits();

    //socrates
    player = new Socrates(0, 128, this);

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::randPoint(int& x, int& y, int radius)
{
    int tempVal = 200;
    double tempX = 0, tempY = 0;
    if (radius == 128)
    {
        while (tempVal != 128)
        {
            tempX = randInt(0, 255);
            tempY = randInt(0, 255);
            tempVal = sqrt((tempX - 128) * (tempX - 128) + (tempY - 128) * (tempY - 128));
        }
    }
    else
    {
        while (tempVal > radius)
        {
            tempX = randInt(0, 255);
            tempY = randInt(0, 255);
            tempVal = sqrt((tempX - 128) * (tempX - 128) + (tempY - 128) * (tempY - 128));
        }
    }

    x = tempX;
    y = tempY;
}

bool StudentWorld::overlaps(int x, int y)
{
    vector<Actor*> ::iterator it;
    it = myList.begin();
    while (it != myList.end())
    {
        Actor* temp = *it;
        double tempVal = sqrt((x - temp->getX()) * (x - temp->getX()) + (y - temp->getY()) * (y - temp->getY()));
        if (tempVal <= static_cast<double>(2 * SPRITE_RADIUS))
            return true;
        it++;
    }
    return false;
}

int StudentWorld::move()
{
    //player do something
    player->doSomething();

    vector <Actor*>::iterator it;
    it = myList.begin();

    //actors doSomething
    while (it != myList.end())
    {
        Actor* temp = *it;
        temp->doSomething();
        it++;
    }

    //delete dead actors
    deleteDead();

    //addNewActors
    addNewActors();

    scoreBoard();

    //if player dies
    if (!player->isAlive())
    {
        decLives();
        addBacteria(-1000);
        return GWSTATUS_PLAYER_DIED;
    }

    if (m_nBacteria <= 0)
        return GWSTATUS_FINISHED_LEVEL;

    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::scoreBoard()
{
    ostringstream oss;
    oss.setf(ios::fixed);
    oss.precision(1);
    oss.fill('0');
    oss << setw(6) << getScore() << endl;
    string str = oss.str();

    //game stats
    setGameStatText("Score: " + str + "  Level: " + to_string(getLevel()) + "  Lives: "
        + to_string(getLives()) + "  Health: " + to_string(getPlayer()->getHealth()) + "  Sprays: " +
        to_string(getPlayer()->getSprayAmmo()) + "  Flames: " + to_string(getPlayer()->getFlameAmmo()));
}

void StudentWorld::addToVec(Actor* temp)
{
    myList.push_back(temp);
}

void StudentWorld::addNewActors()
{
    int chanceGoodie = randInt(0, max(510 - getLevel(), 250));
    int chanceFungus = randInt(0, max(510 - getLevel(), 200));
    int percentChance = randInt(0, 9);
    int x, y = 0;
    Actor* temp;

    //addGoodies
    if (chanceGoodie == 0)
    {
        switch (percentChance)
        {
        case 0:
            randPoint(x, y, 128);
            temp = new extraLifeGoodie(x, y, this);
            break;
        case 1:
        case 2:
        case 3:
            randPoint(x, y, 128);
            temp = new flameThrowerGoodie(x, y, this);
            break;
        default:
            randPoint(x, y, 128);
            temp = new restoreHealthGoodie(x, y, this);
            break;
        }
        myList.push_back(temp);
    }
    if (chanceFungus == 0)
    {
        randPoint(x, y, 128);
        temp = new Fungus(x, y, this);
        myList.push_back(temp);
    }
}

void StudentWorld::cleanUp()
{
    delete player;
    player = nullptr;

    vector<Actor*>::iterator it;
    it = myList.begin();

    for (it = myList.begin(); it != myList.end(); it++)
    {
        delete* it;
    }
    myList.clear();

}

void StudentWorld::addDirt()
{
    int x = 0, y = 0;
    for (int i = 0; i <= max(180 - (getLevel() * 20), 20); i++)
    {
        randPoint(x, y, 120);
        Actor* temp = new Dirt(x, y, this);
        myList.push_back(temp);
    }
}

void StudentWorld::addFood()
{
    int x = 0, y = 0;
    randPoint(x, y, 120);
    for (int i = 0; i <= min((getLevel() * 5), 25); i++)
    {
        while (overlaps(x, y))
        {
            randPoint(x, y, 120);
        }
        Actor* temp = new Food(x, y, this);
        myList.push_back(temp);
    }
}

void StudentWorld::addPits()
{
    int x = 0, y = 0;
    randPoint(x, y, 120);
    for (int i = 1; i <= getLevel(); i++)
    {
        while (overlaps(x, y))
        {
            randPoint(x, y, 120);
        }
        Actor* temp = new Pit(x, y, this);
        myList.push_back(temp);
    }
}

void StudentWorld::deleteDead()
{
    vector <Actor*>::iterator it;
    for (it = myList.begin(); it != myList.end();)
    {
        if (!(*it)->isAlive())
        {
            delete* it;
            it = myList.erase(it);
        }
        else
            it++;
    }
}

bool StudentWorld::dirtOverlap(const Actor* temp)
{
    for (int i = 0; i < myList.size(); i++)
    {
        if (myList[i]->getType() == "dirt")
        {
            double x = temp->getX();
            double y = temp->getY();

            double actorX = myList[i]->getX();
            double actorY = myList[i]->getY();

            double radius = sqrt((actorX - x) * (actorX - x) + (actorY - y) * (actorY - y));
            if (radius <= static_cast<double>(SPRITE_RADIUS))
            {
                return true;
            }
        }
    }
    return false;
}

void StudentWorld::addBacteria(int num)
{

    m_nBacteria += num;
    if (m_nBacteria < 0)
        m_nBacteria = 0;
}

Socrates* StudentWorld::getPlayer()
{
    return player;
}

Socrates* StudentWorld::overlapSocrates(const Actor* temp) const
{
    double actorX = temp->getX();
    double actorY = temp->getY();

    double playerX = player->getX();
    double playerY = player->getY();

    double radius = sqrt((actorX - playerX) * (actorX - playerX) + (actorY - playerY) * (actorY - playerY));

    if (radius <= static_cast<double>(2 * SPRITE_RADIUS))
        return player;

    return nullptr;
}

Actor* StudentWorld::findMove(const Actor* temp, string type) const
{
    double tempRad = 200;
    int loc = -1;

    for (int i = 0; i < myList.size(); i++)
    {

        if (type == "enemyOverlap")
        {
            if (temp == myList[i] || myList[i]->getType() == "flame" || myList[i]->getType() == "food"
                || myList[i]->getType() == "flameGoodie" || myList[i]->getType() == "restGoodie"
                || myList[i]->getType() == "lifeGoodie" || myList[i]->getType() == "spray"
                || myList[i]->getType() == "pit")
                continue;
        }


        double x = temp->getX();
        double y = temp->getY();

        double actorX = myList[i]->getX();
        double actorY = myList[i]->getY();

        double radius = sqrt((actorX - x) * (actorX - x) + (actorY - y) * (actorY - y));


        if (type == "foodOverlap" && myList[i]->getType() == "food" && radius <= static_cast<double>(2 * SPRITE_RADIUS))
        {
            return myList[i];
        }

        else if (type == "enemyOverlap" && radius <= static_cast<double>(2 * SPRITE_RADIUS))
        {
            return myList[i];
        }

        else if (type == "foodLocation" && myList[i]->getType() == "food" && radius <= 128 && radius < tempRad)
        {
            tempRad = radius;
            loc = i;
        }
    }

    if (type == "foodLocation" && tempRad != 200 && loc != -1)
    {
        return myList[loc];
    }

    return nullptr;
}

StudentWorld::~StudentWorld()
{
    this->cleanUp();
}

