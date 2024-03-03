#pragma once
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

class PriorityQueue {
private:

    static const int cap = 50000; //capacity
    Element elements[cap]; //array of elements of generic type Elements

    int nextLink[cap]; //array with next links
    int prevLink[cap]; //array with previous links

    int first; //head of the list
    int firstEmpty; // first empty element of the array

    Relation relation;


    //return the empty slot in the list
    int allocate();

    //deallocates the space of index i
    void deallocate(int i);

    //creates a node
    int createNode(TElem e, TPriority p);
public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//destructor
	~PriorityQueue();

    //ADT PriorityQueue– using a DLLA on an array with (element,priority)pair ordered based on a relation between the priorities.
};