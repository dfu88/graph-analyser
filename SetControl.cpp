/* This is the controller part for your program.
 * In this file, students are required to complete the "control" logic.
 * Controller accepts keyboard inputs from the user through View, and manipulate data in Model.
 * Then, the result from Model is sent back to user through View.
 * Think about the design before the actual implementation.
 * Various diagrams such as class diagram and sequence diagram can be very helpful.
 *
 *  SetControl.cpp
 *
 *  Created on: 23/10/2017
 *	  Author: Dylan Fu
 */

#include "SetControl.h"

SetControl::SetControl()
{
	cout <<"Initializing the calculator, please wait! ... \n" << endl;
	
	//Initialize all members
	setUI = new SetUI();
	setModel = new SetOfStrings();
	relationModel = new StringRelation();
}

SetControl::~SetControl()
{
	//dispose all members
	delete setUI;
	delete setModel;
	delete relationModel;
}

bool SetControl::Run()
{			
	#ifdef _DEBUG
		Testing();
		return false; // exit the program after testing
	#endif

	string command, modCommand;
	
	//invoke the main user interaction
	while(true)
	{
		
		//show the menu and get user command
		command = setUI->GetCommand();
	
		int argc = 0;

		// string tokenizer to split string by using " " as the separator.
		// stores the values in argv array while the number of argument is argc.
		vector<string> argv;
		int i = 0;
		size_t found;
		if (!command.empty()){
			while((found = command.find(" ",i))!=std::string::npos) {
				argv.push_back(command.substr(i,found-i));
				i = found+1;
			}
			argv.push_back(command.substr(i));
		}

		argc = argv.size();

		// if enter is pressed
		if (argc == 0) continue;

		//help command execution (Completed)
		if (argv.at(0).compare("help")==0){
			setUI->Help();
		}
		//ls command execution (Completed)
		else if (argv.at(0).compare("ls")==0){
			if (!(argc == 1 || argc == 2)){setUI->printError("argument"); continue;}
			if (argc == 2){
				string cmd(argv[1]);
				cmd = "ls " + cmd;
				system(cmd.c_str());		
			}		
			else system("ls");
		}
		//clear command execution (Completed)
		else if (argv.at(0).compare("clear")==0){
			if (!(argc == 1)){setUI->printError("argument"); continue;}
			if (argc == 1){
				system("clear");
				setUI->TopicScreen();
			}
		}
		//open command execution
		else if (argv.at(0).compare("open")==0){
			if (!(argc == 2 || argc == 3)) {setUI->printError("argument"); continue;}
			SetOfStrings *temps = new SetOfStrings();
			StringRelation *tempr = new StringRelation();
			if (argc == 2){
				if (!(setUI->ReadFromFile(argv.at(1), temps, tempr, false))){
					//if file cannot be read or invalid
					setUI->printError("file");
					delete temps;
					delete tempr;
					continue;
				} else {
					setModel = temps;
					relationModel = tempr;
					relationModel->setInput(setModel);
//					setUI->printLoadSuccess();
				}
			}
			else if ((argc==3)&&(argv.at(2).compare("-v")==0)){
				if (!(setUI->ReadFromFile(argv.at(1), temps, tempr, true))){
					//if file cannot be read or invalid
					setUI->printError("file");
					delete temps;
					delete tempr;
					continue;
				} else {
					setModel = temps;
					relationModel = tempr;
					relationModel->setInput(setModel);
//					setUI->printLoadSuccess();
				}
			}
			else{
				//if the file cannot be read
				if (!setUI->ReadFromFile(argv.at(1), temps, tempr, (argv.at(2).compare("-v") == 0) ? true:false)) {
					setUI->printError("file");
					delete temps;
					delete tempr;
					continue;
				}
			}
		}
		//list command execution
		else if (argv.at(0).compare("list")==0){
			if (!(argc == 1)) {setUI->printError("argument"); continue;}
			if ((setModel->isEmpty())||(relationModel->isEmpty())||(relationModel->isWeightEmpty())) {setUI->printError("load"); continue;}
			setUI->ListMembers(setModel);
			setUI->ListMembers(relationModel);
			setUI->ListWeights(relationModel);
		}
		//check command execution
		else if (argv.at(0).compare("check")==0){
			if (!(argc == 2)) {setUI->printError("argument"); continue;}
			if ((setModel->isEmpty())||(relationModel->isEmpty())||(relationModel->isWeightEmpty())) {setUI->printError("graph"); continue;}
			if (argv.at(1).compare("-r")==0) {setUI->printProperties("reflexive",relationModel->isReflexive()); continue;}
			else if (argv.at(1).compare("-s")==0) {setUI->printProperties("symmetric",relationModel->isSymmetric()); continue;}
			else if (argv.at(1).compare("-t")==0) {setUI->printProperties("transitive",relationModel->isTransitive()); continue;}
			else if (argv.at(1).compare("-e")==0) {setUI->printProperties("equivalence",relationModel->isEquivalence()); continue;}
			else {setUI->printError("argument"); continue;}
		}
		//eqclass command execution
		else if (argv.at(0).compare("eqclass")==0){
			if (!(argc == 2)) {setUI->printError("argument"); continue;}
			if ((setModel->isEmpty())||(relationModel->isEmpty())||(relationModel->isWeightEmpty())) {setUI->printError("graph"); continue;}
			if (!(relationModel->isEquivalence())) {setUI->printError("equivalence"); continue;}
			if (!(setModel->isMember(argv.at(1)))) {setUI->printError("member"); continue;}
			SetOfStrings *eqclass = new SetOfStrings();
			eqclass = relationModel->computeEquivalenceClass(argv.at(1));
			setUI->printEquivalenceClass(argv.at(1), eqclass);
			delete eqclass;
		}
		//reachable command execution
		else if (argv.at(0).compare("reachable")==0){
			if (!(argc == 3)) {setUI->printError("argument"); continue;}
			if ((setModel->isEmpty())||(relationModel->isEmpty())||(relationModel->isWeightEmpty())) {setUI->printError("graph"); continue;}
			if ((relationModel->isReachable(argv.at(1),argv.at(2)))==-1){setUI->printError("member"); continue;}
			if ((relationModel->isReachable(argv.at(1),argv.at(2)))==1){setUI->printReachable("reachable"); continue;}
			if ((relationModel->isReachable(argv.at(1),argv.at(2)))==2){setUI->printReachable("=="); continue;}
			if ((relationModel->isReachable(argv.at(1),argv.at(2)))==0){setUI->printReachable("unreachable"); continue;}
		}
		//path command execution
		else if (argv.at(0).compare("path")==0){
			if (!(argc == 3)) {setUI->printError("argument"); continue;}
			if ((setModel->isEmpty())||(relationModel->isEmpty())||(relationModel->isWeightEmpty())) {setUI->printError("graph"); continue;}
			if ((relationModel->computeShortest(argv.at(1),argv.at(2)))==-1){setUI->printError("path"); continue;}
			else if ((relationModel->computeShortest(argv.at(1),argv.at(2)))==-2){setUI->printError("member"); continue;}
			else if ((relationModel->computeShortest(argv.at(1),argv.at(2)))==-3){setUI->printReachable("unreachable"); continue;}
			else {setUI->printShortestPath(relationModel->computeShortest(argv.at(1),argv.at(2)), relationModel->getPath());}
		}
		// exit command execution
		else if (argv.at(0).compare("exit")==0){
			if (!(argc == 1)) {setUI->printError("argument"); continue;}
			exit(0);
		}
		//command is invalid
		else{
			setUI->printError("command");
		}
	}
	return true;
}

