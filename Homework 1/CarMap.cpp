#include <iostream>
using namespace std;

#include "CarMap.h"

CarMap::CarMap()   
{

}

bool CarMap:: addCar(std::string license)
{
	return m_ncars.insert(license, 0);
}

double CarMap::miles(std::string license) const
{
	double miles;
	if (m_ncars.get(license, miles))
		return miles;
	else
		return -1;
}

bool CarMap::drive(std::string license, double distance)
{
	double miles;
	if (m_ncars.get(license, miles))
	{
		if (distance < 0)
		{
			return false;
		}
		else
		{
			distance += miles;
			m_ncars.update(license, distance);
			return true;
		}
	}
	return false;
}

int CarMap::fleetSize() const
{
	return m_ncars.size();
}

void CarMap::print() const
{
	for (int i = 0; i < fleetSize(); i++)
	{
		KeyType license;
		ValueType miles;
		m_ncars.get(i, license,miles);
		cout << license << " " << miles << endl;
	}
}