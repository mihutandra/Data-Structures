#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    // Complexity: all O(1)
    this->current=0;
}


void MapIterator::first() {
    // Complexity: all O(1)
    this->current=0;
}


void MapIterator::next() {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    if (!valid()){
        throw exception();
    } else {
        this->current++;
    }
}


TElem MapIterator::getCurrent(){ // Complexity: all O(1)

    if (!valid()){
        throw exception();
    } else {
        return this->map.e[this->current];
    }

}


bool MapIterator::valid() const {
    return  (this->current < this->map.n);

}

// Complexitiy: Best :  ; Worst:


