#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
#include <string>
#include <iostream>

#define PI 3.14159265

using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld)
    : GraphObject(imageID, startX, startY, direction, depth), m_sWorld(sWorld), m_alive(true), m_type(""),
    m_health(), m_angle(), m_damage()
{}

bool Actor::isAlive()
{
    return m_alive;
}

void Actor::kill()
{
    m_alive = false;
}

void Actor::setType(string type)
{
    m_type = type;
}

string Actor::getType()
{
    return m_type;
}

int Actor::getHealth()
{
    return m_health;
}

void Actor::setHealth(int health)
{
    m_health = health;
}

void Actor::setAngle(int angle)
{
    m_angle = angle;
}

int Actor::getAngle()
{
    return m_angle;
}

int Actor::getDamage()
{
    return m_damage;
}

void Actor::setDamage(int damage)
{
    m_damage = damage;
}

StudentWorld* Actor::myWorld()
{
    return m_sWorld;
}

/////////////////////////////////////////////////////////////////////
Dirt::Dirt(double startX, double startY, StudentWorld* sWorld)
    : Actor(IID_DIRT, startX, startY, 0, 1, sWorld)
{
    setType("dirt");
}

void Dirt::takeDamage(int damage)
{
    kill();
}

//////////////////////////////////////////////////////////////////////
Socrates::Socrates(double startX, double startY, StudentWorld* sWorld)
    :m_spray(20), m_flame(5), Actor(IID_PLAYER, startX, startY, 0, 0, sWorld)
{
    setType("socrates");
    setHealth(100);
    setAngle(180);
}

void Socrates::doSomething()
{
    if (!(myWorld()->getPlayer()->isAlive()))
        return;

    int ch;
    if (myWorld()->getKey(ch))
    {
        // user hit a key during this tick!
        double x = getX();
        double y = getY();
        int angle = getAngle();
        Actor* temp;

        switch (ch)
        {
        case KEY_PRESS_LEFT:
            //move Socrates counterclockwise
            moveAngle(angle, -128);
            angle += 5;
            setDirection(angle);
            moveAngle(angle, 128);
            setDirection(angle + 180);
            setAngle(angle);
            break;


        case KEY_PRESS_RIGHT:
            //move Socrates clockwise
            moveAngle(angle, -128);
            angle -= 5;
            setDirection(angle);
            moveAngle(angle, 128);
            setDirection(angle + 180);
            setAngle(angle);
            break;


        case KEY_PRESS_SPACE:
            if (m_spray > 0)
            {
                m_spray -= 1;
                getPositionInThisDirection(angle + 180, (2 * SPRITE_RADIUS), x, y);
                temp = new Spray(x, y, angle + 180, myWorld());
                myWorld()->addToVec(temp);
                myWorld()->playSound(SOUND_PLAYER_SPRAY);
            }
            break;


        case KEY_PRESS_ENTER:
            if (m_flame > 0)
            {
                int rot = getAngle();
                m_flame -= 1;
                for (int i = 0; i <= 15; i++)
                {
                    getPositionInThisDirection(rot, (2 * SPRITE_RADIUS), x, y);
                    temp = new Flame(x, y, rot, myWorld());
                    myWorld()->addToVec(temp);
                    rot += 22;
                }
                myWorld()->playSound(SOUND_PLAYER_FIRE);
            }
            break;
        }
    }
    else
    {
        if (m_spray < 20)
            m_spray += 1;
    }
}

int Socrates::getFlameAmmo()
{
    return m_flame;
}

void Socrates::addFlameAmmo(int ammo)
{
    m_flame += ammo;
}

int Socrates::getSprayAmmo()
{
    return m_spray;
}

void Socrates::takeDamage(int damage)
{
    int health = getHealth();
    health -= damage;
    setHealth(health);
    myWorld()->playSound(SOUND_PLAYER_HURT);
    if (health <= 0)
        kill();
}

//////////////////////////////////////////////////////////
Food::Food(double startX, double startY, StudentWorld* sWorld)
    : Actor(IID_FOOD, startX, startY, up, 1, sWorld)
{
    setType("food");
}

//////////////////////////////////////////////////////////
Goodie::Goodie(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld)
    :Actor(imageID, startX, startY, 0, 1, sWorld), m_ticks(0)
{}

void Goodie::doSomething()
{
    if (!isAlive())
    {
        return;
    }

    if (ifOverlap())
        return;

    if(m_ticks > max(rand() % (300 - (10 * myWorld()->getLevel())), 50))
    {
        kill();
    }
    m_ticks++;
}

void Goodie::takeDamage(int num)
{
    kill();
}

