#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    //This setup allows the iterator to start iterating from the smallest key and progress in ascending order
    this->stack = new int[this->map.uniqueKeys];
    this->stack_index = -1;
    this->index_in_da = 0;
    int current = this->map.tree->root;
    while(current != -1) //traverses the left children of the nodes starting from the root until reaching the leftmost node
    {
        this->stack_index++;
        this->stack[this->stack_index] = current;
        current = this->map.tree->left[current];
    }
    if (this->stack_index == -1) //represents the index of the rightmost node in the binary search tree
        this->currentPosition = -1; //bst was empty
    else
        this->currentPosition = this->stack[this->stack_index];
}
// Best Case: Theta(1) when the root of the tree holds the element having the smallest key
// Worst Case: Theta(number of keys) when the elements were added in descending order (the tree is degenerate)
// Total Complexity: O(number of keys)

void SMMIterator::first(){
    delete[] this->stack;
    this->stack = new int[this->map.uniqueKeys];
    this->stack_index = -1; //empty stack
    this->index_in_da = 0;
    int current = this->map.tree->root;
    while (current != -1)//traverses the left children of the nodes starting from the root until reaching the leftmost node
    {
        this->stack_index++;
        this->stack[this->stack_index] = current;
        current = this->map.tree->left[current]; //go left
    }
    if (this->stack_index == -1) // stack_index represents the index of the rightmost node in the binary search tree
        this->currentPosition = -1; // tree was empty
    else
        this->currentPosition = this->stack[this->stack_index];
}
// Best Case: Theta(1) when the root of the tree holds the element having the smallest key
// Worst Case: Theta(number of keys) when the elements were added in descending order (the tree is degenerate)
// Total Complexity: O(number of keys)


void SMMIterator::next(){ //moving to the next value within the current key or by traversing to the next key with a larger value
    if (this->currentPosition == -1)
        throw exception();
    index_in_da++;
    // We haven't finished traversing the array of values for the current key
    if (this->map.tree->elements[this->currentPosition].nrValues > this->index_in_da) //more values to be iterated for the current key
    {
        return;
    }
    // We reached the end of the array of values for the current key, set a new current key
    this->index_in_da = 0; //prepare for new key
    int current = this->stack[this->stack_index];
    this->stack_index--; //decremented to move up one level in the binary search tree
    // Test if we can go right
    if (this->map.tree->right[current] != -1)
    { // If a right child exists, it means there are more keys with larger values to be iterated
        current = this->map.tree->right[current];
        while (current != -1)
        { // iteratively moves to the leftmost child until reaching a leaf node
            this->stack_index++;
            this->stack[this->stack_index] = current;
            current = this->map.tree->left[current];
        }
    }
    // The iterator is no longer valid
    if (this->stack_index == -1)
        this->currentPosition = -1; // no more keys to be iterated
    else  // more keys to be iterated
        this->currentPosition = this->stack[this->stack_index]; //the new current key.

}
// Best Case: Theta(1) when fetching the next element from the array of values for a specific key
// Worst Case: Theta(number of keys) when the tree is degenerate
// Total complexity: O(number of keys)

bool SMMIterator::valid() const{
    if (this->currentPosition != -1)
        return true;
    return false;
}
// Complexity: Theta(1)

TElem SMMIterator::getCurrent() const{
    if (this->currentPosition == -1)
        throw exception();
    TElem elem;
    elem.first = this->map.tree->elements[this->currentPosition].key;
    elem.second = this->map.tree->elements[this->currentPosition].values[this->index_in_da];
    return elem;
}
// Complexity: Theta(1)