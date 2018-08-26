/*
 *  SetUI.cpp
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#include "SetUI.h"

SetUI::SetUI()
{
	TopicScreen();
}

SetUI::~SetUI(){}

// Greet the user and shows the developer name.
void SetUI::TopicScreen()
{
	system("clear");
	cout <<"----------------------------------------------------------------------"<< endl;
	cout <<"\033[1;31mSet Calculator\033[0m\n\033[1;37mDeveloper Name: \033[0m" << "\033[1;34mDylan Fu (dfu987, 165746216)\033[0m\n";
	cout << ColorText("To know available commands, please type ",PURPLE) <<"'help'"<< endl;
	cout <<"---------------------------------------------------------------------"<< endl;
}

bool SetUI::ReadFromFile(string filename, SetOfStrings *ss, StringRelation *sr, bool verbose)
{
	string line;
	ifstream infile (filename.c_str());
	
	//return false if the file does not exist
	if (!infile.good()) return false;
	
	// displays file contents when -v
	if (verbose){
		getline(infile, line);
		cout << ColorText(line,WHITE) << "\n";
		getline(infile, line); //bypass second line
		while (getline(infile, line)){
			cout << ColorText(line,WHITE) << "\n";
			if (line.find("}")!=string::npos) {break;}
		}
	}

	infile.clear();
	infile.seekg(0, infile.beg);

	getline(infile,line); // Get the first line to extract set members
	line.erase(0,2); // Remove '//' in the line
	
	vector<string> element;
	int i = 0;
	size_t found;
	while((found = line.find(",",i))!=std::string::npos) {
		ss->insertElement(line.substr(i,found-i));
		i = found+1;	
	}
	ss->insertElement(line.substr(i));
	
	getline(infile,line); // To bypass the second line
	
	//read the rest of the file.
	while (getline(infile,line)){
		// removes whitespace
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		// find } as the finisher for file reading
		if (line.find("}")!=string::npos) {break;}
		// skip empty line
		if ((found = line.find("->",0))==std::string::npos) {continue;}
		// fetch set and relation in the line
		if (!getFromLine(ss, sr, line)) return false;
	}
	sr->setInput(ss);

	infile.close();
	
	cout<< ColorText("  File reading was successful\n",GREEN);
	cout<< ColorText("  Please type 'list' to view the members and relations defined in the graph\n",GREEN);
	cout<< ColorText("  If a directory is opened instead of a file, program will generate incorrect outputs\n",PURPLE);

	return true;
}

bool SetUI::getFromLine(SetOfStrings *ss, StringRelation *sr, string line){
	vector<string> element;
	int i = 0;
	size_t found;
	while((found = line.find("->",i))!=std::string::npos) {
		element.push_back(line.substr(i,found-i));
		i = found+2;
	}
	element.push_back(line.substr(i,line.find("[",i)-i));
	
	//create relation string by appending
	string relation = element[0]+","+element[1];

	//create temp StringRelation to check if relation is valid
	StringRelation tempR;
	tempR.setInput(ss);	tempR.insertElement(relation);
	if(!tempR.isValid()) return false;

	//if relation is already part of set
	//then file is invalid, thus return false
	if(sr->isMember(relation)) return false;
	sr->insertElement(relation);

	//extract weight as string
	size_t weightIndex = line.find("=",i)+2;
	string temp = line.substr(weightIndex,(line.find("]",i)-1)-weightIndex);
	//convert weight string into int
	int weight = atoi(temp.c_str());
	sr->insertWeight(weight);

	return true;
}

//list the members in setModel
int SetUI::ListMembers(SetOfStrings* model){
	cout<<"  The members of the "<<ColorText("sets",BLUE)<<" are:\n  => {" ;
	vector<string>::iterator p=model->getvitrbegin();
	cout<<ColorText(*p,BLUE); ++p;
	while(p!=model->getvitrend()){
		cout<<", "<<ColorText(*p,BLUE);
		++p;
	}
	cout<<"}"<<endl;
	return 1;
}

//list the members in relationModel
int SetUI::ListMembers(StringRelation* model){
	cout<<"  The members of the "<<ColorText("relations",YELLOW)<<" are:\n  => {";
	int i=0, j=0;
	j=model->size();
	while(i<j){
		string next;
		next = model->returnElement(i);
		if(i!=j-1){
			cout<<"("<<ColorText(next,YELLOW)<<")"<<", ";
			++i;
		}
		else{
			cout<<"("<<ColorText(next,YELLOW)<<")";
			++i;
		}
	}
	cout<<"}"<<endl;
	return 1;
}

//list the weights of each respective member in relationModel
int SetUI::ListWeights(StringRelation* model){
	cout<<"  The associated "<<ColorText("weights",PURPLE)<<" are:\n  => {" ;
	vector<int>::iterator it=model->getwitrbegin();
	cout<<"\033[1;35m" << *it <<"\033[0m"; ++it;
	while(it!=model->getwitrend()){
		cout<<", "<<"\033[1;35m" << *it << "\033[0m";
		++it;
	}
	cout<<"}"<<endl;
	return 1;
}

//prints the equivalence class (eqclass) of respective member
void SetUI::printEquivalenceClass(string member, SetOfStrings* eqclass){
	cout << "=> [" << ColorText(member,BLUE) <<"] = {";
	vector<string>::iterator p=eqclass->getvitrbegin();
	cout<<ColorText(*p,YELLOW); ++p;
	while(p!=eqclass->getvitrend()){
		cout<<", "<<ColorText(*p,YELLOW);
		++p;
	}
	cout<<"}"<<endl;
}

void SetUI::printError(string reason)
{
	// error message if the command cannot be understood
	if (reason.compare("command") == 0){
		cout << ColorText("  Command cannot be understood. Please enter help to see the available commands\n", RED);
	}
	// error message if the command argument is incorrect
	else if (reason.compare("argument") == 0){
		cout << ColorText("  Incorrect command arguments!\n",RED);
		cout << ColorText("  Please type help to know about the command arguments\n",RED);
	}
	// error message if the input file is invalid
	else if (reason.compare("file") == 0){
		cout << ColorText("  Error occured while reading the input file. Possible reasons:\n",RED);
		cout << ColorText("  1. File does not exist\n",RED);
		cout << ColorText("  2. Contains a invalid graph\n",RED);
		cout << ColorText("  3. Unreadable data\n",RED);
		cout << ColorText("  Graph could not be loaded successfully\n",RED);
	}
	// error message if a set hasn't been loaded
	else if (reason.compare("load") == 0){
		cout << ColorText("  There is no set loaded to the program\n",RED);
		cout << ColorText("  Please open a file using 'open' command!\n",RED);
	}
	// error message model functions are called when set hasn't been loaded
	else if (reason.compare("graph") == 0){
		cout << ColorText("  Operation could be initialized because there is no graph to compute\n",RED);
		cout << ColorText("  Please load a graph first by using 'open' command which will read a file\n",RED);
	}
	// error message if member doesn't exist in the set
	else if (reason.compare("member") == 0){
		cout << ColorText("  The requested member does not exist in the set\n",RED);
		cout << ColorText("  Please type 'list' to know about existing strings\n",RED);
	}
	// error message if eqclass cmd is executed on a non-equivalent set
	else if (reason.compare("equivalence") == 0){
		cout << ColorText("  Equivalence class request could not be executed\n",RED);
		cout << ColorText("  Possibly the string does not exist in the set or there is no equivalence relation\n",RED);
	}
	// error message if source and destination are equal for path cmd
	else if (reason.compare("path") == 0){
		cout << "  Dijkstra's algorithm cannot handle (source == destination)" <<endl;
		cout << "  The shortest path distance: "<<ColorText("0",GREEN) << endl;
	}
}

void SetUI::printProperties(string property, bool isProperty){
	if (property == "equivalence"){
		if(isProperty){
			cout << ColorText("  => This is an equivalence relation\n",GREEN);
		} else {
			cout << ColorText("  => This is not an equivalence relation\n",RED);
		}
	} else {
		if(isProperty){
			cout << ColorText("  => It is "+property+"\n",GREEN);
		} else {
			cout << ColorText("  => It is not "+property+"\n",RED);
		}
	}
}

string SetUI::GetCommand()
{
	string commandInput, modCommandInput;
	cout << ">> ";
	getline (cin, commandInput);
	// Trims any leading and trailing whitespace
	commandInput.erase(commandInput.begin(), std::find_if(commandInput.begin(), commandInput.end(), [](int ch) {
		return !std::isspace(ch);
	}));
	commandInput.erase(std::find_if(commandInput.rbegin(), commandInput.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), commandInput.end());
	// Removes any unnecessary whitespace within the string
	unique_copy (commandInput.begin(), commandInput.end(), back_insert_iterator<string>(modCommandInput), [](char a,char b){ return isspace(a) && isspace(b);});
	commandInput = modCommandInput;
	return commandInput;
}

//prints the help message (Completed)
void SetUI::Help()
{
	cout << ColorText("Current available commands:\n",PURPLE);
	cout << ColorText("Anything inside <> bracket is an optional argument, while [] bracket contains a must argument.\n\n",PURPLE);
	cout << left << setw(45) << ColorText("	help", RED) << left << setw(50) << "Show help." << endl << endl;
	cout << left << setw(45) << ColorText("	ls <path> ", RED) << left << setw(50) << "Identical to the ls shell command. If a path is given, then" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "the program returns all the files in that path." << endl << endl;
	cout << left << setw(45) << ColorText("	clear ", RED) << left << setw(50) << "Identical to the clear shell command. Clear the screen." << endl << endl;
	cout << left << setw(45) << ColorText("	open [file_path] <-v>", RED) << left << setw(50) << "Open a file. If the file does not exist, then program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message. If -v (verbose) option is enabled (e.g., open a.txt -v)," << endl;
	cout << left << setw(41) << "" << left << setw(50) << "then each line in the file is printed on console while reading." << endl << endl;
	cout << left << setw(45) << ColorText("	list", RED) << left << setw(50) << "List all the members of set and relation." << endl << endl;
	cout << left << setw(45) << ColorText("	check [OPTION] ", RED) << left << setw(50) << "Check the relation. The option has to be provided. Options are:" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-r (reflexive)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-s (symmetric)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-t (transitive)" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "-e (equivalence relation)" << endl << endl;
	cout << left << setw(45) << ColorText("	eqclass [VALUE]", RED) << left << setw(50) << "Show equivalence class of the given [VALUE = Set member]." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If VALUE is not a member of set, then the program returns" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	reachable [VALUE1] [VALUE2]", RED) << left << setw(50) << "This command checks if two given members are connected to each other" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "If any of VALUE1 and VALUE2 is not a member of the set, then it" << endl;
	cout << left << setw(41) << "" << left << setw(50) << "returns an error message." << endl << endl;
	cout << left << setw(45) << ColorText("	path [VALUE1] [VALUE2]", RED) << left << setw(50) << "Apply Dijkstra algorithm to find the shortest path." << endl;
	cout << left << setw(41) << "" << left << setw(50) << "VALUE1 and VALUE2 are members of the set. VALUE1 is the starting node, and VALUE2 is the destination." << endl << endl;
	cout << left << setw(45) << ColorText("	exit", RED) << left << setw(50) << "Terminate the program." << endl;
	cout << "\n\n";
}

void SetUI::printReachable(string reason){
	if (reason.compare("unreachable") == 0){
		cout << ColorText("  Unreachable!\n", RED);
	}
	else if (reason.compare("reachable") == 0){
		cout << ColorText("  Reachable!\n",GREEN);
	}
	else if (reason.compare("==") == 0){
		cout << ColorText("  Reachable!\n",GREEN);
		cout << ColorText("  (Source == Destination)\n",PURPLE);
	}
}

void SetUI::printShortestPath(int distance, string path){
	cout << "  The shortest path distance: \033[1;32m"<< distance <<"\033[0m"<<endl;
	cout << "  The path is: " << ColorText(path, BLUE) << endl;
}

string SetUI::ColorText(string s, COLOR color)
{
	string temp;
	switch (color) {
		case RED: temp = "\033[1;31m" + s + "\033[0m"; break;
		case BLUE: temp = "\033[1;34m" + s + "\033[0m"; break;
		case YELLOW: temp = "\033[1;33m" + s + "\033[0m"; break;
		case GREEN: temp = "\033[1;32m" + s + "\033[0m"; break;
		case WHITE: temp = "\033[1;37m" + s + "\033[0m"; break;
		case PURPLE: temp = "\033[1;35m" + s + "\033[0m"; break;
		default: temp = "\033[0m" + s; break;
	}
	return temp;
}

