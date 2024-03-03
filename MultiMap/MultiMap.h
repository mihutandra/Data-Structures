#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
#define DELETED pair<int,int>(-444444, -444444)
#define  MAX 100000
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
    int m; //number of locations in the hash table
    TElem e[MAX]; //the array of elements - vector static
    //the hash function
    int h(TKey c, int i) const;
    int sizee;
public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c);

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//descturctor
	~MultiMap();

    // using a hash table with open addressing and quadratic probing in which(key,value)pairs are stored.If a key has
    // multiple values, it appears in multiple pairs.
};

