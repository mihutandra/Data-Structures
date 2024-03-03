
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(cap)
    first = -1;
    firstEmpty = 0; //no empty spaces

    //we initialize the list of links between the elements
    for(int i=0; i<cap-1; i++){
        nextLink[i]=i+1;
    }
    for(int i=1; i<cap; i++){
        prevLink[i]=i-1;
    }

    this->relation = r;
}

int PriorityQueue::allocate() {
    // Complexity: Best : O(1) ; Worst: O(1); Total: O(1)

    int i = firstEmpty; // get the index of the first empty slot
    if (i != -1) { // check if there are any empty slots
        firstEmpty = nextLink[firstEmpty]; // update the first empty slot to the next one
        return i; // return the index of the first empty slot
    } else {
        return -1; // return -1 if there are no empty slots
    }
}

void PriorityQueue::deallocate(int i) {
    // Complexity: Best : O(1) ; Worst: O(1); Total: O(1)

    nextLink[i] = firstEmpty;
    prevLink[i] = -1;
    if(firstEmpty != -1)
        prevLink[firstEmpty] = i;
}

int PriorityQueue::createNode(TElem e,TPriority p){
    // Complexity: Best : O(1) ; Worst: O(1); Total: O(1)

    int i=allocate();   // allocate node for creation
    if(i!=-1) {  // if successful allocation
        this->elements[i]=std::make_pair(e,p);
        nextLink[i]= -1;
        prevLink[i] = -1;
    }
    return i;
}

void PriorityQueue::push(TElem e, TPriority p) {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)

    int newNode = createNode(e, p);
    if (isEmpty()) {
        first = newNode;
        prevLink[first] = -1;
        nextLink[first] = -1;
    } else {
        int current = first;
        while (current != -1 && !relation(p, elements[current].second)) {
            current = nextLink[current];
        }

        if (current == first) {
            first = newNode;
            nextLink[newNode] = current;
            prevLink[current] = newNode;
        } else {
            int prev = prevLink[current];
            nextLink[prev] = newNode;
            prevLink[newNode] = prev;
            prevLink[current] = newNode;
            nextLink[newNode] = current;

        }
    }
}


Element PriorityQueue::pop() {
    // Complexity: Best : O(1) ; Worst: O(n); Total: O(n)
    if (isEmpty()) {
        throw exception();
    }
    else {
        int index = first;
        for (int i = first; i != -1; i = nextLink[i]) {
            if (relation(elements[i].second, elements[index].second))
                index = i;
        }
        Element result = elements[index];
        if (index == first) {
            first = nextLink[first];
            if (first != -1) {
                prevLink[first] = -1;
            }
        }
        else if (index == firstEmpty - 1) {
            firstEmpty--;
        }
        else {
            nextLink[prevLink[index]] = nextLink[index];
            prevLink[nextLink[index]] = prevLink[index];
        }
        return result;
    }
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
    /*iterates through the queue to find the element with the highest priority
     * with respect to the order relation. It does this by keeping track of the
     * maximum element seen so far (maxIndex) and comparing it to each element in the queue*/
    // Complexity: Best : O(1) ; Worst: O(1); Total: O(1)
    if (isEmpty()) {
        throw runtime_error("Queue is empty!");
    }
    return elements[first];
}

bool PriorityQueue::isEmpty() const {
    // Complexity: Best : O(1) ; Worst: O(1); Total: O(1)
    if(first == -1)
        return true;
    return false;
}


PriorityQueue::~PriorityQueue() {
    //TODO
};

