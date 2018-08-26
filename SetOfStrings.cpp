/*
 *  SetOfStrings.cpp
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#include "SetOfStrings.h"
#include <iostream>
#include <algorithm>

using namespace std;

//Getter for private members
//Returns an iterator pointing to the beginning of the private vector
vector<string>::iterator SetOfStrings::getvitrbegin(){
    p=setv.begin();
    return p;
}

//Getter for private members
//Returns an iterator pointing to the end of the private vector
vector<string>::iterator SetOfStrings::getvitrend(){
    p=setv.end();
    return p;
}

bool SetOfStrings::isEmpty()
{
	if(setv.empty()) return true;
	else return false;
}

int SetOfStrings::size(){
	return (int) setv.size();
}

bool SetOfStrings::isMember(string s)
{
	p=setv.begin();
	while(p!=setv.end()){
		if(*p==s)return true;
		++p;
	}
	return false;
}

void SetOfStrings::insertElement(string s)
{
	if(!isMember(s)){
		setv.push_back(s);
	}
}

void SetOfStrings::removeElement(string s)
{
	setv.erase(std::remove(setv.begin(), setv.end(), s), setv.end());
}

//creates a union set of two respective sets, setv and input set s
SetOfStrings *SetOfStrings::setUnion(SetOfStrings *s)
{
	SetOfStrings *s1 = new SetOfStrings();
	p=setv.begin();
	while(p!=setv.end()){
		s1->insertElement(*p);
		++p;
	}
	p=s->getvitrbegin();
	while(p!=s->getvitrend()){
		s1->insertElement(*p);
		++p;
	}
	return s1;
}

bool SetOfStrings::isEqual(SetOfStrings *s)
{
	p=setv.begin();
	while(p!=setv.end()){
		if(!(s->isMember(*p))){
			return false;
		}
		++p;
	}

	if (size() == s->size()){
		return true;
	} else {
		return false;
	}
}

string SetOfStrings::returnElement(int index)
{
	if (index < (int)setv.size() && index >= 0)
		return setv.at(index);
	else
		return "\n";
}

//creates a cross product set, using setv and input set s
SetOfStrings *SetOfStrings::product(SetOfStrings *s)
{
    SetOfStrings *out = new SetOfStrings();
    for(std::vector<string>::iterator it1=setv.begin(); it1!=setv.end(); ++it1){
    	for(std::vector<string>::iterator it2=s->getvitrbegin(); it2!=s->getvitrend(); ++it2){
			string product = *it1 + "," + *it2;
			out->insertElement(product);
		}
    }
    return out;
}

//checks if input set s is a subset of setv
bool SetOfStrings::subset(SetOfStrings *s)
{
	vector<string>::iterator it = s->getvitrbegin();
	while(it!=s->getvitrend()){
		if(!(isMember(*it))){
			return false;
		}
		++it;
	}
    return true;
}
