#include "popUpAction.h"
#include "ApplicationManager.h"
#include<fstream>
popUpAction::popUpAction(ActionType actType,ApplicationManager* pApp):Action(pApp)
{
	PopAct = actType;
}

void popUpAction::ReadActionParameters()
{
}

void popUpAction::Execute()
{
	CFigure* SelectedShape = pManager->GetLastSelected();
	Output* pOut = pManager->GetOutput();
	switch (PopAct) {
	case TO_ShapesToolBar:
		pOut->PrintMessage("Action: Switch to shapes tool bar, creating Design tool bar");
		pOut->CreateShapesToolBar();
		break;
	case TO_COLOR:
		pOut->PrintMessage("Action: Switch to colors tool bar, creating Design tool bar");
		pOut->CreateColorsToolBar();
		break;
	case TO_FILL:
		pOut->PrintMessage("Action: Switch to fill-colors tool bar, creating Design tool bar");
		pOut->CreateFillColorsToolBar();
	}

	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void popUpAction::Record()
{

  fstream Rec(recordFile, ios::app);
  Rec << "\t" << "popUpAction" << "\t" << PopAct;             
  Rec.close();
		
}

void popUpAction::Play(fstream& Play)
{
	Execute();
}