// This function is compiled only when the debug flag is enabled.
#ifdef _DEBUG
void SetControl::Testing(){
	//the name of each test file is hardcoded here.
	SetOfStrings *setTest = new SetOfStrings();
	StringRelation *relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/a.txt", setTest, relationTest, false)==true, "File successfully opened: a.txt");
	// a.txt file contains a graph that is reflexive but not symmetric and transitive.
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive"); // pass if reflexive
	ASSERT(relationTest->isSymmetric()==false, "Relation is not symmetric"); // pass if NOT symmetric
	ASSERT(relationTest->isTransitive()==false, "Relation is not transitive"); // pass if NOT transitive
	
	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/b.txt", setTest, relationTest, false)==true, "File successfully opened: b.txt");
	// b.txt file contains a graph that is reflexive and symmetric but not transitive.
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive"); // pass if reflexitve
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric"); // pass if symmetric
	ASSERT(relationTest->isTransitive()==false, "Relation is not transitive"); // pass if NOT transitive
	
	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/c.txt", setTest, relationTest, false)==true, "File successfully opened: c.txt");
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive");
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric");
	ASSERT(relationTest->isTransitive()==true, "Relation is transitive");
	
	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/d.txt", setTest, relationTest, false)==true, "File successfully opened: d.txt");
	ASSERT(relationTest->isReflexive()==true, "Relation is reflexive");
	ASSERT(relationTest->isSymmetric()==true, "Relation is symmetric");
	ASSERT(relationTest->isTransitive()==true, "Relation is transitive");
	
	setTest = new SetOfStrings();
	relationTest = new StringRelation();
	ASSERT(setUI->ReadFromFile("TestCases/e.txt",setTest,relationTest, false)==true, "File successfully opened: e.txt");
	ASSERT(relationTest->isReflexive()==false, "Relation is not reflexive");
	ASSERT(relationTest->isSymmetric()==false, "Relation is not symmetric");
	ASSERT(relationTest->isTransitive()==false, "Relation is not transitive");
}
#endif


