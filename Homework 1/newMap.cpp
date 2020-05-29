#include <iostream>
#include "newMap.h"
using namespace std;


Map::Map()
{
	m_size = DEFAULT_MAX_ITEMS;
	m_taken = 0;
	m_nmap = new pairs[DEFAULT_MAX_ITEMS];
}

//new functiosn for problem 5
Map::Map(int s)
{
	m_taken = 0;
	m_size = s;
	m_nmap = new pairs[m_size];
}

Map::Map(const Map& src)
{
	m_size = src.m_size;
	m_taken = src.m_taken;
	m_nmap = new pairs[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_nmap[i] = src.m_nmap[i];
	}
}

Map& Map::operator=(const Map& src)
{
	delete[]m_nmap;
	m_size = src.m_size;
	m_taken = src.m_taken;
	m_nmap = new pairs[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_nmap[i] = src.m_nmap[i];
	}
	return *this;
}

Map::~Map()
{
	delete[]m_nmap;
}

//end of new functiosn for problem 5

bool Map::empty() const
{
	if (m_taken == 0)
		return true;
	else
		return false;
}

int Map::size() const
{
	return m_taken;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (m_taken >= m_size)
		return false;
	for (int i = 0; i <= m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			return false;
		}
	}
	m_nmap[m_taken].k = key;
	m_nmap[m_taken].v = value;
	m_taken++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i <= m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			m_nmap[i].v = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			m_nmap[i].v = value;
			return true;
		}
	}
	if (m_taken == m_size)
		return false;
	else
	{
		m_nmap[m_taken].v = value;
		m_nmap[m_taken].k = key;
		m_size++;
		return true;
	}
}

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			if (m_taken == 1)
			{
				m_taken = 0;
				return true;
			}
			m_nmap[i] = m_nmap[m_taken - 1];
			m_taken--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			return true;
		}
	}
	return false;
}


bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < m_taken; i++)
	{
		if (m_nmap[i].k == key)
		{
			value = m_nmap[i].v;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i >= 0 && i < m_taken)
	{
		value = m_nmap[i].v;
		key = m_nmap[i].k;
		return true;
	}
	else
		return false;
}

void Map::swap(Map& other)
{
	Map replacement = other;
	other = *this;
	*this = replacement;
}

