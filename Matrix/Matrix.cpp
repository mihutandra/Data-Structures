#include "Matrix.h"
#include <exception>
#include <stdexcept>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {

	size = nrCols * nrLines;
    rows = nrLines;
    cols = nrCols;
    head = nullptr;
    tail = nullptr;
}


int Matrix::nrLines() const {
	return rows;

}


int Matrix::nrColumns() const {
	return cols;
}


TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Invalid position in matrix");
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->line == i && current->column == j) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= rows || j < 0 || j >= cols) {
        throw std::out_of_range("Invalid position in matrix");
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->line == i && current->column == j) {
            int old_value = current->value;
            current->value = e;
            return old_value;
        }
        current = current->next; // Move to the next node in the list
    }
    // if we reach this point, it means that the element at position (i,j) was 0, so we need to add a new node
    Node* new_node = new Node(i, j, e); // make a new Node of line i, column c, value e
    if (head == nullptr) {
        head = tail = new_node; // the matrix was empty, now it's not :D
    } else {
        Node* prev = nullptr;
        Node* current = head;

        while (current != nullptr && current->line < i) {
            prev = current;
            current = current->next;
        }
        /*starts by traversing the linked list from the head node until it finds a node whose line is greater than or equal to the given line 'i'.
          Then, it further traverses the linked list from that node until it finds a node whose line is greater than 'i'
          or whose line is equal to 'i' but whose column is greater than or equal to the given column 'j'.
          At this point, the new node is inserted in the doubly linked list between the 'prev' and 'current' nodes. */

        while (current != nullptr && current->line == i && current->column < j) {
            prev = current;
            current = current->next;
        }
        //if the 'prev' node is null, it means that the new node needs to be inserted at the beginning
        if (prev == nullptr) {
            new_node->next = head;
            head->prev = new_node;
            head = new_node; }

        //If the 'current' node is null, it means that the new node needs to be inserted at the end
        else if (current == nullptr) {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node; }

        //If neither 'prev' nor 'current' is null, it means that the new node needs to be inserted in between them.
         else {
            prev->next = new_node;
            new_node->prev = prev;
            new_node->next = current;
            current->prev = new_node;
        }
    }
    return 0;
}


