// 
// Block coding puzzle
//
// Ashok Ghosh (c) 2012 
//
#include <iostream>
#include <math.h>
#include "BrickBond.h"
#include "BrickWall.h"

using namespace std;

int main (int argc, char** argv) {

        if(argc < 3) {
		cout << "Usage : brickwall <width> <height>\n";
		exit(1);
	}
	int height = atoi(argv[2]);
	if(height <1 || height >10 ) {
		cout << "Wall height should be between 1 and 10.\n";
		exit(0);
	}

	float width=atof(argv[1]);
	if(width<3 || width>48) {
		cout << "Wall width should be between 3 and 48.\n";
		exit(0);
	}
	if(fmod(width,1.5)!=0) {
		#ifdef DEBUG
		cout << "Width do not match the brick size for uniform wall\n";
		#else
		cout << "0\n";
		#endif
		exit(1);
	}

	// create the bitmaps for all possible bond lenghts
	BrickBond brickBond(width);

	#ifdef DEBUG
	brickBond.print();
	#endif
	
	// create bitmaps with all possible permutations with 3" and 4.5" blocks
	BrickWall wall(width, height);
	int perm = wall.createPermutations();

	#ifdef DEBUG
	wall.printPermutations();
	cout<<"Total permutation = "<<perm<<endl;
	#endif

	CombTree  *permutations = wall.getPermutations();
	unsigned long long combinations = 0;
	unsigned long long totalCombinations = 0;

	// calculate combination
	// first row of bricks can be filled with all possible permutations
	// floowing that each row will only allow permutations where the 
	// brick bonds do not allign i.e. the AND with bitmap should be 0
	// validPermutations will recursively calculate all possible allowed permutaions 
	// for each height level spaecified
	for(int i=0; i<perm; i++) {
		if(height > 1) {
			combinations = wall.validPermutations(height-1, &permutations[i], i);
		}
		else {
			combinations = 1;
		}
		totalCombinations += combinations;
		#ifdef DEBUG
		cout<<"perm["<<i<<"]=";brickBond.printBitMap(permutations[i].bitMap);
		cout<<", valid combinations="<<combinations<<", total="<<totalCombinations<<endl;
		#endif
	}
	
	#ifdef DEBUG
	cout<<"Total Combinations = ";
	#endif
	cout<<totalCombinations<<endl;

}


