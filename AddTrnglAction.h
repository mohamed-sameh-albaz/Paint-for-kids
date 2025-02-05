#pragma once
#include "Actions/Action.h"
#include "CTriangle.h"

class AddTrnglAction :public Action
{
private:
	Point P1, P2, P3;
	GfxInfo TrnglGfxInfo;
	CTriangle* Trig;
public:
	AddTrnglAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
	virtual void RedoAction();

	virtual void Record();

	virtual void Play(fstream& Play); // can not be pure virtual because there are some actions that cannot be recorded


};

