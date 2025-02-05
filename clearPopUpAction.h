#pragma once
#include "Actions/Action.h"
class clearPopUpAction :public Action
{
private:
	ActionType OpenedPopUp;
public:
	clearPopUpAction(ActionType ,ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();

	virtual void Record();

	virtual void Play(fstream& Play);

};

