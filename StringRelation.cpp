/*
 * StringRelation.cpp
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#include "StringRelation.h"

//will be used for calling the ColourText() method in print() functions
SetOfStrings *S = new SetOfStrings();

vector<int>::iterator StringRelation::getwitrbegin(){
	vector<int>::iterator it=weight.begin();
    return it;
}

vector<int>::iterator StringRelation::getwitrend(){
	vector<int>::iterator it=weight.end();
    return it;
}

string StringRelation::getPath(){
	return path;
}

void StringRelation::insertWeight(int s)
{
	weight.push_back(s);
}

int StringRelation::getWeight(string s){
	int pos = memberIndex(setv,s);
	return weight[pos];
}

bool StringRelation::isWeightEmpty(){
	if(weight.empty()) return true;
	else return false;
}

//This helps by assigning the composition member
//s is the pointer to the input set
//and R \subseteq s \times s
void StringRelation::setInput(SetOfStrings *s)
{
	set1=s;
}

//check if the relation provided as input is a
//valid relation i.e., R \subseteq S \times S
//Return true when valid; false otherwise
bool StringRelation::isValid(){
	//Create the product of set1 with itself
	//out= set1 /times set1
	SetOfStrings *out = new SetOfStrings();
	out = set1->product(set1);
	//Overloaded printRelation method used for printing the relation that is
	//equal to the product set
	if(out->subset(this)) return true;
	else return false;
}

//This is one of the main helper function provided as a
//tokenizer to parse relational elements and separate them into components
//This takes a relation element in the form "a,b" and returns
//a string vector containing "a" and "b"
vector<string> StringRelation::makeTokens(string next){
	vector<string> out;
	vector<string>::iterator p;
	char *a = new char [next.length()+1];
	strcpy(a,next.c_str());
	char* token = std::strtok(a,",");
			int index=0;
				while (token != NULL) {
					//std::cout << "The next token is: "<< token << '\n';
					out.push_back(token);
					token = std::strtok(NULL, ",");
					index++;
				}
	return out;
}

//helper function that returns the string "a,a" when input is "a"
string StringRelation::createReflexiveElement(string s){
	string next, next1;
	next = s;
	next1=next;
	next.append(",");
	next.append(next1);
	//cout<<"The reflexive element created"<<next<<endl;
	return next;
}

//helper function that returns the string "a,b" when input is "a" and "b"
string StringRelation::createPairElement(string a, string b){
	string next, next1;
	next = a;
	next1 = b;
	next.append(",");
	next.append(next1);
	//cout<<"The pair element created"<<next<<endl;
	return next;
}

//helper function that creates a dual of "a,b" as "b,a"
string StringRelation::computeDual(string s){

	vector<string> tokens=makeTokens(s);
	vector<string>::iterator p;
	p=tokens.begin();
	string other, other1;
	while(p!=tokens.end()-1){
		other=*p;
		//cout<<"Other: "<< *p << "\n";
		other1=*(p+1);
		//cout<<"Other1: "<<other1<<"\n";
		other1.append(",");
		other1.append(other);
		++p;
	}
	//cout<<"Other1:"<<other1<<endl;
	return other1;
}

//return "a" if s is of the form "a,b"
string StringRelation::returnFirstComponent(string s){
    vector<string> tokens;
    vector<string>::iterator p;
    tokens=makeTokens(s);
    p=tokens.begin();
    return *(p);
}

//return "b" if s is of the form "a,b"
string StringRelation::returnSecondComponent(string s){
	vector<string> tokens;
	vector<string>::iterator p;
	tokens=makeTokens(s);
	p=tokens.begin();
	return *(p+1);
}

//check if s is of the form "a,a" and return true if so
//return false otherwise
bool StringRelation::isReflexiveElement(string s){
	if(isMember(createReflexiveElement(s))){
		return true;
	}
    return false;
}
//check if the relation is reflexive
//if for all s \in set1, (s,s) \in r then reflexive
bool StringRelation::isReflexive(){
    for(std::vector<string>::iterator it=set1->getvitrbegin(); it!=set1->getvitrend(); ++it){
		if(!(isReflexiveElement(*it))){
			return false;
		}
    }
    return true;
}

//check if the relation is symmetric
//if for any s1,s2 \in set1, (s1,s2) \in R implies (s2,s1) \in R
bool StringRelation::isSymmetric(){
	for(std::vector<string>::iterator it=setv.begin(); it!=setv.end(); ++it){
		if(!(isMember(computeDual(*it)))){
			return false;
		}
	}
	return true;
}

//check if the relation is transitive
// for all x,y,z \in set1, (x -> y AND y -> z) implies x -> z
bool StringRelation::isTransitive(){
	for(std::vector<string>::iterator i=setv.begin(); i!=setv.end(); ++i){
		string a = returnFirstComponent(*i);
		string b = returnSecondComponent(*i);
		for(std::vector<string>::iterator j=setv.begin(); j!=setv.end(); ++j){
			if(i==j) 						continue;
			if(!(isFirstComponent(b,*j))) 	continue;
			string c = returnSecondComponent(*j);
			string pair = createPairElement(a,c);
			if(!(isMember(pair))) return false;
		}
	}
    return true;
}

//return true if the relation is an equivalence relation
//return false otherwise
bool StringRelation::isEquivalence(){
	if(isReflexive() && isSymmetric() && isTransitive()){
		return true;
	} else {
		return false;
	}
}

//s1 is of the form "a" while s2 is of the form "p,q"
//if a==p then return true
bool StringRelation::isFirstComponent(string s1, string s2){
	string p = returnFirstComponent(s2);
	if(s1==p){
		return true;
	} else {
		return false;
	}
}


//Given a member of set1, this function determine the equivalence class
//for this element s1 i.e. {s| (s,s1) \in R and R is a equivalence relation}
SetOfStrings *StringRelation::computeEquivalenceClass(string element){
	SetOfStrings *out = new SetOfStrings();
	if(isEquivalence()){
		for(std::vector<string>::iterator it=setv.begin(); it!=setv.end(); ++it){
			string s1 = returnSecondComponent(*it);
			if(s1 == element){
				out->insertElement(returnFirstComponent(*it));
			}
		}
	}
    return out;
}

// Checks whether a destination is reachable from the source
int StringRelation::isReachable(string src, string dst){
	if (!(set1->isMember(src)) || !(set1->isMember(dst))) return -1;
	if (src == dst) return 2;
	SetOfStrings visited;
	queue<string>vertices;
	vertices.push(src);
	visited.insertElement(src);

	while(!vertices.empty()){
		string currentVertice = vertices.front();
		vertices.pop();

		for (vector<string>::iterator it = setv.begin(); it!=setv.end(); ++it){
			string first = returnFirstComponent(*it);
			string second = returnSecondComponent(*it);
			if (!(currentVertice == first)){continue;}
			if (dst == second){return 1;}
			if (!(visited.isMember(second))){
				visited.insertElement(second);
				vertices.push(second);
			}
		}
	}
	return 0;
}

//helper function for implementing Dijkstra's algorithm to find index of min distance in a vector
int StringRelation::minIndex(vector<int> vec){
	vector<int>::iterator it = min_element(vec.begin(), vec.end());
	int pos = distance(vec.begin(), it);
	return pos;
}

//helper function for implementing Dijkstra's algorithm to find index of respective member in a vector
int StringRelation::memberIndex(vector<string> vec, string member){
	vector<string>::iterator it = find(vec.begin(),vec.end(),member);
	int pos = distance(vec.begin(), it);
	return pos;
}

// Dijkstra algorithm implementation
// Input: source node, destination node
// Output: path length (integer)
// Note: the generated path is also stored in "path" variable
int StringRelation::computeShortest(string source, string destination){
	if (source == destination){return -1;}
	if ((isReachable(source,destination)==-1)){return -2;}
	if ((isReachable(source,destination)==0)){return -3;}

	//initialization
	vector<int>dist(set1->size(), INF);
	vector<int>processD(set1->size(), INF);
	vector<string>previous(set1->size(), "");
	vector<string>vertices;
	vector<string>processV;
	for (vector<string>::iterator it=set1->getvitrbegin(); it!=set1->getvitrend(); ++it){
		vertices.push_back(*it);
		processV.push_back(*it);
	}
	dist[memberIndex(vertices,source)] = 0;
	processD[memberIndex(vertices,source)] = 0;

	//iteration
	while(!(processV.empty())){
		int processIndex = minIndex(processD);
		string currentVertice = processV[processIndex];
		processV.erase(std::remove(processV.begin(), processV.end(), currentVertice), processV.end());
		processD.erase(std::remove(processD.begin(), processD.end(), processD[processIndex]), processD.end());

		//perform relaxation
		for (vector<string>::iterator it = setv.begin(); it!=setv.end(); ++it){
			string first = returnFirstComponent(*it);
			string second = returnSecondComponent(*it);
			if (!(currentVertice == first)){continue;}
			int newDistance = dist[memberIndex(vertices,first)] + getWeight(*it);
			if (newDistance < dist[memberIndex(vertices,second)]){
				dist[memberIndex(vertices,second)] = newDistance;
				processD[memberIndex(processV,second)] = newDistance;
				previous[memberIndex(vertices,second)] = currentVertice;
			}

		}
	}

	//Stores shortest path vertices in temp vector
	vector<string>pathVec;
	pathVec.insert(pathVec.begin(),destination);
	string prev = previous[memberIndex(vertices,destination)];
	pathVec.insert(pathVec.begin(),prev);
	while (prev != source){
		prev = previous[memberIndex(vertices,prev)];
		pathVec.insert(pathVec.begin(),prev);
	}

	//Stores formatted path string in member variable
	vector<string>::iterator it=pathVec.begin();
	path = *it; ++it;
	while(it!=pathVec.end()){
		path += " -> ";
		path += *it;
		++it;
	}

	return dist[memberIndex(vertices,destination)];
}
