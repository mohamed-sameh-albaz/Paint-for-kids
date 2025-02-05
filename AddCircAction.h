#pragma once
#include "Actions/Action.h"
#include "CCircle.h"

class AddCircAction :
    public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo CircGfxInfo;
	CCircle* Circ;
public:
	AddCircAction(ApplicationManager* pApp);

	//Reads Circle parameters            NOTE: we need to know why there is the virtual keyword
	virtual void ReadActionParameters();

	//Add Circle to the ApplicationManager
	virtual void Execute();
	virtual void UndoAction();
	virtual void RedoAction();
	virtual void Record();
	virtual void Play(fstream& Play);

};

