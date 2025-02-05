#pragma once
#include "Actions/Action.h"
#include "Figures/CFigure.h"

class AddColorAction :
    public Action
{
private:
	CFigure* SelectedShape;
	color preDrawClr;
	color currentDrawClr;
public:
    AddColorAction(ApplicationManager* pApp);
          
	virtual void ReadActionParameters();
	
	virtual void Execute();
	virtual void UndoAction();
	virtual void RedoAction();
	virtual void Record();
	virtual void Play(fstream& Play) ; 
};

