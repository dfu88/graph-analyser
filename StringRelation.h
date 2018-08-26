/*
 * StringRelation.h
 *
 * 	Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#ifndef STRINGRELATION_H_
#define STRINGRELATION_H_
#include "SetOfStrings.h"

#define INF 214748364	// define infinity macro (max int)

//A class for binary relation over a single set set1
//A relation uses both "composition" and "inheritance"
//A relation "has a" set using which the binary relation is created
//A relation "is a" set and hence it extends a set
//It can perform all set operations i.e., we can create the union, intersection etc. of two relations
//It has additional behaviour not present in a set: we can test for properties such as:
//Reflexive, Symmetric, and Transitive etc.

class StringRelation : public SetOfStrings{
	private:
		SetOfStrings *set1;	// the set over which the relation is created
	    vector<int> weight; // weight vector
		string path; // string for dijkstra's path

		// String splitter, which is a helper function
		vector<string> makeTokens(string input);
		//given string "a,b" return string "b,a"
		string computeDual(string);
		//given "a", returns "a,a"
		string createReflexiveElement(string s);
		//given "a" and "b", returns "a,b"
		string createPairElement(string a, string b);
		//return true if s is of the form "a,a"
		bool isReflexiveElement(string s);
		//return true if s1 is the first component of s2
		//e.g. s1=a and s2=a,b
		bool isFirstComponent(string s1, string s2);
		//Return the first component of the string "a,b" as a
		string returnFirstComponent(string s);
		//Return the second component of the string "a,b" as b
		string returnSecondComponent(string s);
		// Return the weight of an edge
		int getWeight(string s);
		
	public:
		//getters for the private members
		vector<int>::iterator getwitrbegin();
		vector<int>::iterator getwitrend();
		string getPath();

		//inputs the set over which the relation is created
		void setInput(SetOfStrings *s);
		//insert weight
		void insertWeight(int s);
		//checks if weights vector is empty
		bool isWeightEmpty();
		//creates a relation that is identical to the product set of set1
		//then checks whether setv is a subset of product of set1
		bool isValid();
		bool isReflexive();
		bool isSymmetric();
		bool isTransitive();
		bool isEquivalence();
		SetOfStrings *computeEquivalenceClass(string element);
		
		// Find if destination node is reachable from source
		int isReachable(string src, string dst);

		//helper functions for computeShortestPath
		//return index of minimum distance
		int minIndex(vector<int> vec);
		//return index of respective member
		int memberIndex(vector<string> vec, string member);

		// Finding the shortest path
		int computeShortest(string source, string destination);

};
#endif
