#include "MultiMapIterator.h"
#include "MultiMap.h"

void MultiMapIterator::move() {
    while ((current < col.size()) && col.e[current].first == -11111)
        current++;
}

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    current = 0;
    move();
}

TElem MultiMapIterator::getCurrent() const{
    if (!valid()){
        throw std::exception();
    }
    return col.e[current];
}

bool MultiMapIterator::valid() const {
    return (current < col.sizee);
}

void MultiMapIterator::next() {
    if (!valid()){
        throw std::exception();
    }
    current++;
    move();
}

void MultiMapIterator::first() {
	current = 0;
    move();
}


