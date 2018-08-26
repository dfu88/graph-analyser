/*
 *  SetOfStrings.h
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#ifndef SetOfStrings_SetOfStrings_h
#define SetOfStrings_SetOfStrings_h
#include <iostream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <stdio.h>

using namespace std;

class SetOfStrings{
protected:
	vector<string> setv;
	vector<string>::iterator p;
public:
	//getters for the private members
	vector<string>::iterator getvitrbegin();
	vector<string>::iterator getvitrend();

	// Set calculation
	SetOfStrings *setUnion(SetOfStrings *set1);
	SetOfStrings *setIntersection(SetOfStrings *set1);
	SetOfStrings *product(SetOfStrings *set1);
	
	// Utility methods
	bool isEmpty();
	bool isEqual(SetOfStrings *s);
	bool isMember(string s);
	bool subset(SetOfStrings *s);
	int size();
	
	// Insert and remove
	void insertElement(string s);
	void removeElement(string s); 
	
	// Getter
	string returnElement(int index);

};

#endif


