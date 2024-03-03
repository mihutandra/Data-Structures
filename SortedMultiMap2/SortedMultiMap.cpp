#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <vector>

using namespace std;

void SortedMultiMap::resizeSingleElement(int currentPosition){
// Resizes the dynamic array where the values associated to a unique key are stored

    int newCap = 2 * this->tree->elements[currentPosition].capacity;
    TValue* newArr = new TValue[newCap];
    for (int i = 0; i < newCap; i++)
    {
        if (i < this->tree->elements[currentPosition].capacity)
        {
            newArr[i] = this->tree->elements[currentPosition].values[i];
        }
        else
            newArr[i] = NULL_TVALUE;
    }
    delete this->tree->elements[currentPosition].values;
    this->tree->elements[currentPosition].capacity = newCap;
    this->tree->elements[currentPosition].values = newArr;
}
// Complexity: Theta(capacity of the array of values)

void SortedMultiMap::resize()
{
    int newCapacity = 2*this->tree->capacity;
    LA* newElems = new LA[newCapacity];
    int* newLeft = new int[newCapacity];
    int* newRight = new int[newCapacity];
    int* newParent = new int[newCapacity];
    for (int i = 0; i < newCapacity - 1; i++)
    {
        if (i < this->tree->capacity)
            // Copy old values
        {
            newElems[i] = this->tree->elements[i];
            newLeft[i] = this->tree->left[i];
            newRight[i] = this->tree->right[i];
            newParent[i] = this->tree->parent[i]; }
        else
        {
            // Link new free positions
            newLeft[i] = i + 1;
            newRight[i] = -1;
            newParent[i] = -1;
            newElems[i].capacity = 0;
            newElems[i].values = nullptr;
            newElems[i].nrValues = 0; }
    }
    // Also fill last entry
    newLeft[newCapacity-1] = -1;
    newRight[newCapacity-1] = -1;
    newParent[newCapacity-1] = -1;
    newElems[newCapacity-1].capacity = 0;
    newElems[newCapacity-1].values = nullptr;
    newElems[newCapacity-1].nrValues = 0;
    delete[] this->tree->elements;
    delete[] this->tree->left;
    delete[] this->tree->right;
    delete[] this->tree->parent;
    this->tree->firstEmpty = this->tree->capacity;
    this->tree->capacity = newCapacity;
    this->tree->elements = newElems;
    this->tree->left = newLeft;
    this->tree->right = newRight;
    this->tree->parent = newParent;
}
// Complexity: Theta(capacity of the array where keys are stored)

SortedMultiMap::SortedMultiMap(Relation r) {
    this->r = r;
    this->tree = new BST;
    this->tree->capacity = 100;
    this->tree->elements = new LA[100];
    this->tree->left = new int[100];
    this->tree->right = new int[100];
    this->tree->parent = new int[100];
    for (int i = 0; i < 100; i++)
    {
        this->tree->elements[i].capacity = 0;
        this->tree->elements[i].values = nullptr; // no values yet
        this->tree->elements[i].nrValues = 0;
        if (i < 99)
            // Link free positions
        {
            this->tree->left[i] = i + 1; //indicating the next free position
        }
        else // it means it's the last element that-s why -1
        {
            this->tree->left[i] = -1;
        }
        this->tree->right[i] = -1; //indicating that there is no right child initially
        this->tree->parent[i] = -1; //indicating that there is no parent initially
    }
    this->tree->firstEmpty = 0;
    this->tree->root = -1; //indicating that the BST is initially empty
    this->nrElements = 0;
    this->uniqueKeys = 0;
}
// Complexity: Theta(capacity of the array where keys are stored)

