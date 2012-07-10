// 
// BrickWall.h
//
// Ashok Ghosh (c) 2012 
//
#ifndef brickwall_h
#define brickwall_h

#include <iostream>
#include "BrickBond.h"

const bool  TRUE = 1;
const bool  FALSE = 0;

// abstruct data type to hold permutation of blocks
typedef struct PermTree {
        bool leaf;
	unsigned int bitMap;
	float block;
	PermTree *left;
	PermTree *right;
} PermTree;

// ADT to help loop cache
typedef struct CombTree {
        unsigned int bitMap;
	unsigned int *validPerms;
	int totalMatch;
	int *matchIndex;
} CombTree;

class BrickWall 
{
private:
	float width;
	int height;
	BrickBond *brickBonds;

	// a binary tree to hold all possible combinations of two blocks
	// the leaf nodes are the possible permutations for the given width with bitmaps
	PermTree *head; 
	int totalPerm; // total number of permutations (count of leaf nodes)
	unsigned long long **combArray; // 2D array for loop optimization caching
	CombTree *combTree; // cache to store valid permutation for performance optimization

	// create the permutation of blocks recursively
	bool permutation(float width, PermTree *ptree, unsigned int bitMap=0, float block=0);	
	int permCount(PermTree *ptree); // count the leaf nodes(possible permutations)
	void setCombTree(PermTree *ptree); // copy the leaf node bitmaps to an array of struct

	void deleteTree(PermTree *pt); // free memory allocated by tree
public:
	BrickWall(float width, int height);
	~BrickWall();

	int createPermutations();
	CombTree* getPermutations();
	// calculates all possible permutaions recursively by height of the wall
	unsigned long long validPermutations(int height, CombTree *p, int idx);

	void printPermutations();
};

#endif

