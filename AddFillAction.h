#pragma once
#include "Actions/Action.h"
#include "Figures/CFigure.h"
class AddFillAction :
    public Action
{
private:
	CFigure* SelectedShape;
	color currentFillClr;
	color preFillClr;
public:
    AddFillAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
	virtual void RedoAction();
	virtual void Record();
	virtual void Play(fstream& Play);
};

