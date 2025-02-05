#include "RedoAction.h"
#include<fstream>
RedoAction::RedoAction(ApplicationManager* pApp):Action(pApp)
{
}

void RedoAction::ReadActionParameters()
{
}

void RedoAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	if (pManager->getRedoCnt())
	{
		pManager->RedoAct();
		pOut->PrintMessage("Redo");
		pOut->ClearDrawArea();
		pManager->setRedoCnt(pManager->getRedoCnt()-1);
	}
	else
	{
		pOut->PrintMessage("No actions to be Redone");
	}
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void RedoAction::Record()
{
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Redo" << endl;              
	Rec.close();
		
	
}

void RedoAction::Play(fstream& Play)
{
	Execute();

}
