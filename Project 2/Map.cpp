#include <iostream>
#include "Map.h"
using namespace std;


Map::Map()    //default constructor
{
	m_size = 0;        //initializes m_size
}

Map::Map(const Map& src)
// Copy constructor. 
{
	KeyType key;
	ValueType value;

	m_size = src.m_size;    //set size

	for (int i = 0; i < m_size; i++)   //loop for alll nodes
	{
		src.get(i, key, value);        //gets key and value of node "i"
		m_list.addToRear(key, value);  //adds selected value to 5=
	}
}

Map& Map::operator=(const Map& src)
//assignment operator
{
	for (int i = 0; i < m_size; i++)   //loops for all nodes
	{
		KeyType key;
		ValueType val;
		m_list.goTo(0, key, val);      //get key and value from current node
		m_list.deleteItem(key);         //delete current node
	}
	//set size of map
	m_size = src.m_size;

	for (int i = 0; i < m_size; i++) //loops for all new list
	{
		KeyType key;
		ValueType value;
		src.get(i, key, value);    
		m_list.addToRear(key, value); //copy value over
	}
	return (*this);

}



Map::~Map()
// Destructor; calls LinkedList destructor
{

}


bool combine(const Map& m1, const Map& m2, Map& result)
{
	KeyType key;
	ValueType value1;
	ValueType value2;
	bool same = true;   //function initially starts off true
	Map copy(m1);   //start off iwth a copy of a map instead of creating one from scratch
	
	for (int i = 0; i < m2.size(); i++) //loop for all nodes in "m1"
	{
		m2.get(i, key, value1);  //get the key and value at node "i"
		if (copy.contains(key))   //check copy list to see if key exists
		{
			copy.get(key, value2);  //if key exists, get the value of it
			if (value1 != value2)  //check if values are equal
			{
				same = false;       //the functions becomes false
				copy.erase(key);    //erase the key with the un-equal value
			}
		}
		else    //if the key is unique
		{
			copy.insert(key, value1);  //insert it into "copy"
		}
	}
	result.swap(copy); // swap the final "copy" outcome into "result"
	return same;
}


void reassign(const Map& m, Map& result)
{
	KeyType key;
	ValueType value;
	ValueType temp;
	ValueType first;
	Map copy(m);

	if (m.size() == 1)   //if there is only one itemn in the node
	{
		result.swap(copy);  //swap "copy" into "result"
		return;
	}

	m.get(0, key, value);   //get value at end of list
	first = value;           //set that value to the "first" variable

	for (int i = 0; i < m.size(); i++) //loop for all nodes
	{
		m.get(i+1, key, value);     //get the value
		temp = value;               //assign that value to trmp value
		m.get(i, key, value);       //get key 
		copy.update(key, temp);     //change the value of the key
	}
	copy.update(key, first);   //assign the last node the "first" value

	result.swap(copy);   //swap the "copy" map into "result"
	return;
}


bool Map::empty() const   // Return true if the map is empty, otherwise false.
{
	if (m_size == 0)    //there needs to be nothing in the linked list and no head pointer
		return true;  //return true if map is empty
	else 
		return false;   //return false if map is not empty
}

int Map::size() const  // Return the number of key/value pairs in the map.
{
	return m_size;   //return size of the map
}

bool Map::insert(const KeyType& key, const ValueType& value)
// If key is not equal to any key currently in the map, and if the
	// key/value pair can be added to the map, then do so and return true.
	// Otherwise, make no change to the map and return false (indicating
	// that either the key is already in the map, or the map has a fixed
	// capacity and is full)
{
	if (!m_list.findItem(key))   //search for key in linked list
	{
		m_list.addToRear(key, value);  //if doesn't exist, add to rear 
		m_size++;   //add count of nodes
		return true;   //return true after insterting values
	}
	else
	{
		return false;  //return false if key already exists in linked list
	}
}


bool Map::update(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
{
	return m_list.changeItem(key, value);  //return whether the key exists; if it does, change the vlue of the node
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// If key is not equal to any key currently in the map and if the
// key/value pair can be added to the map, then do so and return true.
{
	if (m_list.findItem(key))  //search for key to see if it already exists
	{
		m_list.changeItem(key, value); //if it does change the value
	}
	else   //if does not exist
	{
		m_list.addToRear(key, value);   //add value to the rear
		m_size++;   //add another to the number of nodes
	}
	return true;  //should technically always return true
}

bool Map::erase(const KeyType& key)
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
{
	if (m_list.findItem(key))  //search for input key
	{ 
		m_list.deleteItem(key);   //if key exists delete and remove 1 size
		m_size--;
		return true;
	} 
	else   //if key does not exist return false
	{
		return false;
	}
}

bool Map::contains(const KeyType& key) const
// Return true if key is equal to a key currently in the map, otherwise
// false.
{
	return m_list.findItem(key);   //return true if key exists in linked list
}

bool Map::get(const KeyType& key, ValueType& value) const
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
	if (m_list.findItem(key))   //search for input key
	{
		m_list.getItem(key, value);   //if exists sets value equal to the node
		return true;
	}
	else   //if key does not exists
	{
		return false;
	}
}

bool Map::get(int i, KeyType& key, ValueType& value) const
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of one of the key/value pairs in the map and return
// true.  Otherwise, leave the key and value parameters unchanged and
// return false.  (See below for details about this function.)
{
	if (i >= 0 && i < m_size)  //if int is 0 or greater and less that size
	{
		m_list.goTo(i, key, value);   //set value and key to those of the node
		return true;
	}
	return false;   //if number does not exist
}

void Map::swap(Map& other)
// swaps values using copy constructor
{
	Map temp = other;  
	other = *this;
	*this = temp;
}
