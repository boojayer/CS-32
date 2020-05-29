#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <string>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor : public GraphObject
{
public:
	Actor(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld);
	virtual void doSomething() {};
	bool isAlive();
	void kill();
	void setType(std::string type);
	std::string getType();
	virtual void takeDamage(int damage) {};
	int getHealth();
	void setHealth(int health);
	int getAngle();
	void setAngle(int angle);
	void setDamage(int damage);
	int getDamage();
	StudentWorld* myWorld();

private:
	StudentWorld* m_sWorld;
	bool m_alive;
	int m_health;
	int m_angle;
	int m_damage;
	std::string m_type;
};

/////////////////////////////////////////////////////////////////////
class Dirt : public Actor
{
public:
	Dirt(double startX, double startY, StudentWorld* sWorld);
	virtual void takeDamage(int damage);
};

///////////////////////////////////////////////////////////////////////
class Socrates : public Actor
{
public:
	Socrates(double startX, double startY, StudentWorld* sWorld);
	virtual void doSomething();
	int getFlameAmmo();
	void addFlameAmmo(int ammo);
	int getSprayAmmo();
	virtual void takeDamage(int damage);

private:
	int m_spray;
	int m_flame;
};

////////////////////////////////////////////////////////////////////////
class Food : public Actor
{
public:
	Food(double startX, double startY, StudentWorld* sWorld);
};

//////////////////////////////////////////////////////////////////////
class Goodie : public Actor
{
public:
	Goodie(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld);
	virtual void doSomething();
	virtual void takeDamage(int num);
	bool ifOverlap();
private:
	int m_ticks;
};

//////////////////////////////////////////////////////////////////////
class restoreHealthGoodie : public Goodie
{
public:
	restoreHealthGoodie(double startX, double startY, StudentWorld* sWorld);
};

//////////////////////////////////////////////////////////////////////
class extraLifeGoodie : public Goodie
{
public:
	extraLifeGoodie(double startX, double startY, StudentWorld* sWorld);
};

//////////////////////////////////////////////////////////////////////
class flameThrowerGoodie : public Goodie
{
public:
	flameThrowerGoodie(double startX, double startY, StudentWorld* sWorld);
};

/////////////////////////////////////////////////////////////////////
class Fungus : public Goodie
{
public:
	Fungus(double startX, double startY, StudentWorld* sWorld);
};

///////////////////////////////////////////////////////////////////////
class Weapon : public Actor
{
public:
	Weapon(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld);
	bool ifOverlap(int damage);
	void setMaxPixels(int max);
	virtual void doSomething();
private:
	int m_pixels;
	int m_maxPixels;
};

///////////////////////////////////////////////////////////////////////
class Flame : public Weapon
{
public:
	Flame(double startX, double startY, Direction direction, StudentWorld* sWorld);
};

///////////////////////////////////////////////////////////////////////
class Spray : public Weapon
{
public:
	Spray(double startX, double startY, Direction direction, StudentWorld* sWorld);
};

//////////////////////////////////////////////////////////////////////
class Pit : public Actor
{
public:
	Pit(double startX, double startY, StudentWorld* sWorld);
	virtual void doSomething();
private:
	int m_regSal;
	int m_agroSal;
	int m_eColi;
};

///////////////////////////////////////////////////////////////////////
class Bacteria : public Actor
{
public:
	Bacteria(int imageID, double startX, double startY, Direction direction, int depth, StudentWorld* sWorld);
	void takeDamage(int damage);
	void setHurtSound(int sound);
	void setDeathSound(int sound);
	int getSound(std::string type);
	void setFood(int food);
	int getFood();
	void setMovePlan(int plan);
	bool moveAroundDirt(int angle, std::string type);
	void moveToFood();
	virtual bool regularMovement();
	void killBacteria();
	bool ifOverlapSocrates();
	void ifOverlapFood();
	virtual void doSomething();
	virtual bool agroSalMove();


private:
	int m_hurtSound;
	int m_deathSound;
	int m_food;
	int m_movement;
};

///////////////////////////////////////////////////////////////////////
class RegSalmonella : public Bacteria
{
public:
	RegSalmonella(double startX, double startY, StudentWorld* sWorld);
};

///////////////////////////////////////////////////////////////////////
class AgroSalmonella : public Bacteria
{
public:
	AgroSalmonella(double startX, double startY, StudentWorld* sWorld);
	virtual bool agroSalMove();
};

///////////////////////////////////////////////////////////////////////
class Ecoli : public Bacteria
{
public:
	Ecoli(double startX, double startY, StudentWorld* sWorld);
	virtual bool regularMovement();
};

#endif // ACTOR_H_