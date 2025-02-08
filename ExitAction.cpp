#include "ExitAction.h"
#include<fstream>

ExitAction::ExitAction(ApplicationManager* pApp) :Action(pApp)
{
}

void ExitAction::ReadActionParameters()
{
}

void ExitAction::Execute()
{

	fstream Rec(recordFile, ios::out);
	Rec << "EmptyRecord";
	if (!pManager->isMuted())
		PlaySound("sounds/bye_effect", NULL, SND_ASYNC);
	Sleep(1000);
}