void SortedMultiMap::add(TKey c, TValue v) { //considering various cases such as an empty multimap, existing keys, and finding the appropriate position in the binary search tree to maintain the sorted order based on the relation.

    /// Adding the first element - this will become the root of our tree
    if (this->nrElements == 0) // if empty create the necessary fields
    {
        this->tree->elements[0].key = c;
        // Allocate space for an array of values
        this->tree->elements[0].capacity = 1;
        this->tree->elements[0].values = new TValue[1];
        this->tree->elements[0].values[0] = v;
        this->tree->elements[0].nrValues = 1;
        this->tree->root = 0;
        this->tree->firstEmpty = 1;
        this->tree->left[0] = -1;
        this->tree->right[0] = -1;
        this->nrElements++;
        this->uniqueKeys++;
        return;
    }
    /// The element that we want to add is not the first one, we need to find its position in the tree
    // We start from the root
    int currentPosition = this->tree->root;
    // We also need to find where its parent is so that we can update tha 'parent' array accordingly
    int parent = -1;
    while (currentPosition != -1) //proceeds to find the appropriate position to add the new element
    {
        if (this->tree->elements[currentPosition].key == c)
            /// If the key of the new element is already in the map, we add its value to the array of values
        {
            // If the array of values is full we need to resize => Theta(capacity of the array of values)
            if (this->tree->elements[currentPosition].capacity == this->tree->elements[currentPosition].nrValues)
                this->resizeSingleElement(currentPosition); //resize value_array
            // We add it to the next free position
            this->tree->elements[currentPosition].values[this->tree->elements[currentPosition].nrValues] = v;
            this->tree->elements[currentPosition].nrValues++;
            this->nrElements++;
            return;
        }
        else if (this->r(c, this->tree->elements[currentPosition].key))
        {
            // If the key of the new element is smaller w.r.t the relation, we go left
            parent = currentPosition;
            currentPosition = this->tree->left[currentPosition];
        }
        else
        {
            // If the key of the new element is larger w.r.t the relation, we go right
            parent = currentPosition;
            currentPosition = this->tree->right[currentPosition];
        }
    }

    // We reached this part meaning that currentPosition is -1
    ///  the new element must be given a new entry in the array
    // Resize is needed
    if (this->tree->firstEmpty == -1)
        this->resize();
    // Occupy the first free position
    int freePos = this->tree->firstEmpty;
    // Initialize a new array of values
    this->tree->elements[freePos].key = c;
    this->tree->elements[freePos].capacity = 1;
    this->tree->elements[freePos].values = new TValue[1];
    this->tree->elements[freePos].values[0] = v;
    this->tree->elements[freePos].nrValues = 1;
    // Set the links to the parent accordingly (if smaller or greater)
    if (this->r(c, this->tree->elements[parent].key))
        this->tree->left[parent] = freePos;
    else
        this->tree->right[parent] = freePos;
    this->tree->firstEmpty = this->tree->left[freePos];
    this->tree->left[freePos] = -1;
    this->tree->right[freePos] = -1;
    this->tree->parent[freePos] = parent;
    this->nrElements++;
    this->uniqueKeys++;
}
// Best Case: The element is the first one to be added to the map.
// We simply allocate space for it, no resize needed => Theta(1)

// Worst Case: The worst case occurs when a resize of any type is to be performed (and the values were added in order so the tree is degenerate)
// This could mean the case where need to resize the array in which we keep the values => Theta(capacity of the array of values)
// Or a resize of the array where we keep the keys => Theta(capacity of the array of keys)
// Notice that these two cases are mutually exclusive. We will never have to resize both of them
// The largest of these respective capacities will thus give us the worst case complexity
// Theta(capacity of the array of keys + capacity of the array of values)

// Total complexity: O(capacity of the array of keys + capacity of the array of values)

vector<TValue> SortedMultiMap::search(TKey c) const {
    if(this->nrElements == 0)
        return {};
    // Here we store all the values associated with the given key, if it exists in the map
    vector<TValue> result;
    // Start searching from the root
    int currentPosition = this->tree->root;
    bool found = false;
    while (currentPosition != -1 && !found)
    {
        if (this->tree->elements[currentPosition].key == c)
            found = true;
        else if (this->r(this->tree->elements[currentPosition].key, c))
            // If the key of the searched element is larger w.r.t the relation, we go right
            currentPosition = this->tree->right[currentPosition];
        else
            // If the key of the searched element is smaller w.r.t the relation, we go left
            currentPosition = this->tree->left[currentPosition];
    }
    // currentPosition is -1, the element was not found
    if (!found)
        return {};
    // Add the values from the values array to vector
    for (int i = 0; i < this->tree->elements[currentPosition].nrValues; i++)
    {
        result.push_back(this->tree->elements[currentPosition].values[i]);
    }
    return result; // array of values
}
// Best Case: The element that we search for is the root of the binary tree => Theta(number of values associated to the key)
// Worst Case: The keys were added into the map in order (the tree is degenerate) => Theta(number of keys + number of values associated to the given key)
// Total complexity: O(number of keys + number of values associated to the given key)

