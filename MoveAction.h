#pragma once
#include "Figures/CFigure.h"
#include "Actions/Action.h"

class MoveAction :public Action
{
private:
	Point p;
	Point preCntr;
	CFigure* SelectedShape;
public:
	MoveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
	virtual void RedoAction();
	virtual void Record();
	virtual void Play(fstream& Play);


};

