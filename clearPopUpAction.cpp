#include "clearPopUpAction.h"
#include "ApplicationManager.h"
#include<fstream>
clearPopUpAction::clearPopUpAction(ActionType OpenedPopUp,ApplicationManager* pApp):Action(pApp)
{
	this->OpenedPopUp = OpenedPopUp;
}

void clearPopUpAction::ReadActionParameters()
{
}

void clearPopUpAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearPopUp();
	switch (OpenedPopUp) {

	case TO_ShapesToolBar:
		pManager->UpdateInterface();
		pOut->CreateShapesToolBarTAB();
		break;
	case TO_COLOR:
		pOut->CreateColorsToolBarTAB();
		break;
	case TO_FILL:
		pOut->CreateFillColorsToolBarTAB();
		break;
	}
	pManager->UpdateInterface();
}

void clearPopUpAction::Record()
{
	
}

void clearPopUpAction::Play(fstream& Play)
{


}