bool SortedMultiMap::remove(TKey c, TValue v) {
    if (this->nrElements == 0) // if empty
        return false;
    /// Start from the root to search for the element to be deleted
    int currentPosition = this->tree->root;
    while (currentPosition != -1)
    {
        if (this->tree->elements[currentPosition].key == c)
            // We found the element with the given key
        {
            if (!this->remove_value(currentPosition, v))
                /// But the value that we wanted to remove is not actually in the map
                return false;
            if (this->tree->elements[currentPosition].nrValues > 0)
                // We removed the value successfully, but there are more values associated with the key
                return true;
            // We removed all the values associated with the key, so we need to remove the key from the map completely
            /// If the given key is associated to a node of the binary search tree with NO CHILDREN
            // We simply remove it, now its parent has one less child
            if (this->tree->left[currentPosition] == -1 && this->tree->right[currentPosition] == -1)
            {
                int parent = this->tree->parent[currentPosition];
                if (parent == -1)
                    /// We remove the only element which is the root
                    this->tree->root = -1;
                else
                {
                    /// Find out if the element to be deleted was a right child or a left child
                    if (this->r(c, this->tree->elements[parent].key))
                        this->tree->left[parent] = -1;
                    else
                        this->tree->right[parent] = -1;
                }
                // Set the next free position to the now unoccupied slot in the array
                this->tree->left[currentPosition] = this->tree->firstEmpty;
                this->tree->firstEmpty = currentPosition;
                this->tree->parent[currentPosition] = -1;
                this->uniqueKeys--;
                return true;
            }
            else if ((this->tree->left[currentPosition] != -1 && this->tree->right[currentPosition] == -1) || (this->tree->left[currentPosition] == -1 && this->tree->right[currentPosition] != -1))
            {
                /// The node to be removed had ONE CHILD
                int parent = this->tree->parent[currentPosition];
                // If the node to be removed is the root, its child becomes the new root
                if (parent == -1)
                {
                    if (this->tree->left[currentPosition] != -1) //updates the appropriate links to bypass the current node
                        this->tree->root = this->tree->left[currentPosition];
                    else
                        this->tree->root = this->tree->right[currentPosition];
                }
                else
                {
                    // We assign the child of the node to be deleted to its parent
                    if (this->r(c, this->tree->elements[parent].key)) //determines whether the node is a left child or a right child of its parent
                    {   // here-> left child
                        if (this->tree->left[currentPosition] != -1)
                            this->tree->left[parent] = this->tree->left[currentPosition]; //the left child of the parent is updated to point to the left child of the node to be deleted
                        else
                            this->tree->left[parent] = this->tree->right[currentPosition];

                    }
                    else // if right child
                    {
                        if (this->tree->left[currentPosition] != -1)
                            this->tree->right[parent] = this->tree->left[currentPosition];
                        else
                            this->tree->right[parent] = this->tree->right[currentPosition];
                    }
                }
                // We make the parent of the node to be deleted the parent of its child
                if(this->tree->left[currentPosition] != -1)
                    this->tree->parent[this->tree->left[currentPosition]] = this->tree->parent[currentPosition];
                else
                    this->tree->parent[this->tree->right[currentPosition]] = this->tree->parent[currentPosition];
                // Set the next free position to the now unoccupied slot in the array
                this->tree->left[currentPosition] = this->tree->firstEmpty;
                this->tree->firstEmpty = currentPosition;
                this->tree->parent[currentPosition] = -1;
                this->uniqueKeys--;
                return true;

            }
            else
            {
                /// The node to be deleted has 2 CHILDREN
                // Let us now find its predecessor in the tree, namely the maximum element of the left subtree
                // It is this element that we will actually remove
                int maximum = this->maximum(this->tree->left[currentPosition]); // finds the maximum element in the left subtree of the node to be deleted
                // We copy the information from there to the root
                this->tree->elements[currentPosition] = this->tree->elements[maximum]; //This effectively replaces the node to be deleted with its predecessor
                int parent = this->tree->parent[maximum];
                if(parent == this->tree->root) //parent is the root of the tree
                    this->tree->left[parent] = -1;
                else //maximum node is somewhere within the left subtree of the currentPosition node
                    this->tree->right[parent] = -1;
                // Set the next free position to the now unoccupied slot in the array
                this->tree->left[maximum] = this->tree->firstEmpty;
                this->tree->firstEmpty = maximum;
                this->tree->parent[maximum] = -1;
                this->uniqueKeys--; // since one key has been removed
                return true; //successful removal
            }

        }
        else if (this->r(this->tree->elements[currentPosition].key, c)) // we still search....
            // If the key of the searched element is larger w.r.t the relation, we go right
            currentPosition = this->tree->right[currentPosition];
        else
            // If the key of the searched element is smaller w.r.t the relation, we go left
            currentPosition = this->tree->left[currentPosition];

    }
    return false;
}
// Best Case: The key-value pair to be deleted is stored in the root of the tree and the root has either no children or one child
/// BC:: Theta(number of values associated with the given key)

