#include "Map.h"
#include "MapIterator.h"

void Map::resize() {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    //We allocate a new array with double capacity somewhere in the computer's memory
    TElem *biggerArray = new TElem[2 * cp];

    //We copy all the elements from the old array into the new array
    for (int i = 0; i < this->n; i++)
        biggerArray[i] = this->e[i];

    //We double the capacity
    this->cp = 2 * this->cp;

    //We release the memory space occupied by the old array
    delete[] this->e;

    //We make the field e to refer the new array (with double capacity)
    this->e = biggerArray;
}
Map::Map() {
    // Complexity: O(1)-all cases
    this->cp = 1;
    this->e = new TElem[this->cp];
    this->n = 0;
}

Map::~Map() {
    // Complexity: O(1)- all cases
	delete[] e;
}

TValue Map::add(TKey c, TValue v) {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    if (this->n == this->cp)
        resize();  // resizing if already full

    int key_index = -1;
    for (int i = 0; i < n; i++) {
        if (this->e[i].first == c) {
            key_index = i; // if elem already exists
            break;
        }
    }
    if (key_index != -1) {
        TValue old_value = this->e[key_index].second;
        this->e[key_index].second = v;
        return old_value;
    } else {
        this->e[this->n].first = c;
        this->e[this->n].second = v;
        this->n++;
        return NULL_TVALUE;
    }
}


TValue Map::search(TKey c) const{
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    for ( int i = 0; i<n; i++) {
        if (this->e[i].first == c)
            return this->e[i].second;
    }
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    bool found = false;
    int value = 0;
    int i = 0;
    while (i<this->n && !found){
        if (this->e[i].first==c){
            found = true;
            value = this->e[i].second;
            for (int j = i; j < n-1; j++){
                this->e[j] = this->e[j+1];
            }
            this->n--;
        } else{
            i++;
        }
    }
    if (found)
        return value;
	return NULL_TVALUE;
}


int Map::size() const {
    //Complexity: O(1)
    return this->n;
}

bool Map::isEmpty() const{
    //Complexity: O(1)
    if (this->n == 0)
        return true;
    return false;
}

MapIterator Map::iterator() const {
    //Complexity: O(1)
	return MapIterator(*this);
}



