#include <iostream>
#include "Map.h"
using namespace std;


Map::Map()
{
	m_size = 0;
}

bool Map::empty() const
{
	if (m_size == 0)
		return true;
	else
		return false;
}

int Map::size() const
{
	return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (m_size >= DEFAULT_MAX_ITEMS)
		return false;
	for (int i = 0; i <= m_size; i++)
	{
		if (m_map[i].k == key)
		{
			return false;
		}
	}
		m_map[m_size].k = key;
		m_map[m_size].v = value;
		m_size++;
		return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i <= m_size; i++)
	{
		if (m_map[i].k == key)
		{
			m_map[i].v = value;
			return true;
		}
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].k == key)
		{
			m_map[i].v = value;
			return true;
		}
	}
	if (m_size == DEFAULT_MAX_ITEMS)
		return false;
	else
	{
		m_map[m_size].v = value;
		m_map[m_size].k = key;
		m_size++;
		return true;
	}
}

bool Map::erase(const KeyType& key)
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].k == key)
		{
			if (m_size == 1)
			{
				m_size = 0;
				return true;
			}
			m_map[i] = m_map[m_size - 1];
			m_size--;
			return true;
		}
	}
	return false;
}

bool Map::contains(const KeyType& key) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].k == key)
		{
			return true;
		}
	}
	return false;
}


bool Map::get(const KeyType& key, ValueType& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_map[i].k == key)
		{
			value = m_map[i].v;
			return true;
		}
	}
	return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i >= 0 && i < m_size)
	{
		key = m_map[i].k;
		value = m_map[i].v;
		return true;
	}
	else
		return false;
}

void Map::swap(Map& other)
{
	Map tempMap = other;

	other.m_size = m_size;
	for (int i = 0; i < m_size; i++)
	{
		other.m_map[i].k = m_map[i].k;
		other.m_map[i].v = m_map[i].v;
	}

	m_size = tempMap.m_size;
	for (int i = 0; i < m_size; i++)
	{
		m_map[i].k = tempMap.m_map[i].k;
		m_map[i].v = tempMap.m_map[i].v;
	}
}
