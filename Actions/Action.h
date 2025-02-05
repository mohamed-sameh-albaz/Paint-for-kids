#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"
class ApplicationManager; //forward class declaration
//Base class for all possible actions
class Action
{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job
	bool isFilled;
	static int operationCount;
	string recordFile;
	const int MaxRecOperaion;
	
public:

	Action(ApplicationManager* pApp) :isFilled(false), MaxRecOperaion(20), recordFile("Record/Record.txt") { pManager = pApp; }	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;

	//Execute action (code depends on action type)
	virtual void Execute() =0;
	virtual void UndoAction() {}
	virtual void RedoAction() {}
	virtual void Record() {}; // can not be pure virtual because there are some actions that cannot be recorded
	                          // use pure and make no body in this actions that can't record 
	virtual void Play(fstream &Play) {};// can not be pure virtual because there are some actions that cannot be recorded
	
};
#endif
