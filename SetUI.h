/*
 *  SetUI.h
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#ifndef __SetUI__
#define __SetUI__

#include "StringRelation.h"
#include "SetOfStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
enum COLOR {RED=0, BLUE, GREEN, WHITE, YELLOW, PURPLE};

class SetUI
{
	private:
		//helper function to enable colorful console printouts.
		//COLOR is defined as enum.
		//Takes a string as an input, then return the same string in a different color.
		string ColorText(string s, COLOR color);
		
		//helper function that takes an input string and split it into parts (e.g., "5->3" becomes '5' and '3').
		//If this relation is a valid binary relation, then add this relation to the 'relation' set.
		//Return true if nothing went wrong, else return false.
		bool getFromLine(SetOfStrings *set, StringRelation *relation, string line);
		
	public:
		//constructor/destructor
		SetUI();
		~SetUI();

		//print function for the top banner message.
		//it should include the developer name (i.e., your name)
		void TopicScreen();
		
		//all the error messages are predefined in this function so that they can be
		//called by controller whenever an error is detected.
		void printError(string reason);

		//this function is used to print the result of set properties.
		//E.g., printProperties ("reflexive", true) should print something like:
		//"This graph is reflexive"
		//while, printProperties ("reflexive", false) should print something like:
		//"This graph is not reflexive"
		//Similar to other properties: reflexive, symmetric, transtivie, and equivalence relation
		void printProperties(string property, bool isProperty);
		
		//print help
		void Help();
		
		//reads the keyboard inputs from user
		string GetCommand();
		
		//List all the members in the set of strings.
		//Returns 0 if there is nothing in the model.
		int ListMembers(SetOfStrings* model);
		
		//List all the members in the set of relations.
		//Return 0 if there is nothing in the relation model.
		int ListMembers(StringRelation* model);

		//List all the respective weights for each edge (relation)
		//Return 0 if there is nothing in the relation model.
		int ListWeights(StringRelation* model);
		
		// Print function for equivalence class search
		// For example, when 'eqclass 0' command is entered to the program, then
		// the printout should look like this: e.g., [0] = {1,2,3,4} where 1,2,3,4 are
		// all having equivalence relation with 0.
		// Any error message should be handled in 'printError' function. NOT here.
		void printEquivalenceClass(string member, SetOfStrings* ss);
		
		//methods for reading an input text file.
		//Given a filename, it opens the file and reads the graph.
		//Return false if there is an error while reading the file.
		//While reading the file, it stores data in *ss and *sr appropriately.
		//When verbose option is true, it prints ALL the lines in the file.
		bool ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose);

		//Method for printing whether a destination node is reachable from the source
		void printReachable(string reason);
	
		// method for printing the result of Dijkstra's algorithm applied to the input graph
		// the distance is the shortest distance to the destination
		// the path is a string which contains the path information in the format "a -> b -> ... -> z"
		void printShortestPath(int distance, string path);
};

#endif
