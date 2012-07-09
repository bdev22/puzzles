// 
// BrickBond.cpp
//
// Ashok Ghosh (c) 2012 
//
#include <iostream>
#include "BrickBond.h"

using namespace std;

BrickBond::BrickBond(float width)
{
	// initialize bitmap array
	for(int i=0;i<MAXBONDS;i++) {
		bondBitMap[i]=0;
	}

	unsigned int bmap = 0xFFFFFFFF;
	int i=1;
	unsigned int j=1,prev=bmap;
	for(float f=1.5; f <=width ; f+=1.5,i++) {
	        j=bmap<<i;
	        bondBitMap[i]=(~j)^(~prev);
		prev=j;
	}

}

unsigned int BrickBond::getBondMap(float width)
{
        if(width < 1.5) return bondBitMap[0];
	return bondBitMap[(int)(width/1.5)-1];
}

void BrickBond::print() 
{
	for(int i=1;i<MAXBONDS;i++) {
		if(bondBitMap[i]>0) {	
			cout<< "bondBitMap["<<i<<"]=";
			printBitMap(bondBitMap[i]);
			cout<<endl;
		}
	}
}

void BrickBond::print(float width) 
{
	unsigned int bitMap = getBondMap(width);
	printBitMap(bitMap);
}

void BrickBond::printBitMap(unsigned int bmap) 
{
	int s=0;
	for (int b = 31; b >= 0; b--) {
		//cout << ((bmap >> b) & 1);
		unsigned int bb = bmap>>b;
		if(bb==1 && s==0) s=1;
		if(s) {
			cout << ((bmap >> b) & 1);
		}
		else {
			cout << '*';
		}
	}
}
