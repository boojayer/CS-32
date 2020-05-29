// ExpandableHashMap.h
#include <functional>
#include <vector>
#include <utility>
#include <list>


// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef HASH_MAP
#define HASH_MAP


template<typename KeyType, typename ValueType>

class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;


	// The associate method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts
	// a new association into the hashmap with that key/value pair. If there is
	// already an association with that key in the hashmap, then the item
	// associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
	void associate(const KeyType& key, const ValueType& value);

	// If no association exists with the given key, return nullptr; otherwise,
	// return a pointer to the value associated with that key. This pointer can be
	// used to examine that value, and if the hashmap is allowed to be modified, to
	// modify that value directly within the map (the second overload enables
	// this). Using a little C++ magic, we have implemented it in terms of the
	// first overload, which you must implement.
	const ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

private:
	std::vector<std::list<std::pair<KeyType, ValueType>>> m_hash;
	int m_size;
	double maxLoad;
	int NUM_BUCKETS;

	unsigned int getBucketNumber(const KeyType& key) const
	{
		unsigned int hasher(const KeyType & k);

	    unsigned int temp = hasher(key);
		return temp % NUM_BUCKETS;
	}
};



template <typename KeyType, typename ValueType>
ExpandableHashMap<typename KeyType, typename ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
	m_size = 0;
	NUM_BUCKETS = 8;
	m_hash.resize(8);
	if (maximumLoadFactor <= 0.0)
		maxLoad = .5;
	else
		maxLoad = maximumLoadFactor;
}

template <typename KeyType, typename ValueType>
ExpandableHashMap<typename KeyType, typename ValueType>::~ExpandableHashMap()
{
}

template <typename KeyType, typename ValueType>
void ExpandableHashMap<typename KeyType, typename ValueType>::reset()
{
	m_hash.clear();
	m_size = 0;
	NUM_BUCKETS = 8;
	m_hash.resize(NUM_BUCKETS);
}

template <typename KeyType, typename ValueType>
int ExpandableHashMap<typename KeyType, typename ValueType>::size() const
{
	return m_size;
}

template <typename KeyType, typename ValueType>
void ExpandableHashMap<typename KeyType, typename ValueType>::associate(const KeyType& key, const ValueType& value)
{
	
	if (m_size >= maxLoad * NUM_BUCKETS)
	{
		std::vector<std::list<std::pair<KeyType, ValueType>>> temp;
		NUM_BUCKETS *= 2;
		temp.resize(NUM_BUCKETS);
		for (auto& bucketLIst : m_hash)
		{
			for (auto& listNode : bucketLIst)
			{
				unsigned int b = getBucketNumber(listNode.first);
				temp[b].push_back(std::make_pair(listNode.first, listNode.second));
			}
		}
		m_hash.clear();
		m_hash.resize(NUM_BUCKETS);
		m_hash = temp;
		temp.clear();
	}

	
	ValueType* val = find(key);
	if (val != nullptr)
	{
		*val = value;
	}
	else
	{
		unsigned int bucket = getBucketNumber(key);
		std::pair<KeyType, ValueType> temp(key, value);
		m_hash[bucket].push_back(temp);
		m_size++;
	}
}

template <typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<typename KeyType, typename ValueType>::find(const KeyType& key) const
{
	unsigned int f = getBucketNumber(key);
	const ValueType* ptr = nullptr;
		if (!m_hash[f].empty()) 
		{
			typename std::list<std::pair<KeyType, ValueType>>::const_iterator it = m_hash[f].begin();
			while (it != m_hash[f].end()) 
			{
				if (it->first == key) 
				{
					ptr = &(it->second);
					return ptr;
				}
				it++;
			}
		}
	return nullptr;  
}

#endif //HASH_MAP
