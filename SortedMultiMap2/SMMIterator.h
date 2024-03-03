#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
    friend class SortedMultiMap;
private:

    //DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    SMMIterator(const SortedMultiMap& map);
    int currentPosition;
    int* stack; //The stack is used to keep track of the path taken during the iteration process
    int stack_index; //keep track of the current position
    int index_in_da; //current position within the array of values for the current key during iteration in the SMMIterator class.


public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};
