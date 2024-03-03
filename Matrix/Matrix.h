#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:

	class Node{
    public:
        int line, column, value;
        Node* next;
        Node* prev;
        Node(int l, int c, int v) : line(l), column(c), value(v), next(nullptr), prev(nullptr) {}
    };

    int rows;
    int cols;
    int size;
    Node* head;
    Node* tail;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

};

/*ADTMatrix–represented as a sparse matrix, using a DLL with <line,column,value>triples (value≠0),
 * ordered lexicographically considering the line and column of every element.*/