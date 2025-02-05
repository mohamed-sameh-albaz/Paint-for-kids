#include "DrwModAction.h"

DrwModAction::DrwModAction(ApplicationManager* pApp) :Action(pApp)
{
	Output* pOut = pManager->GetOutput();

	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Draw Mode Activated");
}

void DrwModAction::ReadActionParameters()
{}

void DrwModAction::Execute()
{}
