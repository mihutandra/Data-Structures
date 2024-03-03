#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <cmath>
//#include <exception>


using namespace std;

int MultiMap::h(TKey c, int i) const{ //hash value for the KEY
    // Complexity: Total : O(1)
    return (abs(c % m) + i*i) % m;
}


MultiMap::MultiMap() {
    // Complexity: Total : O(m)
    m = MAX;
    std::fill(e, e + m, NULL_TELEM);
    sizee = 0;
}


void MultiMap::add(TKey c, TValue v) {
    // Complexity: Best : O(1) ; Worst: O(m); Total: O(m)
    int i=0; //probe number
    bool gasit = false;
    do {
        int j = h(c, i);
        if (e[j] == NULL_TELEM || e[j] == DELETED ) {
            e[j]= std::make_pair(c,v);
            sizee++;
            gasit = true;
        }
        else i++;
    } while (i < m && !gasit);

}



bool MultiMap::remove(TKey c, TValue v) {

    // Complexity: Best : O(1) ; Worst: O(m); Total: O(m)
    int i = 0;
    int index = h(c, i);
    while (e[index] != NULL_TELEM) {
        if (e[index].first == c && e[index].second == v) {
            e[index] = DELETED;
            sizee--;
            return true;
        }
        i++;
        index = h(c, i);
    }
    return false;

}


vector<TValue> MultiMap::search(TKey c)  {
    // Once the element is found, it retrieves its value, and then continues searching for all subsequent elements with the same key.
    // It adds the values of all such elements to a vector<TValue> and returns it

    // Complexity: Best : O(1) ; Worst: O(m); Total: O(m)
    vector<TValue> values;
    int i = 0;
    int index = h(c, i);
    while (e[index] != NULL_TELEM ) {
        if( e[index].first == c)
            values.push_back(e[index].second);

        i++;
        index = h(c, i);
    }
    return values;
}

int MultiMap::size() const {
    // Complexity: Total : O(1)
    return sizee;
}

bool MultiMap::isEmpty() const {
    // Complexity: Total : O(1)
    if (sizee == 0)
        return true;
    return false;
}

MultiMapIterator MultiMap::iterator() const {
    // Complexity: Total : O(1)
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {

}



