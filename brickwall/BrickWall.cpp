// 
// BrickWall.cpp
//
// Ashok Ghosh (c) 2012 
//
#include <iostream>
#include "BrickWall.h"

using namespace std;
BrickWall::BrickWall(float wd, int ht)
{
	head = new PermTree;
	width = wd;
	height = ht;
	brickBonds = new BrickBond(wd);
	combArray = NULL;
	combTree = NULL;
}

BrickWall::~BrickWall()
{
	if(brickBonds) delete brickBonds;	
	deleteTree(head);
	if(combArray!=NULL) {
		for(int i=0; i<height; i++) {
			delete combArray[i];
		}
		delete combArray;
	}

	for(int i=0;i<totalPerm;i++) {
		delete combTree[i].validPerms;
		delete combTree[i].matchIndex;
	}
	delete combTree;
}

void BrickWall::deleteTree(PermTree *pt) 
{
	if(pt!=NULL) {
		if(pt->left!=NULL) deleteTree(pt->left);	
		if(pt->right!=NULL) deleteTree(pt->right);	
		delete pt;
	}	

}

CombTree* BrickWall::getPermutations()
{
	return combTree;
}

int BrickWall::createPermutations()
{
	permutation(width, head);
	totalPerm = permCount(head);

	if(combTree==NULL) {
		combTree = new CombTree[totalPerm];
	}
	CombTree *hArray = combTree;
	setCombTree(head);
	combTree = hArray;
	
	if(combArray==NULL) {
		combArray = new unsigned long long*[height];
	}
	for(int i=0; i<height; i++) {
		combArray[i]= new unsigned long long[totalPerm];
		for(int j=0; j<totalPerm; j++) {
			combArray[i][j]=0;
		}
	}
	return totalPerm;
}

bool BrickWall::permutation(float wd, PermTree *ptree, unsigned int bitMap, float block)
{
	ptree->block = block;
	ptree->left = NULL;
	ptree->right = NULL;
	if(wd == 0) {
		ptree->leaf=TRUE;
		ptree->bitMap = bitMap;
	}
	else {
		ptree->leaf=FALSE;
		ptree->bitMap = bitMap | brickBonds->getBondMap(width-wd);
	}

	if(wd >= BLOCK1 ) {
		if(ptree->left==NULL) {
			ptree->left=new PermTree;;
		}
		if(!permutation(wd-BLOCK1,ptree->left,ptree->bitMap, BLOCK1)) {
			if(ptree->left!=NULL) {
				delete(ptree->left);
				ptree->left = NULL;
			}
		}
	}
	if(wd >= BLOCK2 ) {
		if(ptree->right==NULL) {
			ptree->right=new PermTree;;
		}
		if(!permutation(wd-BLOCK2, ptree->right, ptree->bitMap, BLOCK1)) {
			if(ptree->right!=NULL) {
				delete(ptree->right);
				ptree->right = NULL;
			}
		}
	}
	if(wd > 0 && wd < 3) {
		return FALSE; 
	} 
	return TRUE;
}

int BrickWall::permCount(PermTree *ptree) 
{
	if(ptree==NULL) return 0;

	int cnt = permCount(ptree->left) + permCount(ptree->right);
	if(ptree->leaf==TRUE) cnt++;
	return cnt;
}

void BrickWall::setCombTree(PermTree *ptree)
{
	if(ptree!=NULL) {
		setCombTree(ptree->left);
		setCombTree(ptree->right);

		if(ptree->leaf==TRUE) {
			combTree->bitMap = ptree->bitMap;
			combTree->validPerms = NULL;
			combTree++;
		}
	}
}

void BrickWall::printPermutations()
{
	for(int i=0; i< totalPerm; i++) {
		cout << "combTree["<<i<<"]=";
		brickBonds->printBitMap(combTree[i].bitMap);
		cout<<endl;
	}
}

unsigned long long BrickWall::validPermutations(int height, CombTree *p, int idx)
{
	if(p->validPerms==NULL) {
		p->validPerms = new unsigned int[totalPerm];
		p->matchIndex = new int[totalPerm];
		p->totalMatch = 0;
		for(int i=0; i<totalPerm; ++i) {
			if(!(combTree[i].bitMap & p->bitMap)) {
				p->totalMatch++;
				p->matchIndex[p->totalMatch-1] = i;
			}
		}
	}
	unsigned long long validCount=0;
	
	for(int i=0; i<p->totalMatch; ++i) {
		int h = height;
		if(height==1) {
			validCount++;
		}
		else {
			if(0==combArray[--h][p->matchIndex[i]]) {
				combArray[h][p->matchIndex[i]] += 
					validPermutations(h, &combTree[p->matchIndex[i]], p->matchIndex[i]);
			}
			validCount += combArray[h][p->matchIndex[i]];
		}
	}
	return validCount;
}

