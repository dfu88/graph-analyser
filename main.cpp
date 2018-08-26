/* 
 * This is the main.cpp given to you for the second part of your assignment.
 * 
 * Students do not need to change anything in this file.
 *
 * Created on: 3/09/2015
 *     Author: Jin Ro
*/

#include "SetControl.h"

int main(int argc, const char * argv[])
{
	//create system handler instance
	SetControl* controller = new SetControl();
	
	//run the system
	controller->Run();
	
	//must delete explicitly when "new" is used
	delete controller;
	
	return 0;
}


