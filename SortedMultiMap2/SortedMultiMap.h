#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

/// SMM on BST with dynamic allocation and for every key the values are stored in a dynamic array

typedef struct // node structure
{
    TKey key; // key
    TValue* values; // dynamic array of values
    int capacity; //capacity of array
    int nrValues; // nr of actual elems in the array

} LA;

typedef struct { // BST Structure
    LA* elements; // elements of the BST with dynamic allocation
    int* left; // LEFT child
    int* right; // RIGHT child
    int* parent; // PARENT
    int capacity; // capacity of the BST
    int root; // ROOT
    int firstEmpty; // first empty position of the array

} BST;


class SortedMultiMap {
    friend class SMMIterator;
private:
    BST* tree;
    int nrElements; // total nr of (key,value)
    int uniqueKeys; // total nr of unique_keys in BST
    Relation r;

    void resizeSingleElement(int currentPosition); // resize de dy_arr of values for a key
    void resize();// resize the dy_arr for the BST

    int maximum(int position) const; //maximum element
    bool remove_value(int position, TValue value); // Removes the specified value from the array matched to the key at the given position

public:

    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    //returns a vector with all the keys from the SortedMultiMap 
    vector<TKey> keySet() const;


    // destructor
    ~SortedMultiMap();
};