// Worst case: The key-value pair to be deleted is stored in the root of the tree and the root has two children
// In this case, we will need to replace the root with its predecessor and thus search for it
// Say the tree is degenerate, so we will actually have the complexity be
/// WC: Theta(number of keys + number of values associated to the given key)
/// Total complexity: Theta(number of keys + number of values associated to the given key)



int SortedMultiMap::size() const {
    return this->nrElements;
}
// Complexity: Theta(1)

bool SortedMultiMap::isEmpty() const {
    return this->nrElements == 0;
}
// Complexity: Theta(1)


int SortedMultiMap::maximum(int position) const
{ // position - starting position in the BST to begin the search for the maximum element
    if (position == -1)  // empty BST
        return -1;
    while (this->tree->right[position] != -1) //as long as the right child of the current position is not -1, indicating there is a larger element to the right
    {
        position = this->tree->right[position]; // right-> larger elem
    }
    return position; //returns the final position, which represents the maximum element in the BST
}
// Best Case: The maximum element is at the given position => Theta(1)
// Worst Case: The keys were added in ascending order, the tree is degenerate => Theta(number of keys)
// Total Complexity: O(number of keys)


bool SortedMultiMap::remove_value(int position, TValue value)
// Removes the specified value from the array matched to the key at the given position
{
    int remove_pos = -1; //to keep track of the position of the value to be removed in the array of values.

    // Find position of the value to be removed in the array of values
    for (int i = 0; i < this->tree->elements[position].nrValues; i++)
    {
        if (this->tree->elements[position].values[i] == value)
        {
            remove_pos = i;
            break;
        }
    }
    // If not found just return false
    if (remove_pos == -1)
        return false;
    // the remove_pos is not -1, it means the specified value was found in the array of values
    // shifts back the values that come after the deleted value in the array
    for (int i = remove_pos; i < this->tree->elements[position].nrValues-1; i++)
    {  //Each value is replaced with the next value in the array.
        this->tree->elements[position].values[i] = this->tree->elements[position].values[i + 1];
    }
    this->tree->elements[position].nrValues--;
    this->nrElements--; // update the total number of key-value pairs
    return true;
}
// Total complexity: Theta(number of values associated to the given position)


SMMIterator SortedMultiMap::iterator() const {
    return {SMMIterator(*this)};
}
// complexity: Theta(1)



SortedMultiMap::~SortedMultiMap() {
    for (int i = 0; i < this->tree->capacity; i++)
    {
        if (this->tree->elements[i].nrValues != 0)
            delete[] this->tree->elements[i].values;
    }
    delete[] this->tree->elements;
    delete[] this->tree->left;
    delete[] this->tree->right;
    delete[] this->tree->parent;
    delete this->tree;
}
// Complexity: Theta(capacity of the array)