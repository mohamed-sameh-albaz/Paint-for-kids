#include "UndoAction.h"
#include<fstream>
Undoaction::Undoaction(ApplicationManager* pApp):Action(pApp)
{
}

void Undoaction::ReadActionParameters()
{
}

void Undoaction::Execute()
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

void Undoaction::Record()
{	
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Undo" << endl;         
	Rec.close();
		
	
}

void Undoaction::Play(fstream& Play)
{

	Execute();

}
