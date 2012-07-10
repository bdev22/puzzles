// 
// BrickBond.h
//
// Ashok Ghosh (c) 2012 
//
#ifndef brickbond_h
#define brickbond_h

#include <iostream>

// BrickBond precalculates the bitmaps for each width where a bond is possible
// Each element in the array only holds one bond position
// The permutation of a bricks will be combination of these bitmap with logical OR
// Dividing the possible bond position a s lowest possible multiplier of 1.5"


const float BLOCK1 = 3;
const float BLOCK2 = 4.5;
const int MAXBONDS = 32; // 32 bonds will fit a max wall width of 48inch

class BrickBond 
{
private:
	unsigned int bondBitMap[MAXBONDS];
public:
	BrickBond(float width);

	unsigned int getBondMap(float width);

	void print();
	void print(float width);
	void printBitMap(unsigned int bmap);
	
};

#endif

