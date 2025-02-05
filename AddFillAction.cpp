#include "AddFillAction.h"
#include "ApplicationManager.h"
#include "GUI/UI_Info.h"
#include<fstream>

AddFillAction::AddFillAction(ApplicationManager* pApp) :Action(pApp),preFillClr(UI.FillColor)
{
	SelectedShape = pManager->GetLastSelected();
}

void AddFillAction::ReadActionParameters()
{
}

void AddFillAction::Execute()
{
	Output* pOut = pManager->GetOutput();
		preFillClr = UI.FillColor;
	switch (pOut->fillcolornum) {
	case ITM_NO_FILL :
		UI.FillColor = UI.BkGrndColor;   
		break;
	case ITM_BLACK_FILL:
		UI.FillColor = BLACK;
		break;
	case ITM_BLUE_FILL:
		UI.FillColor = BLUE;
		break;
	case ITM_GREEN_FILL:
		UI.FillColor = GREEN;
		break;
	case ITM_ORANGE_FILL:
		UI.FillColor = ORANGE;
		break;
	case ITM_RED_FILL:
		UI.FillColor = RED;
		break;
	case ITM_YELLOW_FILL:
		UI.FillColor = YELLOW;
		break;
	}

	if (SelectedShape)
	{
		currentFillClr = UI.FillColor;
		SelectedShape->SetSelected(false);
		SelectedShape->ChngFillClr(UI.FillColor);

		pManager->AddActToUndoRedo(this);
		pManager->setWillBeDeleted(true);
		pManager->ResetRedoCnt();
		pOut->ClearDrawArea();
	}
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void AddFillAction::UndoAction()
{
	SelectedShape->ChngFillClr(preFillClr);
	UI.FillColor = preFillClr;
}

void AddFillAction::RedoAction()
{
	SelectedShape->ChngFillClr(currentFillClr);
	UI.FillColor = currentFillClr;
}

void AddFillAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t"<< pOut->fillcolornum << endl;
	Rec.close();
}

void AddFillAction::Play(fstream& Play)
{
	Execute();
}
