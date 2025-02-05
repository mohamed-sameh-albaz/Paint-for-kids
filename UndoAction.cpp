#include "UndoAction.h"
#include<fstream>
UndoAction::UndoAction(ApplicationManager* pApp):Action(pApp)
{
}

void UndoAction::ReadActionParameters()
{
}

void UndoAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	if (pManager->getUndoCnt())
	{
		pManager->UndoAct();
		pOut->PrintMessage("Undo");
		pOut->ClearDrawArea();
		pManager->setRedoCnt(pManager->getRedoCnt()+1);
	}
	else
	{
		pOut->PrintMessage("No actions to be Undone");
	}

	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void UndoAction::Record()
{	
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Undo" << endl;         
	Rec.close();
		
	
}

void UndoAction::Play(fstream& Play)
{

	Execute();

}
