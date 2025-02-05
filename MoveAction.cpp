#include "MoveAction.h"
#include "ApplicationManager.h"
#include "Figures/CRectangle.h"
#include<fstream>

MoveAction::MoveAction(ApplicationManager* pApp):Action(pApp)
{
	SelectedShape = pManager->GetLastSelected();
}

void MoveAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(p.x,p.y);
	
}

void MoveAction::Execute()
{
	
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigCount() && SelectedShape) {

		pOut->PrintMessage("Enter your distination :-)");

		//This action needs to read some parameters first
		ReadActionParameters();
		if(SelectedShape->getMovingValidity(p))
		{
			preCntr = SelectedShape->getPreCoord();
			SelectedShape->move(p);
			SelectedShape->SetSelected(false);
			pOut->ClearDrawArea();
			pOut->ClearStatusBar();

			pManager->AddActToUndoRedo(this);
			pManager->setWillBeDeleted(true);
			pManager->ResetRedoCnt();
		}
		else
		{
			pOut->PrintMessage("Give valid position");
		}
	}
	else
	{
		pManager->GetFigCount() ? pOut->PrintMessage("No Selected Figures to Move!")
			:pOut->PrintMessage("No Figures to Move!");	
	}
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void MoveAction::UndoAction()
{
	SelectedShape->move(preCntr);
}

void MoveAction::RedoAction()
{
	SelectedShape->move(p);
}

void MoveAction::Record()
{
		
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Move" << "\t" << p.x << "\t" << p.y << endl;
	Rec.close();

	
}

void MoveAction::Play(fstream& Play)
{
	Play >> p.x >> p.y;
	Execute();
}