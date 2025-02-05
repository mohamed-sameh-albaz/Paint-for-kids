#pragma once
#include "Actions/Action.h"
class popUpAction : public Action
{
private:
	ActionType PopAct;
public:
	popUpAction(ActionType,ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	virtual void Record();
	virtual void Play(fstream& Play) ; // can not be pure virtual because there are some actions that cannot be recorded


};

