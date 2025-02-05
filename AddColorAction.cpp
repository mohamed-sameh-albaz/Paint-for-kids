#include "AddColorAction.h"
#include "GUI/UI_Info.h"
#include "ApplicationManager.h"
#include<fstream>

AddColorAction::AddColorAction(ApplicationManager* pApp):Action(pApp),preDrawClr(UI.DrawColor),currentDrawClr(UI.DrawColor)
{
	SelectedShape = pManager->GetLastSelected();
}

void AddColorAction::ReadActionParameters()
{
}

void AddColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	switch (pOut->colornum) {
	case ITM_BLACK:
		UI.DrawColor = BLACK;
		break;
	case ITM_BLUE:
		UI.DrawColor = BLUE;
		break;
	case ITM_GREEN:
		UI.DrawColor = GREEN;
		break;
	case ITM_ORANGE:
		UI.DrawColor = ORANGE;
		break;
	case ITM_RED:
		UI.DrawColor = RED;
		break;
	case ITM_YELLOW:
		UI.DrawColor = YELLOW;
		break;
	}
	if (SelectedShape)
	{
		preDrawClr = currentDrawClr;
		currentDrawClr = UI.DrawColor;
		SelectedShape->SetSelected(false);
		SelectedShape->ChngDrawClr(currentDrawClr);

		pManager->AddActToUndoRedo(this);
		pManager->setWillBeDeleted(true);
		pManager->ResetRedoCnt();
	}
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void AddColorAction::UndoAction()
{
	SelectedShape->ChngDrawClr(preDrawClr);
	UI.DrawColor=preDrawClr; 
}

void AddColorAction::RedoAction()
{
	SelectedShape->ChngDrawClr(currentDrawClr);
	preDrawClr = currentDrawClr;
	UI.DrawColor = currentDrawClr;
}


void AddColorAction::Record()
{	
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec <<  "\t" << pOut->colornum << endl;
	Rec.close();
}

void AddColorAction::Play(fstream& Play)
{
	Execute();
}

 
