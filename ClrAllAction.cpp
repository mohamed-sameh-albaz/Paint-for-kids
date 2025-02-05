#include "ClrAllAction.h"
#include<fstream>
ClrAllAction::ClrAllAction(ApplicationManager* pApp) :Action(pApp)
{
}

void ClrAllAction::ReadActionParameters()
{
}

void ClrAllAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigCount())
	{
		pManager->ClearAll();
		pOut->ClearDrawArea();
	}
	pManager->ClearUndoRedoList();
	pManager->ResetUndoCnt();
	pManager->ResetRedoCnt();
	pOut->PrintMessage("Clear All");
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void ClrAllAction::Record()
{	
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "ClearAll" << endl;              
	Rec.close();
		
}

void ClrAllAction::Play(fstream& Play)
{
	Execute();

}