bool Goodie::ifOverlap()
{
    Socrates* player = myWorld()->overlapSocrates(this);
    if (player != nullptr)
    {
        if (getType() == "restGoodie")
        {
            myWorld()->increaseScore(250);
            player->setHealth(100);
            myWorld()->playSound(SOUND_GOT_GOODIE);
        }
        else if (getType() == "flameGoodie")
        {
            myWorld()->increaseScore(300);
            player->addFlameAmmo(5);
            myWorld()->playSound(SOUND_GOT_GOODIE);
        }
        else if (getType() == "lifeGoodie")
        {
            myWorld()->increaseScore(500);
            myWorld()->incLives();
            myWorld()->playSound(SOUND_GOT_GOODIE);
        }
        else if (getType() == "fungus")
        {
            myWorld()->increaseScore(-50);
            myWorld()->getPlayer()->takeDamage(20);
        }
        kill();
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////
restoreHealthGoodie::restoreHealthGoodie(double startX, double startY, StudentWorld* sWorld)
    :Goodie(IID_RESTORE_HEALTH_GOODIE, startX, startY, 0, 1, sWorld)
{
    setType("restGoodie");
}

///////////////////////////////////////////////////////////
extraLifeGoodie::extraLifeGoodie(double startX, double startY, StudentWorld* sWorld)
    : Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, 0, 1, sWorld)
{
    setType("lifeGoodie");
}

///////////////////////////////////////////////////////////
flameThrowerGoodie::flameThrowerGoodie(double startX, double startY, StudentWorld* sWorld)
    : Goodie(IID_FLAME_THROWER_GOODIE, startX, startY, 0, 1, sWorld)
{
    setType("flameGoodie");
}

///////////////////////////////////////////////////////////
Fungus::Fungus(double startX, double startY, StudentWorld* sWorld)
    :Goodie(IID_FUNGUS, startX, startY, 0, 1, sWorld)
{
    setType("fungus");
}

////////////////////////////////////////////////////////////
Weapon::Weapon(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld)
    :Actor(imageID, startX, startY, direction, 1, sWorld), m_pixels(0), m_maxPixels(0)
{
    setAngle(direction);
}

bool Weapon::ifOverlap(int damage)
{
    Actor* temp = myWorld()->findMove(this, "enemyOverlap");
    if (temp != nullptr)
    {
        temp->takeDamage(damage);
        kill();
        return true;
    }
    return false;
}

void Weapon::setMaxPixels(int max)
{
    m_maxPixels = max;
}

void Weapon::doSomething()
{
    if (!isAlive())
        return;
    if (ifOverlap(getDamage()))
        return;
    double x = getX();
    double y = getY();

    if (m_pixels <= m_maxPixels)
    {
        moveAngle(getAngle(), SPRITE_RADIUS * 2);
        m_pixels += (2 * SPRITE_RADIUS);
    }

    if (ifOverlap(getDamage()))
        return;

    if (m_pixels > m_maxPixels)
        kill();
}

//////////////////////////////////////////////////////////////
Flame::Flame(double startX, double startY, Direction direction, StudentWorld* sWorld)
    : Weapon(IID_FLAME, startX, startY, direction, 1, sWorld)
{
    setType("flame");
    setMaxPixels(32);
    setDamage(5);
}

////////////////////////////////////////////////////////////
Spray::Spray(double startX, double startY, Direction direction, StudentWorld* sWorld)
    :Weapon(IID_SPRAY, startX, startY, direction, 1, sWorld)
{
    setType("spray");
    setMaxPixels(112);
    setDamage(2);
}

////////////////////////////////////////////////////////////
Pit::Pit(double startX, double startY, StudentWorld* sWorld)
    : Actor(IID_PIT, startX, startY, 0, 1, sWorld), m_regSal(5), m_agroSal(3), m_eColi(2)
{
    setType("pit");
    myWorld()->addBacteria(10);
}

void Pit::doSomething()
{
    int rand = randInt(0, 49);
    double x = getX();
    double y = getY();
    if (m_regSal != 0 || m_agroSal != 0 || m_eColi != 0)
    {
        if (rand == 0)
        {
            for (;;)
            {
                int spawn = randInt(1, 3);

                if (m_agroSal != 0 && spawn == 1)
                {
                    AgroSalmonella* temp = new AgroSalmonella(x, y, myWorld());
                    myWorld()->addToVec(temp);
                    m_agroSal--;
                    return;
                }

                else if (m_eColi != 0 && spawn == 2)
                {
                    Ecoli* temp = new Ecoli(x, y, myWorld());
                    myWorld()->addToVec(temp);
                    m_eColi--;
                    return;
                }

                else if (m_regSal != 0 && spawn == 3)
                {
                    RegSalmonella* temp = new RegSalmonella(x, y, myWorld());
                    myWorld()->addToVec(temp);
                    m_regSal--;
                    return;
                }
            }
        }
    }
    else
    {
        kill();
    }
}

/////////////////////////////////////////////////////////////
Bacteria::Bacteria(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld)
    :Actor(imageID, startX, startY, 90, 0, sWorld), m_deathSound(), m_food(0), m_movement(0), m_hurtSound()
{
    setAngle(direction);
}

void Bacteria::takeDamage(int damage)
{

    int health = getHealth();
    health -= damage;
    setHealth(health);
    if (getHealth() <= 0)
    {
        killBacteria();
    }
    else
        myWorld()->playSound(getSound("damage"));
}

void Bacteria::setHurtSound(int sound)
{
    m_hurtSound = sound;
}

void Bacteria::setDeathSound(int sound)
{
    m_deathSound = sound;
}

int Bacteria::getSound(string type)
{
    if (type == "hurt")
        return m_hurtSound;
    if (type == "death")
        return m_deathSound;
    return -1;
}

void Bacteria::setFood(int food)
{
    m_food = food;
}

int Bacteria::getFood()
{
    return m_food;
}

void Bacteria::setMovePlan(int plan)
{
    m_movement = plan;
}

bool Bacteria::moveAroundDirt(int angle, string type)
{

    int inc = 0;
    if (getType() == "ecoli")
        inc = 2;
    else
        inc = 3;

    int temp = randInt(0, 359);
    moveAngle(angle, inc);

    double radius = sqrt((getX() - 128) * (getX() - 128) + (getY() - 128) * (getY() - 128));
    if (radius > 128 || myWorld()->dirtOverlap(this))
    {
        if (type != "goSocrates")
        {
            setAngle(temp);
            setDirection(temp);
            setMovePlan(10);
        }
        moveAngle(angle, -(inc));
        return false;
    }

    moveAngle(angle, -(inc));
    return true;
}

void Bacteria::moveToFood()
{
    Actor* temp = myWorld()->findMove(this, "foodLocation");

    if (temp == nullptr)
    {
        int tempInt = randInt(0, 359);
        setAngle(tempInt);
        setDirection(tempInt);
        setMovePlan(10);
        return;
    }
    else
    {
        double x = temp->getX();
        double y = temp->getY();
        double thisX = getX();
        double thisY = getY();
        int angle = 0;

        double radius = sqrt((x - thisX) * (x - thisX) + (y - thisY) * (y - thisY));

        double tempX = 100;
        double tempY = 100;

        for (int i = 0; i < 360; i++)
        {
            double newX = getY();
            double newY = getX();
            getPositionInThisDirection(i, radius, newX, newY);
            newX = sqrt((x - newX) * (x - newX));
            newY = sqrt((y - newY) * (y - newY));
            if (newX <= tempX && newY <= tempY)
            {
                tempX = newX;
                tempY = newY;
                angle = i;
            }
        }
        setDirection(angle);
        setAngle(angle);
        setMovePlan(10);

        if (!moveAroundDirt(angle, ""))
            return;
    }
}

bool Bacteria::ifOverlapSocrates()
{
    Socrates* player = myWorld()->overlapSocrates(this);
    if (player != nullptr)
    {
        player->takeDamage(getDamage());
        return true;
    }
    return false;
}

bool Bacteria::regularMovement()
{
    if (m_movement > 0)
    {
        setMovePlan(m_movement - 1);

        if (moveAroundDirt(getAngle(), ""))
        {
            moveAngle(getAngle(), 3);
            return true;
        }
    }
    else
    {
        moveToFood();
    }
    return false;
}

void Bacteria::killBacteria()
{
    double x = getX();
    double y = getY();

    if (isAlive())
    {
        myWorld()->increaseScore(100);
        kill();
        myWorld()->addBacteria(-1);
        myWorld()->playSound(getSound("death"));

        int chance = randInt(0, 1);
        if (chance == 0)
        {
            Food* temp = new Food(x, y, myWorld());
            myWorld()->addToVec(temp);
            myWorld()->playSound(SOUND_BACTERIUM_BORN);
        }
    }
}

void Bacteria::ifOverlapFood()
{
    string str = "foodOverlap";
    Actor* food = myWorld()->findMove(this, str);
    if (food != nullptr)
    {
        food->kill();
        setFood(getFood() + 1);
    }
}

void Bacteria::doSomething()
{

    string canPass = "yes";

    //check if alive
    if (!isAlive())
        return;

    if (agroSalMove())
        canPass = "no";

    //overlap player
    if (ifOverlapSocrates())
        return;


    //eaten 3 food
    else if (getFood() >= 3)
    {
        int x = static_cast<int>(getX());
        int y = static_cast<int>(getY());
        //x coord
        if (x < (VIEW_WIDTH / 2))
            x = x + SPRITE_RADIUS;
        else
            x = x - SPRITE_RADIUS;

        //y coord
        if (y < (VIEW_WIDTH / 2))
            y = y + SPRITE_RADIUS;
        else
            y = y - SPRITE_RADIUS;

        if (getType() == "regSalmonella")
        {
            RegSalmonella* temp = new RegSalmonella(x, y, myWorld());
            myWorld()->addToVec(temp);
        }
        else if (getType() == "agroSalmonella")
        {
            AgroSalmonella* temp = new AgroSalmonella(x, y, myWorld());
            myWorld()->addToVec(temp);
        }
        else if (getType() == "ecoli")
        {
            Ecoli* temp = new Ecoli(x, y, myWorld());
            myWorld()->addToVec(temp);
        }

        //////////////////////add more///////////////////////////////

        setFood(0);
    }
    //overlap food
    else
        ifOverlapFood();

    //agro salmonella return after finding socrates
    if (canPass == "no")
        return;

    //do movement per bacteria
    if (regularMovement())
        return;

}

bool Bacteria::agroSalMove() 
{ return false; };

////////////////////////////////////////////////////////////
RegSalmonella::RegSalmonella(double startX, double startY, StudentWorld* sWorld)
    :Bacteria(IID_SALMONELLA, startX, startY, 90, 0, sWorld)
{
    setType("regSalmonella");
    setHealth(4);
    setDamage(1);
    setHurtSound(SOUND_SALMONELLA_HURT);
    setDeathSound(SOUND_SALMONELLA_DIE);
    myWorld()->playSound(SOUND_BACTERIUM_BORN);
}

/////////////////////////////////////////////////////////////
AgroSalmonella::AgroSalmonella(double startX, double startY, StudentWorld* sWorld)
    :Bacteria(IID_SALMONELLA, startX, startY, 90, 0, sWorld)
{
    setType("agroSalmonella");
    setHealth(10);
    setDamage(4);
    setHurtSound(SOUND_SALMONELLA_HURT);
    setDeathSound(SOUND_SALMONELLA_DIE);
    myWorld()->playSound(SOUND_BACTERIUM_BORN);
}

bool AgroSalmonella::agroSalMove()
{
    double x = getX();
    double y = getY();
    int angle = 0;

    double playerX = myWorld()->getPlayer()->getX();
    double playerY = myWorld()->getPlayer()->getY();

    double radius = sqrt((x - playerX) * (x - playerX) + (y - playerY) * (y - playerY));

    if (radius <= 72.0)
    {

        double tempX = 100;
        double tempY = 100;

        for (int i = 0; i < 360; i++)
        {
            double newX = playerX;
            double newY = playerY;
            getPositionInThisDirection(i, radius, newX, newY);
            newX = sqrt((playerX - newX) * (playerX - newX));
            newY = sqrt((playerY - newY) * (playerY - newY));
            if (newX <= tempX && newY <= tempY)
            {
                tempX = newX;
                tempY = newY;
                angle = i;
            }
        }

        setDirection(angle);
        setAngle(angle);

        if (!moveAroundDirt(angle, "goSocrates"))
        {
            return true;
        }
        moveAngle(angle, 3);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////
Ecoli::Ecoli(double startX, double startY, StudentWorld* sWorld)
    :Bacteria(IID_ECOLI, startX, startY, 90, 0, sWorld)
{
    setType("ecoli");
    setHealth(5);
    setDamage(4);
    setHurtSound(SOUND_ECOLI_HURT);
    setDeathSound(SOUND_ECOLI_DIE);
    myWorld()->playSound(SOUND_BACTERIUM_BORN);
}

bool Ecoli::regularMovement()
{
    double x = getX();
    double y = getY();
    int angle = 0;

    double playerX = myWorld()->getPlayer()->getX();
    double playerY = myWorld()->getPlayer()->getY();

    double radius = sqrt((x - playerX) * (x - playerX) + (y - playerY) * (y - playerY));

    if (radius <= 256.0)
    {

        double tempX = 100;
        double tempY = 100;

        for (int i = 0; i < 360; i++)
        {
            double newX = playerX;
            double newY = playerY;
            getPositionInThisDirection(i, radius, newX, newY);
            newX = sqrt((playerX - newX) * (playerX - newX));
            newY = sqrt((playerY - newY) * (playerY - newY));
            if (newX <= tempX && newY <= tempY)
            {
                tempX = newX;
                tempY = newY;
                angle = i;
            }
        }

        setDirection(angle);
        setAngle(angle);

        int i = 0;
        while (!moveAroundDirt(angle, "goSocrates") && i < 10)
        {
            angle += 10;
            setDirection(angle);
            setAngle(angle);
            i++;
        }
        if (i == 10)
        {
            return true;
        }
        moveAngle(angle, 2);
    }
    return true;
}